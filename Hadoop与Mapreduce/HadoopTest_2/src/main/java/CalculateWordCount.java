import org.apache.commons.io.IOUtils;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.mapreduce.lib.output.*;
import org.apache.log4j.BasicConfigurator;

import java.io.IOException;
import java.util.*;

/**
 * CalculateWordCount 统计单词个数
 *
 */

public class CalculateWordCount {

    //Mapper
    public static class WordCountMapper extends Mapper<Object, Text,Text, IntWritable> {
        //----------配置信息
        //类别名称
        public String[] TextClassName;
        //输入文件路径
        public String[] InputFilePath;
        //----------Mapper写入的Key与value  单词名称/类别的index
        private Text mapperKey = new Text();
        private IntWritable index  = new IntWritable(0);
        //设置
        @Override
        protected void setup(Context context) throws IOException, InterruptedException {
            Configuration config = context.getConfiguration();
            //获取配置的信息：类别名称,输入文件路径
            TextClassName = config.get("TextClassName").split(",");
            InputFilePath = config.get("InputFilePath").split(",");
        }
        //map
        public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
            //获取类别：当前路径是否包含配置的类别文件路径
            index.set(0);
            String filepath = ((FileSplit)context.getInputSplit()).getPath().toString();
            for(int i=0;i<InputFilePath.length;i++){
                if(filepath.contains(InputFilePath[i])){
                    index.set(i);
                    break;
                }
            }
            //设置Context
            StringTokenizer itr = new StringTokenizer(value.toString());
            while(itr.hasMoreTokens()) {
                mapperKey.set(itr.nextToken());
                context.write(mapperKey, index);
            }
        }
    }

    //Reduce
    public static class WordCountReducer extends Reducer<Text, IntWritable, Text, Text> {
        //----------配置信息
        public String[] TextClassName;
        public String[] InputFilePath;
        public int[] wordSumCount;
        public String outputFileName;
        public String dirPath;
        public String wordCountOutPutPath;
        public String sumOutPutPath;

        //多文件输出
        private MultipleOutputs multipleOutputs;

        //Reducer输出的Key
        private Text reducerKey =new Text();

        @Override
        protected void setup(Context context) throws IOException, InterruptedException {
            //多文件输出
            multipleOutputs = new MultipleOutputs(context);
            //获取配置的信息：
            Configuration config = context.getConfiguration();
            TextClassName = config.get("TextClassName").split(",");
            InputFilePath = config.get("InputFilePath").split(",");
            wordSumCount = new int[TextClassName.length];
            Arrays.fill(wordSumCount, 0);
            outputFileName = config.get("outputFileName");
            dirPath = config.get("dirPath");
            wordCountOutPutPath = config.get("wordCountOutputPath");
            sumOutPutPath = config.get("sumOutPutPath");
        }

        //reduce
        public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
            IntWritable val;
            int[] sumCount = new int[TextClassName.length];
            Arrays.fill(sumCount, 0);

            //统计单词
            for(Iterator it = values.iterator(); it.hasNext();) {
                val = (IntWritable)it.next();
                //当前单词对应类别出现次数
                sumCount[val.get()] += 1;
                //统计单词总个数
                wordSumCount[val.get()] += 1;
            }

            //将统计后的单词次数转成字符串写入文件,格式：  单词 次数1，次数2
            //次数顺序为类别顺序
            String tempResult = "";
            for(int i=0;i<sumCount.length;i++){
                tempResult += Integer.toString(sumCount[i]);
                if(i != sumCount.length -1){
                    tempResult +=",";
                }
            }

            reducerKey.set(tempResult);
            multipleOutputs.write("Text",key, reducerKey,dirPath+wordCountOutPutPath +"/Part");
        }

        //CleanUp
        @Override
        protected void cleanup(Context context) throws IOException, InterruptedException {
            //写入总单词个数
            Text key =new Text();
            key.set("Sum");
            String tempSum = "";
            for(int i=0;i<wordSumCount.length;i++){
                tempSum += Integer.toString(wordSumCount[i]);
                if(i != wordSumCount.length -1){
                    tempSum +=",";
                }
            }
            reducerKey.set(tempSum);
            multipleOutputs.write(key, reducerKey,dirPath+sumOutPutPath +"/Part");
            multipleOutputs.close();
        }
    }


    //MapReduce
    public static int startMapReduce(FileSystem fs,List<String> _textClassName,List<String> _textClassInputFilePath,
                                     String _inputFilePath, String _DirPath,
                                     String _outPutPath,String _wordCountOutputPath,String _sumOutPutPath, String _jobName) throws Exception{
        BasicConfigurator.configure();
        Configuration conf = new Configuration();
        //设置配置信息
        String temp_TextClassName = "";
        String temp_InputFilePath = "";
        for(int i=0;i<_textClassName.size();i++){
            temp_TextClassName +=_textClassName.get(i).toString();
            temp_InputFilePath += _textClassInputFilePath.get(i).toString();
            if(i != _textClassName.size() -1){
                temp_TextClassName += ",";
                temp_InputFilePath += ",";
            }
        }
        conf.set("TextClassName",temp_TextClassName);
        conf.set("InputFilePath",temp_InputFilePath);
        conf.set("outPutPath",_outPutPath);
        conf.set("wordCountOutputPath",_wordCountOutputPath);
        conf.set("sumOutPutPath",_sumOutPutPath);
        conf.set("dirPath",_DirPath);


        //Job设置
        Job job = Job.getInstance(conf, _jobName);
        job.setJarByClass(CalculateWordCount.class);
        job.setMapperClass(CalculateWordCount.WordCountMapper.class);
        job.setReducerClass(CalculateWordCount.WordCountReducer.class);
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(IntWritable.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);
        job.setNumReduceTasks(1);

        //设置输入路径
        List<Path> filePaths = new ArrayList<Path>();
        String content= IOUtils.toString(fs.open(new Path(_inputFilePath)), "UTF-8");
        StringTokenizer itr = new StringTokenizer(content,"\r\n");
        while(itr.hasMoreTokens()) {
            filePaths.add(new Path(itr.nextToken()));
        }

        //输入输出格式
        FileInputFormat.setInputPaths(job, (Path[])filePaths.toArray(new Path[filePaths.size()]));
        MultipleOutputs.addNamedOutput(job,"Text",TextOutputFormat.class,Text.class,Text.class);
        LazyOutputFormat.setOutputFormatClass(job,TextOutputFormat.class);
        FileOutputFormat.setOutputPath(job, new Path(_DirPath+_wordCountOutputPath));

        int result = job.waitForCompletion(true)?0:1;
        return result;
    }
}

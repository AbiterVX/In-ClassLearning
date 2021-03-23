import org.apache.commons.io.IOUtils;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataInputStream;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.BytesWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.LazyOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.MultipleOutputs;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.log4j.BasicConfigurator;

import javax.swing.*;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.*;



public class CalculateResult {
    //Mapper
    public static class ResultMapper extends Mapper<Object, BytesWritable,Text, Text> {
        //----------配置信息
        public String[] TextClassName;
        public String[] InputFilePath;
        public String wordCountInputPath;
        public String sumInputPath;
        public String hdfsPath;
        public String TrainingFiles;
        //单词字典：   K/V: 单词名/wordcount时的value（次数1，次数2，，，）
        public HashMap<String,String> wordCountData = new HashMap<String, String>();
        public Integer[] sumCount;

        //----------Mapper写入的Key与value
        private Text mapperKey = new Text();
        private Text mapperValue = new Text();
        private IntWritable textClassIndex  = new IntWritable(0);

        private double[] classProbability;
        //设置
        @Override
        protected void setup(Context context) throws IOException, InterruptedException {
            //读入配置信息
            Configuration config = context.getConfiguration();
            TextClassName = config.get("TextClassName").split(",");
            InputFilePath = config.get("InputFilePath").split(",");
            wordCountInputPath = config.get("wordCountInputPath");
            sumInputPath = config.get("sumInputPath");
            hdfsPath = config.get("hdfsPath");
            TrainingFiles = config.get("TrainingFiles");
            //FileSystem
            FileSystem fs = null;
            try {
                fs = FileSystem.get(new URI(hdfsPath),new Configuration());
            } catch (URISyntaxException e) {
                e.printStackTrace();
            }

            // 读入前一步统计的单词个数：WordCount
            String wordCountContent= IOUtils.toString(fs.open(new Path(wordCountInputPath+"/Part-r-00000")), "UTF-8");
            StringTokenizer itr = new StringTokenizer(wordCountContent,"\r\n");
            while(itr.hasMoreTokens()) {
                String token = itr.nextToken();
                String[] keyAndValue = token.split("\t");
                wordCountData.put(keyAndValue[0],keyAndValue[1]);
            }

            //读入前一步统计的每类单词总数：SumCount
            String sumContent= IOUtils.toString(fs.open(new Path(sumInputPath+"/Part-r-00000")));
            String[] temp_sumCount = sumContent.split("\t")[1].trim().split(",");
            sumCount = new Integer[TextClassName.length];
            for(int i=0;i<temp_sumCount.length;i++){
                sumCount[i]= Integer.valueOf(temp_sumCount[i]);
            }

            //测试集每个类别的概率
            classProbability = new double[TextClassName.length];
            Arrays.fill(classProbability, 1);
            List<Path> filePaths = new ArrayList<Path>();
            String content= IOUtils.toString(fs.open(new Path(TrainingFiles)), "UTF-8");
            itr = new StringTokenizer(content,"\r\n");
            int classIndex = 0;
            String token = "";
            int fileSumCount = 0;
            while(itr.hasMoreTokens()) {
                token = itr.nextToken();
                fileSumCount +=1;
                for(int i=0;i<TextClassName.length;i++){
                    if(token.contains(TextClassName[i])){
                        classProbability[i] += 1;
                        break;
                    }
                }
            }
            for(int i=0;i<TextClassName.length;i++){
                classProbability[i] /= (double)fileSumCount;
            }

        }

        //map
        public void map(Object key, BytesWritable value, Context context) throws IOException, InterruptedException {
            String content = new String(value.getBytes());

            //获取类别
            textClassIndex.set(0);
            String filepath = ((FileSplit)context.getInputSplit()).getPath().toString();
            for(int i=0;i<InputFilePath.length;i++){
                if(filepath.contains(InputFilePath[i])){
                    textClassIndex.set(i);
                    break;
                }
            }

            //对当前文件WordCount:      HashMap K/V: 单词名：个数
            HashMap<String,Integer> currentFileWordCount = new HashMap<String, Integer>();
            StringTokenizer itr = new StringTokenizer(content,"\r\n");
            while(itr.hasMoreTokens()) {
                String token =itr.nextToken();
                currentFileWordCount.merge(token, 1, Integer::sum);
            }

            //计算概率
            double[] resultProbabilities = new double[InputFilePath.length];
            //Arrays.fill(resultProbabilities, 1);
            for(int i=0;i<TextClassName.length;i++){
                resultProbabilities[i] = classProbability[i];
            }
            //遍历HashMap
            for (String tempKey : currentFileWordCount.keySet()) {
                //该单词在测试集里出现的次数
                Integer wordTimes = currentFileWordCount.get(tempKey);
                //该单词在训练集里出现的次数
                String wordCountValue = wordCountData.get(tempKey);
                String[] temp_wordCount = null;
                if(wordCountValue != null) {
                    temp_wordCount = wordCountValue.split(",");
                }

                for(int i=0;i<TextClassName.length;i++){
                    //如果未出现，设为1
                    int wordCount = 1;
                    if(temp_wordCount != null){
                        wordCount = Integer.parseInt(temp_wordCount[i]);
                        if(wordCount == 0 ){
                            wordCount = 1;
                        }
                    }
                    else{
                        wordCount = 1;
                    }
                    //计算概率： 某类别概率 *=  当前单词的概率：（ 该类别训练集出现次数 / 该类别训练集总数 ）^ 测试集出现次数
                    double temp = Math.pow( (double)wordCount/(double)sumCount[i]/4.0  *(double)sumCount[0]    ,wordTimes);
                    //System.out.println("wordCount:"+wordCount + ",temp:"+ temp);
                    resultProbabilities[i] *= temp;
                }
            }

            //将概率转为string
            String probabiltities = "";
            for(int i=0;i<resultProbabilities.length;i++){
                probabiltities += String.valueOf(resultProbabilities[i]);
                if(i != resultProbabilities.length -1){
                    probabiltities += ",";
                }
            }
            //写入
            mapperKey.set(((FileSplit)context.getInputSplit()).getPath().toString());
            mapperValue.set(probabiltities);
            context.write(mapperKey, mapperValue);
        }
    }

    //Reduce
    public static class ResultReducer extends Reducer<Text, Text, Text, Text> {
        //----------配置信息
        public String[] TextClassName;
        public String[] InputFilePath;
        public String dirPath;
        public String wordCountInputPath;
        public String sumInputPath;
        public String resultPath;
        public String resultTempPath;

        //多文件输出
        private MultipleOutputs multipleOutputs;

        //Reducer输出的Key
        private Text reducerValue =new Text();

        @Override
        protected void setup(Context context) throws IOException, InterruptedException {
            multipleOutputs = new MultipleOutputs(context);
            Configuration config = context.getConfiguration();
            //配置信息
            TextClassName = config.get("TextClassName").split(",");
            InputFilePath = config.get("InputFilePath").split(",");
            dirPath = config.get("dirPath");
            wordCountInputPath = config.get("wordCountOutputPath");
            sumInputPath = config.get("sumOutPutPath");
            resultPath = config.get("resultPath");
            resultTempPath = config.get("resultTempPath");
        }

        public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
            for (Text value : values) {
                //写入原始数据
                reducerValue.set(value);
                multipleOutputs.write("Text",key, reducerValue,dirPath+resultTempPath +"/CalculateResult-Part");

                //比较得到最大概率
                String[] probabilities = value.toString().split(",");
                double tempValue = 0;
                int textClassIndex = 0;
                double tempMax = 0;
                for(int i=0;i<probabilities.length;i++){
                    if(i>0){
                        tempValue = Double.parseDouble(probabilities[i]);
                        if(tempValue > tempMax){
                            tempMax = tempValue;
                            textClassIndex = i;
                        }
                    }
                    else{
                        textClassIndex = i;
                        tempMax = Double.parseDouble(probabilities[i]);
                    }
                }

                reducerValue.set(TextClassName[textClassIndex]);
                multipleOutputs.write("Text",key, reducerValue,dirPath+resultPath +"/Part");
            }
        }

        @Override
        protected void cleanup(Context context) throws IOException, InterruptedException {
            multipleOutputs.close();
        }
    }


    public static class WholeFileInputFormat extends FileInputFormat<NullWritable, BytesWritable>{
        @Override
        protected boolean isSplitable(JobContext context, Path file){
            return false;
        }

        @Override
        public RecordReader<NullWritable, BytesWritable> createRecordReader(InputSplit inputSplit, TaskAttemptContext taskAttemptContext) throws IOException, InterruptedException {
            WholeFileRecordReader reader = new WholeFileRecordReader();
            reader.initialize(inputSplit,taskAttemptContext);
            return reader;
        }

        class WholeFileRecordReader extends RecordReader<NullWritable,BytesWritable>{
            private FileSplit fileSplit;    //保存输入的分片，他将被转换成一条（key,value）记录
            private Configuration conf;     //配置对象
            private BytesWritable value = new BytesWritable();  //value 对象，内容为空
            private boolean processed = false;  //布尔变量记录 记录是否被处理过


            @Override
            public void initialize(InputSplit inputSplit, TaskAttemptContext taskAttemptContext) throws IOException, InterruptedException {
                fileSplit = (FileSplit) inputSplit; //将输入分片强制转换成FileSplit
                conf = taskAttemptContext.getConfiguration();   //从context获取配置信息
            }

            @Override
            public boolean nextKeyValue() throws IOException, InterruptedException {
                if(!processed){
                    byte[] contents = new byte[(int)fileSplit.getLength()];
                    Path file = fileSplit.getPath();
                    FileSystem fs =file.getFileSystem(conf);
                    FSDataInputStream in = null;
                    try {
                        in = fs.open(file);
                        org.apache.hadoop.io.IOUtils.readFully(in,contents,0,contents.length);
                        value.set(contents,0,contents.length);
                    }
                    finally {
                        org.apache.hadoop.io.IOUtils.closeStream(in);
                    }
                    processed = true;
                    return true;
                }

                return false;
            }

            @Override
            public NullWritable getCurrentKey() throws IOException, InterruptedException {
                return NullWritable.get();
            }

            @Override
            public BytesWritable getCurrentValue() throws IOException, InterruptedException {
                return value;
            }

            @Override
            public float getProgress() throws IOException, InterruptedException {
                return processed ? 1.0f:0.0f;
            }

            @Override
            public void close() throws IOException {
                //do nothing
            }
        }
    }



    //MapReduce
    public static int startMapReduce(FileSystem fs, List<String> _textClassName, List<String> _textClassInputFilePath,
                                     String _inputFilePath, String _DirPath,
                                     String _hdfsPath, String _wordCountInputPath, String _sumInputPath,
                                     String _resultPath, String _resultTempPath,String _jobName,String TrainingFiles) throws Exception{
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
        conf.set("resultPath",_resultPath);
        conf.set("resultTempPath",_resultTempPath);
        conf.set("wordCountInputPath",_wordCountInputPath);
        conf.set("sumInputPath",_sumInputPath);
        conf.set("dirPath",_DirPath);
        conf.set("hdfsPath",_hdfsPath);
        conf.set("TrainingFiles",TrainingFiles);

        //Job设置
        Job job = Job.getInstance(conf, _jobName);
        job.setJarByClass(CalculateResult.class);
        job.setMapperClass(ResultMapper.class);
        job.setReducerClass(ResultReducer.class);
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(Text.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);
        job.setNumReduceTasks(1);
        //以整个文件输入
        job.setInputFormatClass(WholeFileInputFormat.class);

        //设置输入路径
        List<Path> filePaths = new ArrayList<Path>();
        String content= IOUtils.toString(fs.open(new Path(_inputFilePath)), "UTF-8");
        StringTokenizer itr = new StringTokenizer(content,"\r\n");
        while(itr.hasMoreTokens()) {
            filePaths.add(new Path(itr.nextToken()));
        }

        //输入输出格式

        WholeFileInputFormat.setInputPaths(job, (Path[])filePaths.toArray(new Path[filePaths.size()]));
        MultipleOutputs.addNamedOutput(job,"Text", TextOutputFormat.class,Text.class,Text.class);
        LazyOutputFormat.setOutputFormatClass(job,TextOutputFormat.class);
        FileOutputFormat.setOutputPath(job, new Path(_DirPath+_resultTempPath));

        int result = job.waitForCompletion(true)?0:1;
        return result;
    }
}

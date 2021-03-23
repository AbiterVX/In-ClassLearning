import org.apache.commons.io.IOUtils;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.JobContext;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.LazyOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.MultipleOutputs;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.log4j.BasicConfigurator;

import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.*;

class EvaluationData{
    public int TP;
    public int FP;
    public int FN;
    public int TN;
    EvaluationData(){
        TP = 0;
        FP = 0;
        FN = 0;
        TN = 0;
    }
}

public class CalculateEvaluation {
    //Mapper
    public static class EvaluationMapper extends Mapper<Object, Text,IntWritable, IntWritable> {
        public String[] TextClassName;
        public String[] InputFilePath;

        private IntWritable mapperKey = new IntWritable();
        private IntWritable mapperValue  = new IntWritable(0);
        @Override
        protected void setup(Context context) throws IOException, InterruptedException {
            Configuration config = context.getConfiguration();
            TextClassName = config.get("TextClassName").split(",");
            InputFilePath = config.get("InputFilePath").split(",");
        }
        public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
            String[] token = value.toString().trim().split("\t");
            String resultFilePath = token[0];
            String resultClassName = token[1];
            //获取类别
            int originIndex = 0;
            for(int i=0;i<TextClassName.length;i++){
                if(resultFilePath.contains(TextClassName[i])){
                    originIndex = i;
                    break;
                }
            }
            int classificationIndex = 0;
            for(int i=0;i<TextClassName.length;i++){
                if(resultClassName.equals(TextClassName[i])){
                    classificationIndex = i;
                    break;
                }
            }
            //设置Context
            mapperKey.set(originIndex);
            mapperValue.set(classificationIndex);
            context.write(mapperKey, mapperValue);
        }
    }


    //Reduce
    public static class EvaluationReducer extends Reducer<IntWritable, IntWritable, Text, Text> {
        public String[] TextClassName;
        public String[] InputFilePath;
        public String dirPath;
        public String evaluationOutPutPath;
        private MultipleOutputs multipleOutputs;
        private final Text reducerValue =new Text();
        private final Text reducerKey =new Text();
        private EvaluationData[] evaluationDataArray;
        private EvaluationData sumEvaluation;
        @Override
        protected void setup(Context context) throws IOException, InterruptedException {
            multipleOutputs = new MultipleOutputs(context);
            Configuration config = context.getConfiguration();
            TextClassName = config.get("TextClassName").split(",");
            InputFilePath = config.get("InputFilePath").split(",");
            dirPath = config.get("dirPath");
            evaluationOutPutPath = config.get("evaluationOutPutPath");

            evaluationDataArray = new EvaluationData[TextClassName.length];
            for(int i=0;i<evaluationDataArray.length;i++){
                evaluationDataArray[i] = new EvaluationData();
            }
            sumEvaluation = new EvaluationData();
        }

        public void reduce(IntWritable key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
            int keyIndex = key.get();
            int valueIndex = 0;
            for (IntWritable value : values) {
                valueIndex = value.get();
                if(keyIndex == valueIndex){
                    evaluationDataArray[keyIndex].TP += 1;
                }
                else if(keyIndex != valueIndex){
                    evaluationDataArray[valueIndex].FP += 1;
                    evaluationDataArray[keyIndex].FN += 1;
                }
                /*
                if(TextClassName.length == 2){
                    if(keyIndex == 0 && valueIndex == 0){
                        sumEvaluation.TP +=1;
                    }
                    else if(keyIndex == 0 && valueIndex == 1){
                        sumEvaluation.FP +=1;
                    }
                    else if(keyIndex == 1 && valueIndex == 0){
                        sumEvaluation.FN +=1;
                    }
                    else if(keyIndex == 1 && valueIndex == 1){
                        sumEvaluation.TN +=1;
                    }
                }
                */
            }
        }

        @Override
        protected void cleanup(Context context) throws IOException, InterruptedException {
            double microAverageTP =0;
            double microAverageFP =0;
            double microAverageFN =0;
            double macroAveragePrecision =0;
            double macroAverageRecall =0;
            double macroAverageF1Score =0;

            double precision = 0;
            double recall = 0;
            double f1Score = 0;

            for(int i=0;i<evaluationDataArray.length;i++){
                //计算当前类别的：TP，FP，FN
                double TP = (double)evaluationDataArray[i].TP;
                double FP = (double)evaluationDataArray[i].FP;
                double FN = (double)evaluationDataArray[i].FN;
                //计算：precision，recall，f1Score
                precision = TP / (TP + FP);
                recall = TP / (TP + FN);
                f1Score = 2 * precision * recall / (precision + recall);
                //多分类宏平均
                macroAveragePrecision += precision;
                macroAverageRecall += recall;
                macroAverageF1Score += f1Score;
                //多分类微平均
                microAverageTP += TP;
                microAverageFP += FP;
                microAverageFN += FN;

                //输出当前类别Evaluation
                outPut("ClassName:" + TextClassName[i] +",Index:" + i,"  TP:"+ TP +"  FP:"+ FP + "  FN:"+ FN);
                outPut("    precision:",String.valueOf(precision));
                outPut("    recall:",String.valueOf(recall));
                outPut("    f1Score:",String.valueOf(f1Score));
            }

            //多分类：宏平均
            macroAveragePrecision /= evaluationDataArray.length;
            macroAverageRecall /= evaluationDataArray.length;
            macroAverageF1Score /= evaluationDataArray.length;
            //输出
            outPut("Multi-classification-Macro-Average, Total:" + String.valueOf(evaluationDataArray.length) + " Class", "  ");
            outPut("    precision:",String.valueOf(macroAveragePrecision));
            outPut("    recall:",String.valueOf(macroAverageRecall));
            outPut("    f1Score:",String.valueOf(macroAverageF1Score));

            //多分类:微平均
            precision = microAverageTP / (microAverageTP + microAverageFP);
            recall = microAverageTP / (microAverageTP + microAverageFN);
            f1Score = 2 * precision * recall / (precision + recall);
            //输出
            outPut("Multi-classification-Micro-Average, Total:" + String.valueOf(evaluationDataArray.length) + " Class",
                    "  TP:"+ microAverageTP +"  FP:"+ microAverageFP + "  FN:"+ microAverageFN );
            outPut("    precision:",String.valueOf(precision));
            outPut("    recall:",String.valueOf(recall));
            outPut("    f1Score:",String.valueOf(f1Score));
            /*
            if(TextClassName.length == 2) {
                precision = (double)sumEvaluation.TP / (double)(sumEvaluation.TP + sumEvaluation.FP);
                recall = (double)sumEvaluation.TP / (double)(sumEvaluation.TP + sumEvaluation.FN);
                f1Score = 2 * precision * recall / (precision + recall);
                //输出
                outPut("Binary-classification, Total:" + String.valueOf(evaluationDataArray.length) + " Class",
                        "  TP:"+ sumEvaluation.TP +"  FP:"+ sumEvaluation.FP + "  FN:"+ sumEvaluation.FN +"  TN:"+sumEvaluation.TN);
                outPut("    precision:",String.valueOf(precision));
                outPut("    recall:",String.valueOf(recall));
                outPut("    f1Score:",String.valueOf(f1Score));
            }
            */
        }

        private void outPut(String _key,String _value) throws IOException, InterruptedException {
            reducerKey.set(_key);
            reducerValue.set(_value);
            multipleOutputs.write("Text",reducerKey, reducerValue,dirPath+evaluationOutPutPath +"/Part");
        }
    }


    //MapReduce
    public static int startMapReduce(FileSystem fs,List<String> _textClassName,List<String> _textClassInputFilePath,
                                     String _inputFilePath, String _DirPath,
                                     String _evaluationOutPutPath,String _outputPath,String _jobName) throws Exception{
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
        conf.set("evaluationOutPutPath",_evaluationOutPutPath);
        conf.set("dirPath",_DirPath);

        //Job设置
        Job job = Job.getInstance(conf, _jobName);
        job.setJarByClass(CalculateWordCount.class);
        job.setMapperClass(EvaluationMapper.class);
        job.setReducerClass(EvaluationReducer.class);
        job.setMapOutputKeyClass(IntWritable.class);
        job.setMapOutputValueClass(IntWritable.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);
        job.setNumReduceTasks(1);


        //输入输出格式
        FileInputFormat.setInputPaths(job, _inputFilePath);
        MultipleOutputs.addNamedOutput(job,"Text",TextOutputFormat.class,Text.class,Text.class);
        LazyOutputFormat.setOutputFormatClass(job,TextOutputFormat.class);
        FileOutputFormat.setOutputPath(job, new Path(_DirPath+_outputPath));

        int result = job.waitForCompletion(true)?0:1;
        return result;
    }

}

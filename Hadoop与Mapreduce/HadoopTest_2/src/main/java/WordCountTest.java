import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.FloatWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.log4j.BasicConfigurator;

import java.io.IOException;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;
import java.util.StringTokenizer;

public class WordCountTest {
    //Mapper
    public static class TokenizerMapper extends Mapper<Object, Text, Text, IntWritable> {
        private final static IntWritable one = new IntWritable(1);
        private Text mapperKey = new Text();
        public void map(Object key, Text value, Mapper<Object, Text, Text, IntWritable>.Context context) throws IOException, InterruptedException {
            //设置Context
            StringTokenizer itr = new StringTokenizer(value.toString());
            while (itr.hasMoreTokens()) {
                mapperKey.set(itr.nextToken());
                context.write(mapperKey, one);
            }
        }
    }

    //Reduce
    public static class IntSumReducer extends Reducer<Text, IntWritable, Text, IntWritable> {
        private IntWritable result = new IntWritable();
        public void reduce(Text key, Iterable<IntWritable> values, Reducer<Text, IntWritable, Text, IntWritable>.Context context) throws IOException, InterruptedException {
            int sum = 0;
            IntWritable val;
            for (Iterator it = values.iterator(); it.hasNext(); sum += val.get()) {
                val = (IntWritable) it.next();
            }
            this.result.set(sum);
            context.write(key, this.result);
        }
    }

    //MapReduce
    public static int startMapReduce(FileSystem fs, List<String> _textClassName, List<String> _textClassInputFilePath, String _inputFilePath, String _outputFilePath, String _jobName) throws Exception {
        BasicConfigurator.configure();

        Configuration conf = new Configuration();
        conf.set("fs.hdfs.impl", "org.apache.hadoop.hdfs.DistributedFileSystem");
        Job job = Job.getInstance(conf, _jobName);
        job.setJarByClass(WordCountTest.class);
        job.setMapperClass(WordCountTest.TokenizerMapper.class);
        job.setCombinerClass(WordCountTest.IntSumReducer.class);
        job.setReducerClass(WordCountTest.IntSumReducer.class);

        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(IntWritable.class);
        FileInputFormat.addInputPath(job, new Path(_inputFilePath));
        FileOutputFormat.setOutputPath(job, new Path(_outputFilePath));

        int result = job.waitForCompletion(true) ? 0 : 1;
        return result;
    }

}
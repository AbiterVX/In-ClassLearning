import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.*;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.*;


public class Classification {

    //初始化
    private static void init(FileSystem fs, String _workDirName) throws IOException {
        //创建工作目录
        if(fs.exists(new Path(_workDirName))){
            fs.delete(new Path(_workDirName),true);
        }
        fs.mkdirs(new Path(_workDirName));
    }
    //随机抽取文件，分为测试集与训练集
    private static boolean partFiles(FileSystem fs,List<String> _inputFilePath, String _trainingFilePath, String _testingFilePath) throws IOException, URISyntaxException {
        //测试集占比
        float partRatio = 0.8f;
        //测试集与训练集的文件名
        Vector<String> trainingFileName = new Vector<>();
        Vector<String> testingFileName = new Vector<>();

        //读取文件，随机shuffle并抽取占比的文件作为训练集
        for(int i=0;i<_inputFilePath.size();i++){
            Path folderPath = new Path(_inputFilePath.get(i));
            if (fs.exists(folderPath)){
                FileStatus[] fileStatus = fs.listStatus(folderPath);
                List<FileStatus> files =Arrays.asList(fileStatus) ;
                Collections.shuffle(files);
                for(int j=0;j<files.size();j++){
                    if(j<= (int)((float)files.size()*partRatio) -1 ){
                        trainingFileName.add(files.get(j).getPath().toUri().toString());
                    }
                    else{
                        testingFileName.add(files.get(j).getPath().toString());
                    }
                }
            }
            else{
                return false;
            }
        }

        //----------测试输出
        System.out.println("----------trainingFileName");
        for(int i=0;i<trainingFileName.size();i++){
            System.out.println(trainingFileName.get(i).toString());
        }
        System.out.println("----------testingFileName");
        for(int i=0;i<testingFileName.size();i++){
            System.out.println(testingFileName.get(i).toString());
        }
        System.out.println("----------End");



        //写入文件
        FSDataOutputStream outputStream = null;
        //-----训练集
        if(fs.exists(new Path(_trainingFilePath))){
            fs.delete(new Path(_trainingFilePath),true);
        }
        outputStream = fs.create(new Path(_trainingFilePath));
        for(int i=0;i<trainingFileName.size();i++){
            outputStream.write((trainingFileName.get(i).toString() +"\r\n").getBytes());
        }
        outputStream.close();

        //-----测试集
        if(fs.exists(new Path(_testingFilePath))){
            fs.delete(new Path(_testingFilePath),true);
        }
        outputStream = fs.create(new Path(_testingFilePath));
        for(int i=0;i<testingFileName.size();i++){
            outputStream.write((testingFileName.get(i).toString() +"\r\n").getBytes());
        }
        outputStream.close();


        return true;
    }

    //是否继续
    public static void ifContinue(int mapreduceResult){
        if(mapreduceResult !=0){
            System.exit(mapreduceResult);
        }
    }

    //Main
    public static void main(String[] args) throws Exception {
        Config config = new Config();
        FileSystem fs = FileSystem.get(new URI(config.getHdfsPath()),new Configuration());
        init(fs,config.getDirPath());

        //配置信息
        List<String> TextClassName = config.getTextClassName();
        List<String> InputFilePath = config.getInputFilePath();
        String DirPath = config.getDirPath();
        String TrainingFiles = config.getOutputPath("TrainingFiles");
        String TestingFiles = config.getOutputPath("TestingFiles");
        String tempPath = config.getOutputName("TempPath");
        String HdfsPath = config.getHdfsPath();
        String _wordCountInputPath = config.getOutputPath("TrainingWordCount");
        String _sumInputPath = config.getOutputPath("TrainingSum");
        String TrainingWordCount = config.getOutputName("TrainingWordCount");
        String TrainingSum = config.getOutputName("TrainingSum");
        String TestingResult = config.getOutputName("TestingResult");
        String TestingResultFilePath = config.getOutputPath("TestingResult") +"/Part-r-00000";
        String EvaluationOutPutPath = config.getOutputName("TestingEvaluation");


        //划分文件：训练集与测试集
        partFiles(fs,config.getInputFilePath(),TrainingFiles,TestingFiles);

        //统计单词次数
        CalculateWordCount.startMapReduce(fs,TextClassName,InputFilePath,TrainingFiles,DirPath,tempPath,TrainingWordCount,TrainingSum,"Job_CalculateWordCount");

        //测试集统计结果
        CalculateResult.startMapReduce(fs,TextClassName,InputFilePath,TestingFiles,DirPath,HdfsPath,_wordCountInputPath,_sumInputPath,TestingResult,tempPath,"Job_CalculateResult",TrainingFiles);

        //评价Evaluation
        CalculateEvaluation.startMapReduce(fs,TextClassName,InputFilePath, TestingResultFilePath,DirPath, EvaluationOutPutPath,EvaluationOutPutPath, "CalculateEvaluation");


    }
}

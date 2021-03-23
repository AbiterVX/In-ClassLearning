import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import org.apache.commons.io.FileUtils;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;


public class Config {
    private JSONObject jsonObject;
    public Config() throws IOException {
        String path = System.getProperty("user.dir");
        File file=new File(path,"ConfigInformation");
        String content = FileUtils.readFileToString(file, "UTF-8");
        jsonObject = JSONObject.parseObject(content);
    }

    private static String txt2String(File file){
        StringBuilder result = new StringBuilder();
        try{
            BufferedReader br = new BufferedReader(new FileReader(file));//构造一个BufferedReader类来读取文件
            String s = null;
            while((s = br.readLine())!=null){//使用readLine方法，一次读一行
                result.append(System.lineSeparator()+s);
            }
            br.close();
        }catch(Exception e){
            e.printStackTrace();
        }
        return result.toString();
    }

    //获取所有的文本类别
    public List<String> getTextClassName(){
        return getStringList(jsonObject,"TextClassName");
    }

    //获取所有的文本输入路径（目录）
    public List<String> getInputFilePath(){
        return getStringList(jsonObject,"InputFilePath");
    }

    //获取输出文件目录
    public String getOutputPath(String _name){
        JSONObject outputPathJsonObject = getJsonObject(jsonObject,"OutputPath");
        String outputPath = getDirPath() + getStringValue(outputPathJsonObject,_name);
        return outputPath;
    }
    public String getOutputName(String _name){
        JSONObject outputPathJsonObject = getJsonObject(jsonObject,"OutputPath");
        String outputPath = getStringValue(outputPathJsonObject,_name);
        return outputPath;
    }

    //获取HDFS路径前缀
    public String getHdfsPath(){
        return getStringValue(jsonObject,"HdfsAddress");
    }

    //获取文件存放路径（Mapreduce生成文件，中间生成的文件）
    public String getDirPath(){
        return getStringValue(jsonObject,"DirPath");
    }
    //---------- ----------
    //根据Key获取JSONObject的String值
    public static String getStringValue(JSONObject _jsonObject,String _key){
        String value = _jsonObject.getString(_key);
        return value;
    }

    //根据Key获取JSONObject的String数组
    public static List<String> getStringList(JSONObject _jsonObject,String _key){
        List<String> stringList = JSON.parseArray(_jsonObject.getJSONArray(_key).toJSONString(),String.class);
        return stringList;
    }

    //根据Key获取JSONObject的JSONObject数组
    public static JSONObject getJsonObject(JSONObject _jsonObject,String _key){
        JSONObject jsonObject = _jsonObject.getJSONObject(_key);
        return jsonObject;
    }
}

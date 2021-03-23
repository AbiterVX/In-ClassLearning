import org.apache.hadoop.io.ArrayWritable;
import org.apache.hadoop.io.IntWritable;

public class IntArrayWritable extends ArrayWritable {
    public int length;
    public IntArrayWritable(int[] values) {
        super(IntWritable.class);
        IntWritable[] newValues = new IntWritable[values.length];
        for (int i = 0; i < newValues.length; i++) {
            newValues[i] = new IntWritable(values[i]);
        }
        set(newValues);
        length = values.length;
    }
}

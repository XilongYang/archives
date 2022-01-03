package data;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Record {
    public Record(int s) {
        score = s;
        SimpleDateFormat sdf = new SimpleDateFormat();
        sdf.applyPattern("yyyy-MM-dd HH:mm:ss");
        date = sdf.format(new Date());
    }
    public String GetScoreText() {
        return score + "";
    }
    public String GetDate() {
        return date;
    }
    public int GetScore() {
        return score;
    }
    public void Write(ObjectOutputStream out) throws IOException {
        out.writeObject(score);
        out.writeObject(date);
    }
    public void Read(ObjectInputStream in) throws IOException, ClassNotFoundException {
        score = (int) in.readObject();
        date = (String) in.readObject();
    }
    private int score;
    private String date;
}

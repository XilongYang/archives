package ui;

import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;

public class BGM {
    private BGM() {
        bgPlayer.setCycleCount(MediaPlayer.INDEFINITE);
        bgPlayer.play();
    }
    public static BGM GetInstance() {
        return instance;
    }
    public void Play() {
        bgPlayer.play();
    }
    public void Pause() {
        bgPlayer.pause();
    }
    private final String filePath
        = this.getClass().getClassLoader().getResource("dango.mp3").toExternalForm();
    private final MediaPlayer bgPlayer = new MediaPlayer(new Media(filePath));
    private static final BGM instance = new BGM();
}

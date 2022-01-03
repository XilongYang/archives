package sprite.dango;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.util.Duration;

class DangoMove extends DangoState {
    public DangoMove() {
        display = new ImageView();
        display.setImage(frames[curFrame]);
        display.setFitWidth(256);
        display.setFitHeight(256);
        animation = new Timeline(new KeyFrame(Duration.millis(250), e->ChangeFrame()));
        animation.setCycleCount(Timeline.INDEFINITE);
        animation.setRate(1);
        animation.play();
    }
    void ChangeFrame() {
        curFrame = (curFrame + 1) % frames.length;
        display.setImage(frames[curFrame]);
    }
    private final Image[] frames = {
            new Image("dango/move-0.png"),
            new Image("dango/move-1.png"),
    };
    private int curFrame = 0;
}
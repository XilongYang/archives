package sprite.dango;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.util.Duration;

class DangoIdle extends DangoState {
    DangoIdle() {
        display = new ImageView();
        display.setImage(frames[curFrame]);
        display.setFitWidth(128);
        display.setFitHeight(128);
        animation = new Timeline(new KeyFrame(Duration.millis(250), e->ChangeFrame()));
        animation.setCycleCount(Timeline.INDEFINITE);
        animation.play();
    }
    private void ChangeFrame() {
        curFrame = (curFrame + 1) % frames.length;
        display.setImage(frames[curFrame]);
    }
    private final Image[] frames = {
            new Image("dango/stand-0.png"),
            new Image("dango/stand-1.png"),
            new Image("dango/stand-2.png"),
            new Image("dango/stand-3.png")
    };
    protected int curFrame = 0;
}


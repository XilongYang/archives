package sprite.dango;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.util.Duration;

class DangoJump extends DangoState {
    DangoJump() {
        display = new ImageView();
        display.setImage(frames[curFrame]);
        display.setFitWidth(256);
        display.setFitHeight(256);
        animation = new Timeline(new KeyFrame(Duration.millis(125), a->ChangeFrame()));
        animation.setCycleCount(frames.length);
        animation.setRate(1);
        animation.play();
    }
    void ChangeFrame() {
        curFrame = (curFrame + 1) % frames.length;
        display.setImage(frames[curFrame]);
    }
    private final Image[] frames = {
            new Image("dango/jump-1.png"),
            new Image("dango/jump-2.png"),
            new Image("dango/jump-3.png"),
            new Image("dango/jump-3.png"),
            new Image("dango/jump-4.png"),
            new Image("dango/jump-5.png"),
            new Image("dango/jump-6.png"),
    };
    private int curFrame = 0;
}
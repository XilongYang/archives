package sprite;

import javafx.animation.Interpolator;
import javafx.animation.TranslateTransition;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.util.Duration;
import control.AnimationControl;

public class Road extends AnimationControl {
    public Road() {
        display = new ImageView(new Image("road.png"));
        display.setFitHeight(96);
        TranslateTransition tt = new TranslateTransition();
        tt.setNode(display);
        tt.setDuration(Duration.millis(3200));
        tt.setInterpolator(Interpolator.LINEAR);
        tt.setFromX(683);
        tt.setFromY(3);
        tt.setToX(-683);
        tt.setCycleCount(TranslateTransition.INDEFINITE);
        tt.play();
        animation = tt;
    }
}

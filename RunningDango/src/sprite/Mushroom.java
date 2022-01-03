package sprite;

import javafx.animation.Interpolator;
import javafx.animation.TranslateTransition;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.util.Duration;
import control.AnimationControl;

public class Mushroom extends AnimationControl {
    public Mushroom() {
        display = new ImageView(mushrooms[0]);
        display.setFitHeight(108);
        display.setFitWidth(108);
        display.setLayoutX(300);
        TranslateTransition tt = new TranslateTransition();
        tt.setDuration(Duration.millis(4000));
        tt.setNode(display);
        tt.setFromX(1100);
        tt.setFromY(600);
        tt.setToX(-600);
        tt.setInterpolator(Interpolator.LINEAR);
        tt.setAutoReverse(false);
        tt.setOnFinished(e->{
            ChangeImage();
            tt.playFromStart();
        });
        animation = tt;
    }
    private void ChangeImage() {
        int i = (int)(System.currentTimeMillis() % mushrooms.length);
        display.setImage(mushrooms[i]);
    }
    private final Image[] mushrooms = {
            new Image("mushroom0.png"),
            new Image("mushroom1.png"),
            new Image("mushroom2.png")
    };
}

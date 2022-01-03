package sprite.dango;

import javafx.animation.Animation;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.image.ImageView;
import control.AnimationControl;

public abstract class DangoState extends AnimationControl {
    public ImageView GetImageView() {
        return display;
    }
    public Animation GetAnimation() {
        return animation;
    }
    public void SetOnFinished(EventHandler<ActionEvent> a) {
        animation.setOnFinished(a);
    }
}
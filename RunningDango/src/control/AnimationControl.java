package control;

import javafx.animation.Animation;
import javafx.scene.image.ImageView;

public abstract class AnimationControl {
    public void SetRate(double r) {
        animation.setRate(r);
    }
    public void Pause() {
        animation.pause();
    }
    public void Resume() {
        animation.play();
    }
    public void Reset() {
        animation.setRate(1);
        animation.stop();
    }

    public double GetPos() {
        return display.getLocalToSceneTransform().getTx();
    }
    public ImageView GetImageView() {
        return display;
    }
    protected Animation animation;
    protected ImageView display;
}
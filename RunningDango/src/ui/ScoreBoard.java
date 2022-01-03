package ui;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.control.Label;
import javafx.scene.text.Font;
import javafx.util.Duration;
import control.AnimationControl;

public class ScoreBoard extends AnimationControl {
    public ScoreBoard() {
        display = new Label("Score:");
        display.setFont(Font.font("JetBrains Mono", 50));
        score = 0;
        animation = new Timeline(
                new KeyFrame(Duration.millis(125), e->timeAdd()));
        animation.setCycleCount(Timeline.INDEFINITE);
        animation.play();
    }
    public Label GetLabel() {
        return display;
    }
    @Override
    public void Reset() {
        score = 0;
        animation.stop();
    }
    private void timeAdd() {
        display.setText("Score: " + score);
        ++score;
    }
    static public int GetScore() {
        return score;
    }
    private Label display;
    static private Integer score;
}

package control;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.beans.property.BooleanProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.util.Duration;
import ui.ScoreBoard;

import java.io.IOException;


public class CollisionDetector{
    static public CollisionDetector GetInstance() {
        if(instance == null) {
            instance = new CollisionDetector();
        }
        return instance;
    }
    private CollisionDetector(){
        running = new SimpleBooleanProperty(false);
        unlocked= new SimpleBooleanProperty(true);
        checker = new Timeline(new KeyFrame(Duration.millis(20), e->{
            LogicControl.RequestFocus();
            if(!running.getValue() || animations == null){
                return;
            }
            double curRate = 1 + ScoreBoard.GetScore() / 1000.0;
            LogicControl.GetInstance().SetAnimationRate(curRate);
            if(!unlocked.getValue()) {
                return;
            }
            for(int i = 0; i < animations.length; ++i) {
                for(int j = i + 1; j < animations.length; ++j) {
                    double pos1X = animations[i].GetPos();
                    double pos2X = animations[j].GetPos();
                    if(Math.abs(pos1X - pos2X)< 100) {
                        LogicControl.TouchMushroom();
                    }
                }
            }
        }));
        checker.setCycleCount(Timeline.INDEFINITE);
        checker.play();
    }
    public void Add(AnimationControl a) {
        if(animations == null) {
            animations = new AnimationControl[1];
            animations[0] = a;
        } else {
            AnimationControl[] tmp = new AnimationControl[animations.length + 1];
            for(int i = 0; i < animations.length; ++i) {
                tmp[i] = animations[i];
            }
            tmp[tmp.length - 1] = a;
            animations = tmp;
        }
    }
    public void Run() {
        running.setValue(true);
    }
    public void Stop() {
        running.setValue(false);
    }
    public void BindRunningTo(BooleanProperty aim) {
        unlocked.bind(aim);
    }
    Timeline checker;
    SimpleBooleanProperty running;
    SimpleBooleanProperty unlocked;
    private AnimationControl[] animations;
    static private CollisionDetector instance;
}

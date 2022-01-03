package control;

import data.Record;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import sprite.dango.Dango;
import ui.*;

public class LogicControl {
    private LogicControl() {
        paused = false;
    }
    static public LogicControl GetInstance() {
        if(instance == null) {
            instance = new LogicControl();
        }
        return instance;
    }
    static public EventHandler<ActionEvent> GetStartEvent() {
        return e->{
            instance.stage.setScene(instance.game);
            instance.Reset();
            instance.Resume();
            CollisionDetector.GetInstance().Run();
        };
    }
    static public EventHandler<ActionEvent> GetHowToEvent(Text howto) {
        return e-> {
            if(howto.isVisible()) {
                howto.setVisible(false);
            } else {
                howto.setVisible(true);
            }
        };
    }
    static public EventHandler<ActionEvent> GetMuteEvent(StandardButton mute) {
        return e->{
            if(mute.getText().equals("Music: ON")) {
                BGM.GetInstance().Pause();
                mute.setText("Music: OFF");
            } else {
                BGM.GetInstance().Play();
                mute.setText("Music: ON");
            }
        };
    }
    static public EventHandler<ActionEvent> GetExitEvent() {
        return e->System.exit(0);
    }
    static public EventHandler<KeyEvent> GetGamingLogic(Dango dango) {
        return e->{
            boolean paused = instance.paused;
            if(e.getCode() == KeyCode.SPACE && !paused && dango.Unlocked().getValue()) {
                dango.Jump();
            }
            if(e.getCode() == KeyCode.P) {
                if(paused){
                    instance.Resume();
                } else {
                    instance.Pause();
                }
            }
            if(e.getCode() == KeyCode.BACK_SPACE) {
                instance.stage.setScene(instance.menu);
                instance.Reset();
            }
        };
    }
    static public EventHandler<ActionEvent> GetMainMenuEvent() {
        return e-> {
            instance.stage.setScene(instance.menu);
            instance.Reset();
        };
    }
    static public EventHandler<ActionEvent> GetHighScoreEvent() {
        return e-> {
            instance.stage.setScene(instance.highScore);
            instance.Reset();
        };
    }

    static public void TouchMushroom() {
        instance.highScore.AddRecord(new Record(ScoreBoard.GetScore()));
        instance.highScore.Update();
        instance.Pause();
        instance.over.SetScore(ScoreBoard.GetScore());
        instance.stage.setScene(instance.over);
        CollisionDetector.GetInstance().Stop();
        instance.Reset();
    }
    static public void RequestFocus(){
        instance.game.RequestFocus();
    }

    public void SetAnimationRate(double r) {
        for(AnimationControl a : animations) {
            a.SetRate(r);
        }
    }
    private void Reset() {
        for(AnimationControl a : animations) {
            a.Reset();
        }
    }
    private void Pause() {
        paused = true;
        for(AnimationControl a : animations) {
            a.Pause();
        }
        if(game == null) {
            return;
        }
        game.ShowPauseLabel();
        CollisionDetector.GetInstance().Stop();
    }
    private void Resume() {
        paused = false;
        for(AnimationControl a : animations) {
            a.Resume();
        }
        game.HiddenPauseLabel();
        CollisionDetector.GetInstance().Run();
    }

    public void SetStage(Stage primary) {
        stage = primary;
    }
    public void SetMainScene(WelcomeScene main) {
        menu = main;
    }
    public void SetGamingScene(GamingScene gaming) {
        game = gaming;
    }
    public void SetOverScene(OverScene gameOver) {
        over = gameOver;
    }
    public void SetHighScoreScene(HighScoreScene highScoreScene) {
        highScore = highScoreScene;
    }
    public void SetAnimationControls(AnimationControl... animation) {
        animations = animation;
        Reset();
    }

    private Stage stage;
    private WelcomeScene menu;
    private GamingScene game;
    private OverScene over;
    private HighScoreScene highScore;
    private AnimationControl[] animations;
    private boolean paused;
    static private LogicControl instance = new LogicControl();
}

package sprite.dango;

import control.AnimationControl;
import control.CollisionDetector;
import javafx.beans.property.BooleanProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.geometry.Pos;
import javafx.scene.layout.GridPane;

public class Dango extends AnimationControl {
    public Dango(GridPane pane) {
        grid = pane;
        grid.setAlignment(Pos.TOP_LEFT);
        grid.setHgap(100);
        grid.setVgap(500);
        state = new DangoMove();
        animation = state.GetAnimation();
        display = state.GetImageView();
        stateUnlocked = new SimpleBooleanProperty(true);
        grid.add(state.GetImageView(), 1, 1);
        CollisionDetector.GetInstance().BindRunningTo(stateUnlocked);
    }
    public void Idle() {
        grid.getChildren().remove(state.GetImageView());
        state = new DangoIdle();
        animation = state.GetAnimation();
        display = state.GetImageView();
        grid.add(state.GetImageView(), 1, 1);
    }

    public void Move() {
        stateUnlocked.setValue(true);
        grid.getChildren().remove(state.GetImageView());
        state = new DangoMove();
        animation = state.GetAnimation();
        display = state.GetImageView();
        grid.add(state.GetImageView(), 1, 1);
    }

    public void Jump() {
        stateUnlocked.setValue(false);
        grid.getChildren().remove(state.GetImageView());
        state = new DangoJump();
        animation = state.GetAnimation();
        display = state.GetImageView();
        grid.add(state.GetImageView(), 1, 1);
        state.SetOnFinished(e->Move());
    }

    public void Reset() {
        grid.getChildren().remove(state.GetImageView());
        state = new DangoMove();
        animation = state.GetAnimation();
        display = state.GetImageView();
        grid.add(state.GetImageView(), 1, 1);
    }

    public SimpleBooleanProperty Unlocked() {
        return stateUnlocked;
    }

    private DangoState state;
    private final GridPane grid;
    private SimpleBooleanProperty stateUnlocked;
}

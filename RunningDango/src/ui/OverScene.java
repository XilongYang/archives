package ui;

import control.LogicControl;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.text.Font;

public class OverScene extends Scene{
    public OverScene(StackPane stack, double width, double height) {
        super(stack, width, height);
        pane = stack;

        SetBackgroundImage(new Image("over.jpg"));
        SetUpScoreLabel();
        SetUpButtons();
    }

    public void SetBackgroundImage(Image img) {
        if(bgView == null) {
            bgView = new ImageView();
        }
        bgView.setImage(img);
        pane.getChildren().add(bgView);
        bgView.setFitWidth(pane.getWidth());
        bgView.setFitHeight(pane.getHeight());
    }

    public void SetScore(int s) {
        finalScore.setText("You Score: " + s);
    }

    private void SetUpScoreLabel() {
        GridPane labelGrid = new GridPane();
        pane.getChildren().add(labelGrid);
        labelGrid.setAlignment(Pos.TOP_CENTER);
        labelGrid.setPadding(new Insets(100));
        finalScore.setFont(Font.font("JetBrains Mono", 50));
        labelGrid.add(finalScore, 0, 0);
    }

    private void SetUpButtons() {
        StandardButton retryButton = new StandardButton("Retry"
                , LogicControl.GetStartEvent());
        StandardButton backButton = new StandardButton("Main Menu"
                , LogicControl.GetMainMenuEvent());
        StandardButton highButton = new StandardButton("High Score"
                , LogicControl.GetHighScoreEvent());
        pane.getChildren().add(new ButtonPane(Pos.CENTER, 0, 0
                , retryButton, backButton, highButton));
    }

    private StackPane pane;
    private ImageView bgView;
    private Label finalScore = new Label();
}

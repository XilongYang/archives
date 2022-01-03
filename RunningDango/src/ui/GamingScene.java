package ui;

import control.CollisionDetector;
import control.LogicControl;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.effect.DropShadow;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.text.Font;
import sprite.Mushroom;
import sprite.Road;
import sprite.dango.Dango;

public class GamingScene extends Scene{
    public GamingScene(StackPane stack, double width, double height) {
        super(stack, width, height);
        pane = stack;
        pane.setAlignment(Pos.CENTER);

        DropShadow ds = new DropShadow();
        ds.setOffsetY(2.0);

        SetBackgroundImage(new Image("background.png"));
        SetUpRoad();
        SetUpMushroom();
        SetUpPauseLabel();
        SetUpScoreBoard();
        SetUpDango();
        LogicControl.GetInstance().SetAnimationControls(road, mushroom, scoreBoard, dango);
        CollisionDetector.GetInstance().Add(mushroom);
        CollisionDetector.GetInstance().Add(dango);
    }
    public void RequestFocus() {
        dango.GetImageView().requestFocus();
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
    public void ShowPauseLabel() {
        pauseLabel.setVisible(true);
    }
    public void HiddenPauseLabel() {
        pauseLabel.setVisible(false);
    }
    private void SetUpRoad() {
        GridPane roadGrid = new GridPane();
        pane.getChildren().add(roadGrid);
        roadGrid.setAlignment(Pos.BOTTOM_CENTER);
        road = new Road();
        roadGrid.add(road.GetImageView(), 0, 0);
    }
    private void SetUpMushroom() {
        AnchorPane mushroomPane = new AnchorPane();
        pane.getChildren().add(mushroomPane);
        mushroom = new Mushroom();
        mushroomPane.getChildren().add(mushroom.GetImageView());
    }
    private void SetUpScoreBoard() {
        scoreBoard = new ScoreBoard();
        GridPane labelGrid = new GridPane();
        pane.getChildren().add(labelGrid);
        labelGrid.setAlignment(Pos.TOP_RIGHT);
        labelGrid.setPadding(new Insets(30));
        labelGrid.add(scoreBoard.GetLabel(), 0, 0);
    }
    private void SetUpPauseLabel() {
        pauseLabel = new Label("Paused");
        pauseLabel.setFont(Font.font(32));
        pauseLabel.setVisible(false);
        pane.getChildren().add(pauseLabel);
    }
    private  void SetUpDango() {
        GridPane dangoGrid = new GridPane();
        pane.getChildren().add(dangoGrid);
        dango = new Dango(dangoGrid);
        pane.setOnKeyPressed(LogicControl.GetGamingLogic(dango));
    }
    private final StackPane pane;
    private ImageView bgView;
    private Road road;
    private Mushroom mushroom;
    private ScoreBoard scoreBoard;
    private Label pauseLabel;
    private Dango dango;
}

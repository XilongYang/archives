package ui;

import control.LogicControl;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.effect.DropShadow;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import sprite.dango.Dango;

public class WelcomeScene extends Scene{
    public WelcomeScene(StackPane stack, double width, double height) {
        super(stack, width, height);
        pane = stack;
        pane.setAlignment(Pos.CENTER);

        ds = new DropShadow();
        ds.setOffsetY(2.0);

        SetBackgroundImage(new Image("welcome.jpg"));
        SetTitle("Running Dango");
        SetUpDango();
        SetUpHowTo();
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
    public void SetTitle(String t) {
        if (title == null) {
            title = new Text();
            title.setFont(new Font("JetBrains Mono", 72));
            title.setFill(Color.rgb(240, 200, 100));
            title.setEffect(ds);
            title.setCache(true);
            title.setScaleX(1.5);
            title.setScaleY(1.5);
        }
        if (titleGrid == null) {
            titleGrid = new GridPane();
            pane.getChildren().add(titleGrid);
            titleGrid.setAlignment(Pos.TOP_CENTER);
            titleGrid.setVgap(180);
            titleGrid.add(title, 0, 1);
        }
        title.setText(t);
    }
    private void SetUpDango() {
        GridPane dangoGrid = new GridPane();
        pane.getChildren().add(dangoGrid);
        Dango welcomeDango = new Dango(dangoGrid);
        dangoGrid.setAlignment(Pos.TOP_CENTER);
        dangoGrid.setVgap(85);
        dangoGrid.setHgap(-250);
        welcomeDango.Idle();
    }
    private void SetUpHowTo() {
        AnchorPane howtoPane = new AnchorPane();
        pane.getChildren().add(howtoPane);
        howto = new Text("HOW TO PLAY\n"
                + "Help the Dango run away and avoid mushrooms.\n"
                + "Press SPACE to jump.\n"
                + "Pree P to pause/resume game.\n"
                + "Press BACKSPACE to return main menu.\n");
        howtoPane.getChildren().add(howto);
        howto.setFont(Font.font(20));
        howto.setX(880);
        howto.setY(60);
        howto.setFill(Color.rgb(255, 255, 255));
        howto.setEffect(ds);
        howto.setVisible(false);
    }
    private void SetUpButtons() {
        StandardButton startButton = new StandardButton("Start"
                , LogicControl.GetStartEvent());
        StandardButton howtoButton = new StandardButton("How to play"
                , LogicControl.GetHowToEvent(howto));
        StandardButton muteButton = new StandardButton("Music: ON", e->{});
        muteButton.setOnAction(LogicControl.GetMuteEvent(muteButton));
        StandardButton highButton = new StandardButton("High Score"
                , LogicControl.GetHighScoreEvent());
        StandardButton exitButton = new StandardButton("Exit"
                , LogicControl.GetExitEvent());
        pane.getChildren().add(new ButtonPane(Pos.TOP_CENTER, 400, 0
                , startButton, muteButton, howtoButton, highButton, exitButton));
    }

    private StackPane pane;
    private ImageView bgView;
    private DropShadow ds;
    private GridPane titleGrid;
    private Text title;
    private Text howto;
}

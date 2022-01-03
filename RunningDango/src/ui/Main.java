package ui;

import control.LogicControl;
import javafx.application.Application;
import javafx.scene.image.Image;
import javafx.scene.layout.*;
import javafx.stage.Stage;

import java.io.UnsupportedEncodingException;

public class Main extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception{
        final int WINDOW_WIDTH  = 1366;
        final int WINDOW_HEIGHT = 768;

        path = GetPath();

        LogicControl control = LogicControl.GetInstance();
        control.SetStage(primaryStage);

        WelcomeScene welcomeScene = new WelcomeScene(
                new StackPane(), WINDOW_WIDTH, WINDOW_HEIGHT);
        control.SetMainScene(welcomeScene);

        GamingScene gameingScene = new GamingScene(
                new StackPane(), WINDOW_WIDTH, WINDOW_HEIGHT);
        control.SetGamingScene(gameingScene);

        OverScene overScene = new OverScene(
                new StackPane(), WINDOW_WIDTH, WINDOW_HEIGHT);
        control.SetOverScene(overScene);

        HighScoreScene highScoreScene = new HighScoreScene(
                new StackPane() , WINDOW_WIDTH, WINDOW_HEIGHT);
        control.SetHighScoreScene(highScoreScene);

        BGM.GetInstance().Play();

        primaryStage.getIcons().add(new Image("icon.jpg"));
        primaryStage.setTitle("Dango");
        primaryStage.setScene(welcomeScene);
        primaryStage.setResizable(false);
        primaryStage.show();
    }
    private String GetPath()
    {
        String path = this.getClass().getProtectionDomain().getCodeSource().getLocation().getPath();
        if(System.getProperty("os.name").contains("dows"))
        {
            path = path.substring(1,path.length());
            try {
                path = java.net.URLDecoder.decode(path, "utf-8");
            } catch (UnsupportedEncodingException ue) {
                System.out.println(ue.getMessage());
            }
        }
        if(path.contains("jar"))
        {
            path = path.substring(0,path.lastIndexOf("."));
            return path.substring(0,path.lastIndexOf("/") + 1);
        }
        return path.replace("target/classes/", "");
    }
    static public String path;
}
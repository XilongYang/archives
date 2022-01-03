package ui;

import control.LogicControl;
import data.Record;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.text.Font;
import javafx.scene.text.Text;

import java.io.*;
import java.util.ArrayList;

public class HighScoreScene extends Scene{
    public HighScoreScene(StackPane stack, double width, double height) {
        super(stack, width, height);
        pane = stack;

        SetBackgroundImage(new Image("highscore.jpg"));
        SetTitle("High Score");
        SetUpScoreBoard();
        SetUpButtons();

        if(CheckFile()) {
            ReadFile();
        }
    }
    public void Update() {
        records.sort((a, b)->{
            if(a.GetScore() < b.GetScore()) {
                return 1;
            } else if(a.GetScore() == b.GetScore()) {
                return 0;
            } else {
                return -1;
            }
        });
        for(int i = 0; i < 15; ++i) {
            if(i >= records.size()) {
                highScores[i].setText("--");
                times[i].setText("--");
            }
            else{
                highScores[i].setText(records.get(i).GetScoreText());
                times[i].setText(records.get(i).GetDate());
            }
        }
        WriteFile();
    }
    public void AddRecord(Record r) {
        records.sort((a, b)->{
            if(a.GetScore() < b.GetScore()) {
                return 1;
            } else if(a.GetScore() == b.GetScore()) {
                return 0;
            } else {
                return -1;
            }
        });
        if(records.size() < 15) {
            records.add(r);
        } else if(records.get(records.size() - 1).GetScore() < r.GetScore())
        {
            records.remove(records.size() - 1);
            records.add(r);
        }
    }
    public void SetTitle(String t) {
        if (title == null) {
            title = new Text();
            title.setFont(new Font("JetBrains Mono", 32));
            title.setCache(true);
            title.setScaleX(1.5);
            title.setScaleY(1.5);
        }
        if (titleGrid == null) {
            titleGrid = new GridPane();
            pane.getChildren().add(titleGrid);
            titleGrid.setAlignment(Pos.TOP_CENTER);
            titleGrid.setVgap(50);
            titleGrid.add(title, 0, 1);
        }
        title.setText(t);
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

    private void SetUpButtons() {
        StandardButton backButton = new StandardButton("Main Menu"
                , LogicControl.GetMainMenuEvent());
        pane.getChildren().add(new ButtonPane(Pos.CENTER, 600, 0
                , backButton));
    }
    private void SetUpScoreBoard() {
        if(scoreGrid == null) {
            final String longSpace = "                ";
            scoreGrid = new GridPane();
            pane.getChildren().add(scoreGrid);
            scoreGrid.setAlignment(Pos.CENTER);
            scoreGrid.setGridLinesVisible(true);
            Label no = new Label("  No.  ");
            no.setFont(Font.font(24));
            Label score = new Label(longSpace + "Score" + longSpace);
            score.setFont(Font.font(24));
            Label time = new Label(longSpace + "Time" + longSpace);
            time.setFont(Font.font(24));
            scoreGrid.addRow(0, no, score, time);
            for(int i = 1; i <= 15; ++i) {
                Label tmp = new Label( i + ". ");
                tmp.setFont(Font.font(24));
                scoreGrid.add(tmp, 0, i);
                highScores[i - 1] = new Label("--");
                highScores[i - 1].setFont(Font.font(24));
                scoreGrid.add(highScores[i - 1],1,i);
                times[i - 1] = new Label("--");
                times[i - 1].setFont(Font.font(24));
                scoreGrid.add(times[i - 1], 2, i);
            }
        }
    }

    private boolean CheckFile() {
        try{
            new FileInputStream(filePath);
        } catch (FileNotFoundException f) {
            System.out.println("Create new highscore.dat");
            try {
                new FileOutputStream(filePath);
                return false;
            } catch (FileNotFoundException of) {
                System.out.println(of.getMessage());
                System.exit(-1);
            }
        }
        return true;
    }
    private void ReadFile() {
        try (ObjectInputStream input =
                     new ObjectInputStream(new FileInputStream(filePath))) {
            int size = input.read();
            for(int i = 0; i < size; ++i) {
                records.add(new Record(0));
                try {
                    records.get(i).Read(input);
                } catch (ClassNotFoundException c) {
                    System.out.println("Class Not Found");
                    System.exit(-1);
                }
                highScores[i].setText(records.get(i).GetScoreText());
                times[i].setText(records.get(i).GetDate());
            }
        } catch (IOException e) {
        }
    }
    private void WriteFile() {
        try (ObjectOutputStream output =
                     new ObjectOutputStream(new FileOutputStream(filePath, false))){
            output.write(records.size());
            for(Record r : records) {
                r.Write(output);
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
            System.exit(-1);
        }
    }

    private final StackPane pane;
    private ImageView bgView;
    private Text title;
    private GridPane titleGrid;
    private GridPane scoreGrid;
    private final Label[] highScores = new Label[15];
    private final Label[] times = new Label[15];
    private final ArrayList<Record> records = new ArrayList<>();
    private final String filePath = Main.path + "highscore.dat";
}

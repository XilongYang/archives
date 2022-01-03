package ui;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;
import javafx.scene.text.Font;


public class StandardButton extends Button{
    StandardButton(String text, EventHandler<ActionEvent> a) {
        this.setText(text);
        this.setPrefSize(200,36);
        this.setFont(Font.font(20));
        this.setOnAction(a);
    }
}

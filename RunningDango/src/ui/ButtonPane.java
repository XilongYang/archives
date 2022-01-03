package ui;

import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;

public class ButtonPane extends GridPane{
    ButtonPane(Pos pos, double Vgap, double Hgap, Button... buttons) {
        this.setAlignment(pos);
        this.setVgap(Vgap);
        this.setHgap(Hgap);
        VBox buttonBox= new VBox();
        this.add(buttonBox, 1, 1);
        buttonBox.setAlignment(Pos.CENTER);
        buttonBox.setSpacing(15);
        for(Button b : buttons) {
            buttonBox.getChildren().add(b);
        }
    }
}

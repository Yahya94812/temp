import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;

public class CalculatorApplet extends Applet implements ActionListener {
TextField num1Field, num2Field, resultField;
    Button addButton, subtractButton;

    public void init() {
        // Set layout
setLayout(new GridLayout(4, 2, 5, 5));

        // Create text fields
        num1Field = new TextField(10);
        num2Field = new TextField(10);
resultField = new TextField(10);
resultField.setEditable(false);

        // Create buttons
addButton = new Button("Add");
subtractButton = new Button("Subtract");

        // Add components to the applet
add(new Label("Number 1:"));
        add(num1Field);
add(new Label("Number 2:"));
        add(num2Field);
add(new Label("Result:"));
        add(resultField);
        add(addButton);
        add(subtractButton);

        // Add action listeners
addButton.addActionListener(this);
subtractButton.addActionListener(this);
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == addButton) {
int num1 = Integer.parseInt(num1Field.getText());
int num2 = Integer.parseInt(num2Field.getText());
            int result = num1 + num2;
resultField.setText(String.valueOf(result));
        } else if (e.getSource() == subtractButton) {
int num1 = Integer.parseInt(num1Field.getText());
int num2 = Integer.parseInt(num2Field.getText());
            int result = num1 - num2;
            resultField.setText(String.valueOf(result));
        }
    }
}



<applet code="CalculatorApplet.class" width="300" height="200"></applet>

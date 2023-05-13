package view.gui.newgame_window.result_dialog;

import scores.HighScores;
import view.gui.newgame_window.GameWindow;

import javax.swing.*;
import java.awt.*;
import java.io.*;

public class VictoryDialog extends JDialog {
    public VictoryDialog(GameWindow owner) {
        super(owner, "Game over", true);
        add(new JLabel("<html><h1>You have won!</h1>" +
                        "<h3>Now you can save your result<h3></html>"),
                        BorderLayout.CENTER);

        JButton tryAgainButton = new JButton("Try again");
        tryAgainButton.addActionListener(actionEvent -> {
            owner.dispose();
            new GameWindow(owner.getCols(), owner.getRows(), owner.getTotalBombs(), owner.getUserName());
        });

        JButton saveResultButton = new JButton("Save result");
        saveResultButton.addActionListener(actionEvent -> {
            owner.dispose();
            try {
                FileInputStream fileInputStream = new FileInputStream("C:\\Users\\osipo\\IdeaProjects\\sweeper\\src\\main\\resources\\highscores");
                ObjectInputStream objectInputStream = new ObjectInputStream(fileInputStream);
                HighScores highScores = (HighScores) objectInputStream.readObject();
                objectInputStream.close();

                highScores.add(owner.getScore());

                FileOutputStream fileOutputStream = new FileOutputStream("C:\\Users\\osipo\\IdeaProjects\\sweeper\\src\\main\\resources\\highscores");
                ObjectOutputStream objectOutputStream = new ObjectOutputStream(fileOutputStream);
                objectOutputStream.writeObject(highScores);
                objectOutputStream.close();

            } catch (IOException | ClassNotFoundException ex) {

            }
        });

        JButton closeButton = new JButton("Close");
        closeButton.addActionListener(actionEvent -> owner.dispose());

        JPanel panel = new JPanel();
        panel.add(saveResultButton);
        panel.add(tryAgainButton);
        panel.add(closeButton);
        add(panel, BorderLayout.SOUTH);
        setSize(360, 160);
        setLocationRelativeTo(null);
    }
}

package view.gui.dialogs;

import view.gui.GameWindow;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class VictoryDialog extends JDialog {
    public VictoryDialog(GameWindow owner) {
        super(owner, "Game over", true);
        add(new JLabel("<html><h1>You have won!</h1>" +
                        "<h3>Now you can save your result<h3></html>"),
                        BorderLayout.CENTER);

        JButton bTryAgain = new JButton("Try again");
        bTryAgain.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                owner.dispose();
                new GameWindow(owner.getCols(), owner.getRows(), owner.getTotalBombs(), owner.getUserName());
            }
        });

        JButton bSaveResult = new JButton("Save result");
        bSaveResult.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                owner.dispose();
                /*
                *   Some realisation
                *   for saving
                * */
            }
        });

        JButton bClose = new JButton("Close");
        bClose.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                owner.dispose();
            }
        });

        JPanel panel = new JPanel();
        panel.add(bSaveResult);
        panel.add(bTryAgain);
        panel.add(bClose);
        add(panel, BorderLayout.SOUTH);
        setSize(360, 160);
        setLocationRelativeTo(null);
    }
}

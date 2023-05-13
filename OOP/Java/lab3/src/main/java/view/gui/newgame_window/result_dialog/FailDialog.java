package view.gui.newgame_window.result_dialog;

import view.gui.newgame_window.GameWindow;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class FailDialog extends JDialog {
    JFrame owner;
    public FailDialog(GameWindow owner) {
        super(owner, "Game over", true);
        add(new JLabel("<html><h1>You have lost!</h1>" +
                        "<h3>Don't worry and try again<h3></html>"),
                BorderLayout.CENTER);

        this.owner = owner;

        JButton tryAgainButton = new JButton("Try again");
        tryAgainButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                owner.dispose();
                new GameWindow(owner.getCols(), owner.getRows(), owner.getTotalBombs(), owner.getUserName());
            }
        });

        JButton closeButton = new JButton("Close");
        closeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                owner.dispose();
            }
        });

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosed(WindowEvent e) {
                owner.dispose();
            }
        });
        JPanel panel = new JPanel();
        panel.add(tryAgainButton);
        panel.add(closeButton);
        add(panel, BorderLayout.SOUTH);
        setSize(360, 160);
        setLocationRelativeTo(null);
    }
}

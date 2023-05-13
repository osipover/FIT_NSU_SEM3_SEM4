package view.gui;

import view.gui.about_window.AboutDialog;
import view.gui.highscores_window.HighScoresDialog;
import view.gui.newgame_window.NewGameLaunch;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SweeperGUI extends JFrame{


    public SweeperGUI() {
        JButton newGameButton = createButtonNewGame();
        add(newGameButton);

        JButton aboutButton = createButtonAbout();
        add(aboutButton);

        JButton highScoresButton = createButtonHighScores();
        add(highScoresButton);

        initLaunchPage();
    }

    private JButton createButtonHighScores() {
        JButton highScoresButton = new JButton("High scores");
        highScoresButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
               Dialog highScoresDialog =  new HighScoresDialog(SweeperGUI.this);
               highScoresDialog.setVisible(true);
            }
        });
        return highScoresButton;
    }

    private JButton createButtonNewGame() {
        JButton newGameButton = new JButton("New game");
        newGameButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                NewGameLaunch launch = new NewGameLaunch();
            }
        });
        return newGameButton;
    }

    private JButton createButtonAbout() {
        JButton aboutButton = new JButton("About");
        aboutButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Dialog aboutDialog = new AboutDialog(SweeperGUI.this);
                aboutDialog.setVisible(true);
            }
        });
        return aboutButton;
    }


    private void initLaunchPage() {
        setSize(420, 420);
        setLayout(new FlowLayout());
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setTitle("Sweeper");
        setLocationRelativeTo(null);
        setResizable(false);
        setVisible(true);
    }

}

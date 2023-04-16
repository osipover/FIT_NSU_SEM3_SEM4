package view.gui;

import view.gui.dialogs.AboutDialog;
import view.gui.dialogs.NewGameLaunch;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SweeperGUI extends JFrame{


    public SweeperGUI() {

        JButton bNewGame = createButtonNewGame();
        add(bNewGame);

        JButton bAbout = createButtonAbout();
        add(bAbout);

        add(new JButton("wede"));

        initLaunchPage();
    }

    private JButton createButtonNewGame() {
        JButton bNewGame = new JButton("New game");
        bNewGame.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                NewGameLaunch launch = new NewGameLaunch();
            }
        });
        return bNewGame;
    }

    private JButton createButtonAbout() {
        JButton bAbout = new JButton("About");
        bAbout.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Dialog dAbout = new AboutDialog(SweeperGUI.this);
                dAbout.setVisible(true);
            }
        });
        return bAbout;
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

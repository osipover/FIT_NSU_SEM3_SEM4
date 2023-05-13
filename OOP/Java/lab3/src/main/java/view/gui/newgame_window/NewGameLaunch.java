package view.gui.newgame_window;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class NewGameLaunch extends JFrame {
    private JTextField textName;
    private JTextField textWidth;
    private JTextField textHeight;
    private JTextField textBombs;

    public NewGameLaunch() {
        setLayout(new FlowLayout(FlowLayout.CENTER));
        JPanel panelName = createPanelName();
        JPanel panelFieldSize = createPanelFieldSize();
        JPanel panelBombs = createPanelBombs();

        JButton bPlay = createButtonPlay();

        initFrame();
    }

    private JButton createButtonPlay() {
        JButton playButton = new JButton("Play");
        playButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    int width = Integer.parseInt(textWidth.getText());
                    int height = Integer.parseInt(textHeight.getText());
                    int totalBombs = Integer.parseInt(textBombs.getText());
                    GameWindow gameWindow = new GameWindow(width, height, totalBombs, textName.getText());
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(null,
                            "Incorrect integer format",
                            "Error",
                            JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        add(playButton);

        return playButton;
    }

    private JPanel createPanelBombs() {
        JPanel bombsPanel = new JPanel();
        textBombs = new JTextField("10");
        bombsPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        bombsPanel.add(new JLabel("Bombs"));
        bombsPanel.add(textBombs);
        bombsPanel.revalidate();
        add(bombsPanel);
        return bombsPanel;
    }

    private JPanel createPanelFieldSize() {
        JPanel pFieldSize = new JPanel();
        textWidth = new JTextField("9", 2);
        textHeight = new JTextField("9", 2);
        pFieldSize.setLayout(new FlowLayout(FlowLayout.LEFT));
        pFieldSize.add(new JLabel("Field size"));
        pFieldSize.add(textWidth);
        pFieldSize.add(new JLabel("x"));
        pFieldSize.add(textHeight);
        pFieldSize.revalidate();
        add(pFieldSize);
        return pFieldSize;
    }

    private JPanel createPanelName() {
        JPanel pName = new JPanel();
        textName = new JTextField("unknown", 15);
        pName.setLayout(new FlowLayout(FlowLayout.LEFT));
        pName.add(new JLabel("Name"));
        pName.add(textName);
        pName.revalidate();
        add(pName);
        return pName;
    }

    private void initFrame() {
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setTitle("New game");
        setSize(250, 150);
        setLocationRelativeTo(null);
        setResizable(false);
        setVisible(true);
    }


}

package view.gui.dialogs;

import view.gui.GameWindow;

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
        JButton bPlay = new JButton("Play");
        bPlay.addActionListener(new ActionListener() {
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
        add(bPlay);

        return bPlay;
    }

    private JPanel createPanelBombs() {
        JPanel pBombs = new JPanel();
        textBombs = new JTextField("10");
        pBombs.setLayout(new FlowLayout(FlowLayout.LEFT));
        pBombs.add(new JLabel("Bombs"));
        pBombs.add(textBombs);
        pBombs.revalidate();
        add(pBombs);
        return pBombs;
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

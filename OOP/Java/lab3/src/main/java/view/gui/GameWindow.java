package view.gui;

import controler.Controler;
import model.*;
import view.gui.dialogs.FailDialog;
import view.gui.dialogs.VictoryDialog;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class GameWindow extends JFrame{
    private Game game;
    private Controler controler;

    private final int COLS;
    private final int ROWS;
    private final int TOTAL_BOMBS;
    private final String USER_NAME;

    private JLabel countOfBombsLabel;
    private JPanel gameFieldPanel;
    private Stopwatch stopwatch;

    private JButton[][] buttons;



    public GameWindow(int cols, int rows, int totalBombs, String userName) {
        COLS = cols;
        ROWS = rows;
        TOTAL_BOMBS = totalBombs;
        USER_NAME = userName;

        game = new Game(COLS, ROWS, TOTAL_BOMBS);
        game.start();
        controler = new Controler(game);

        setIcons();
        initGameStatus();
        initGameField();
        initStopwatch();
        initFrame();
    }

//    private void initMetainfo() {
//        metainfoPanel = new JPanel();
//        initGameStatus(metainfoPanel);
//        initStopwatch(metainfoPanel);
//        add(metainfoPanel, BorderLayout.NORTH);
//    }
//
    private void initStopwatch() {
        stopwatch = new Stopwatch();
        stopwatch.setFont(new Font("Montserrat", Font.BOLD, 16));
        add(stopwatch, BorderLayout.SOUTH);
        stopwatch.start();
    }
//
    private void initGameStatus() {
        countOfBombsLabel = new JLabel();
        countOfBombsLabel.setText("Number of bombs: 10");
        add(countOfBombsLabel, BorderLayout.NORTH);
    }

    public int getCols() {
        return COLS;
    }

    public int getRows() {
        return ROWS;
    }

    public int getTotalBombs() {
        return TOTAL_BOMBS;
    }

    public String getUserName() {
        return USER_NAME;
    }

    private void initGameField() {
        buttons = new JButton[COLS][ROWS];
        gameFieldPanel = new JPanel(new GridLayout(COLS, ROWS)) {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                for (Coord coord : Ranges.getAllCoords()) {
                    buttons[coord.x][coord.y].setIcon(game.getCell(coord).icon);
                }
            }
        };
        for (Coord coord : Ranges.getAllCoords()) {
            JButton button = new JButton(game.getCell(coord).icon);
            button.setPreferredSize(new Dimension(40, 40));
            button.addMouseListener(new MouseAdapter() {
                @Override
                public void mousePressed(MouseEvent e) {
                    if (e.getButton() == MouseEvent.BUTTON1) {
                        controler.pressLeftButton(coord);
                    } else if (e.getButton() == MouseEvent.BUTTON3) {
                        controler.pressRightButton(coord);
                    }
                    gameFieldPanel.repaint();
                    if (game.isOver()) {
                        stopwatch.stop();
                        Dialog dialog = game.getState() == GameState.WON
                                ? new VictoryDialog(GameWindow.this)
                                : new FailDialog(GameWindow.this);
                        dialog.setVisible(true);
                    }
                }
            });
            buttons[coord.x][coord.y] = button;
            gameFieldPanel.add(button);
        }

        if(game.isOver()) {
            dispose();
        }

        add(gameFieldPanel, BorderLayout.CENTER);
    }

    private void initFrame() {
        pack();
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setTitle("Sweeper");
        setLocationRelativeTo(null);
        setResizable(false);
        setVisible(true);
    }

    private void setIcons() {
        for (Cell cell : Cell.values()) {
            cell.icon = getIcon(cell.name().toLowerCase());
        }
    }

    private ImageIcon getIcon(String name) {
        String filename = "img/" + name.toLowerCase() + ".png";
        ImageIcon icon = new ImageIcon(getClass().getResource("../../" + filename));
        return icon;
    }
}

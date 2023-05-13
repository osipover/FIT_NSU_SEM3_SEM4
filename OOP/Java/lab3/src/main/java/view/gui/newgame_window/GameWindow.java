package view.gui.newgame_window;

import controler.ControllerGUI;
import model.*;
import model.cell.Cell;
import model.coord.Coord;
import model.ranges.Ranges;
import model.state.GameState;
import scores.Score;
import stopwatch.StopwatchGUI;
import view.gui.newgame_window.result_dialog.FailDialog;
import view.gui.newgame_window.result_dialog.VictoryDialog;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class GameWindow extends JFrame{
    private Game game;
    private ControllerGUI controller;

    private final int COLS;
    private final int ROWS;
    private final int TOTAL_BOMBS;
    private final String USER_NAME;

    private JLabel countOfBombsLabel;
    private JPanel gameFieldPanel;
    private StopwatchGUI stopwatch;

    private JButton[][] buttons;

    public GameWindow(int cols, int rows, int totalBombs, String userName) {
        COLS = cols;
        ROWS = rows;
        TOTAL_BOMBS = totalBombs;
        USER_NAME = userName;

        game = new Game(COLS, ROWS, TOTAL_BOMBS);
        game.start();
        controller = new ControllerGUI(game);

        initNumOfBombsLabel();
        initGameField();
        initStopwatch();
        initFrame();
    }

    private void initStopwatch() {
        stopwatch = new StopwatchGUI();
        stopwatch.setFont(new Font("Montserrat", Font.BOLD, 16));
        add(stopwatch, BorderLayout.SOUTH);
        stopwatch.start();
    }

    private void initNumOfBombsLabel() {
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
                    buttons[coord.x][coord.y].setIcon(getIcon(game.getCell(coord)));
                }
            }
        };
        for (Coord coord : Ranges.getAllCoords()) {
            JButton button = new JButton(getIcon(game.getCell(coord)));
            button.setPreferredSize(new Dimension(40, 40));
            button.addMouseListener(new MouseAdapter() {
                @Override
                public void mousePressed(MouseEvent e) {
                    if (e.getButton() == MouseEvent.BUTTON1) {
                        controller.pressLeftButton(coord);
                    } else if (e.getButton() == MouseEvent.BUTTON3) {
                        controller.pressRightButton(coord);
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

    private ImageIcon getIcon(Cell cell) {
        String filemame = "img/" + cell.name().toLowerCase() + ".png";
        return new ImageIcon(getClass().getResource("../../" + filemame));
    }

    public Score getScore() {
        return new Score(USER_NAME, stopwatch.getHours(), stopwatch.getMinutes(), stopwatch.getSeconds());
    }
}


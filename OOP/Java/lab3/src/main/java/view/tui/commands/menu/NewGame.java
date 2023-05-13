package view.tui.commands.menu;

import controler.ControllerTUI;
import model.cell.Cell;
import model.coord.Coord;
import model.Game;
import model.state.GameState;
import stopwatch.StopwatchTUI;
import view.tui.colorize.Colorize;
import view.tui.commands.Command;
import view.tui.parser.CommandParser;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Properties;
import java.util.Scanner;

public class NewGame implements Command {
    private Game game;
    private ControllerTUI controler;
    private final Scanner scanner = new Scanner(System.in);
    private final StopwatchTUI stopwatch = new StopwatchTUI();

    private int width;
    private int height;
    private int numBombs;

    @Override
    public void execute(ArrayList<String> args) {
        width = getWidthFromConsole();
        height = getHeightFromConsole();
        numBombs = getNumBombsFromConsole();

        game = new Game(width, height, numBombs);
        controler = new ControllerTUI(game);
        game.start();

        Scanner scanner = new Scanner(System.in);
        String line;

        stopwatch.start();
        while (!game.isOver()) {
            outputGameWindow();
            line = scanner.nextLine();
            CommandParser.parse(line);
            controler.execute(CommandParser.getCommandName(), CommandParser.getCommandArgs());
        }
        outputGameWindow();
        outputGameResult();
        exitGame();
    }

    private void exitGame() {
        System.out.println("Press \"4\" to EXIT");
        String line = scanner.nextLine();
        while (!line.equals("4")){
            line = scanner.nextLine();
        }

    }

    private void outputGameWindow() {
        clearConsole();
        outputNumBombs();
        outputStopwatch();
        outputGameField();
    }

    private void outputStopwatch() {
        stopwatch.stop();
        System.out.println(stopwatch.toString());
    }

    private void outputGameResult() {
        if (game.getState() == GameState.WON) {
            System.out.println(Colorize.green("You are winner!"));
        }
        if (game.getState() == GameState.LOSE) {
            System.out.println(Colorize.red("You are looser!"));
        }
    }

    private void clearConsole(){
        try {
            ProcessBuilder pb = new ProcessBuilder("cmd", "/c", "cls");
            Process startProcess = pb.inheritIO().start();
            startProcess.waitFor();
        } catch (Exception ex) {

        }
    }

    private void outputNumBombs() {
        System.out.println("Number of bombs: " + numBombs);
    }

    private void outputGameField() {
        for (int x = -1; x < width; ++x) {
            for (int y = -1; y < height; ++y) {
                if (x == -1 && y == -1) {
                    System.out.print(' ');
                    System.out.print(' ');
                } else if (x == -1 && y != -1) {
                    System.out.print(y);
                    System.out.print(' ');
                } else if (x != -1 && y == -1) {
                    System.out.print(x);
                    System.out.print(' ');
                } else {
                    System.out.print(getSymbol(game.getCell(new Coord(x, y))) + ' ');
                }
            }
            System.out.println();
        }
    }

    private String getSymbol(Cell cell) {
        try {
            Properties properties = new Properties();
            properties.load(getClass().getClassLoader().getResourceAsStream("symbols.properties"));
            String symbol = properties.getProperty(cell.name().toLowerCase());
            return colorize(symbol);
        } catch (IOException e) {
            return null;
        }
    }

    private String colorize(String symbol) {
        if (symbol.equals("F")) return Colorize.green(symbol);
        if (symbol.equals("B")) return Colorize.red(symbol);
        if (symbol.equals("b")) return Colorize.red(symbol);
        if (symbol.equals("f")) return Colorize.purple(symbol);
        if (symbol.equals("*")) return Colorize.blue(symbol);

        return Colorize.white(symbol);
    }

    private int getWidthFromConsole() {
        System.out.print("WIDTH FIELD: ");
        return scanner.nextInt();
    }

    private int getHeightFromConsole() {
        System.out.print("HEIGHT FIELD: ");
        return scanner.nextInt();
    }

    private  int getNumBombsFromConsole() {
        System.out.print("NUMBER OF BOMBS: ");
        return scanner.nextInt();
    }
}

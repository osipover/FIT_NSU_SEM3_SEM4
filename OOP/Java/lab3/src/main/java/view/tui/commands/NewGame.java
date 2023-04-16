package view.tui.commands;

import controler.Controler;
import model.Cell;
import model.Coord;
import model.Game;
import model.GameState;
import view.tui.CommandParser;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Properties;
import java.util.Scanner;

public class NewGame implements Command{

    private Game game;
    private Controler controler;
    private final Scanner scanner = new Scanner(System.in);

    private int width;
    private int height;
    private int numBombs;

    @Override
    public void execute(ArrayList<String> args) {
        width = getWidthFromConsole();
        height = getHeightFromConsole();
        numBombs = getNumBombsFromConsole();

        setSymbols();

        game = new Game(width, height, numBombs);
        controler = new Controler(game);
        game.start();

        String line;
        while (!game.isOver()) {
            clearConsole();
            outputNumBombs();
            outputGameField();

            line = scanner.nextLine();
            CommandParser.parse(line);
            controler.execute(CommandParser.getCommandName(), CommandParser.getCommandArgs());
        }
        outputGameResult();
    }

    private void outputGameResult() {
        clearConsole();
        outputNumBombs();
        outputGameField();

        if (game.getState() == GameState.WON) {
            System.out.println("YOU ARE WINNER!!!");
        }
        if (game.getState() == GameState.LOSE) {
            System.out.println("YOU ARE LOOSER!!!");
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
                    System.out.print(game.getCell(new Coord(x, y)).symbol + ' ');
                }
            }
            System.out.println();
        }
    }

    private void setSymbols() {
        try {
            Properties properties = new Properties();
            properties.load(getClass().getClassLoader().getResourceAsStream("symbols.properties"));
            for (Cell cell : Cell.values()) {
                cell.symbol = properties.getProperty(cell.name().toLowerCase());
            }
        } catch (IOException e) {

        }

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

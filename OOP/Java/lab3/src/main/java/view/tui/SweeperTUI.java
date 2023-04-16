package view.tui;

import controler.Controler;
import model.Coord;
import model.Game;
import model.Ranges;
import view.tui.commands.Command;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.util.Properties;
import java.util.Scanner;

public class SweeperTUI {
    private Game game;
    private Controler controler;

    private final int COLS = 9;
    private final int ROWS = 9;
    private final int TOTAL_BOMBS = 10;

    public SweeperTUI() {
        CommandFactory cmdFactory = new CommandFactory();
        Scanner scanner = new Scanner(System.in);
        String line = scanner.nextLine();
        while (!line.equals("exit")) {
            CommandParser.parse(line);
            Command command = cmdFactory.create(CommandParser.getCommandName());
            command.execute(CommandParser.getCommandArgs());
            line = scanner.nextLine();
        }
    }

    private void outputField() {

    }

}

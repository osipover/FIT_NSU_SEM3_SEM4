package view.tui;

import model.Game;
import view.tui.commands.Command;
import view.tui.commands.Console;
import view.tui.factory.CommandFactory;
import view.tui.parser.CommandParser;

import java.util.Scanner;

public class SweeperTUI {
    private Game game;

    public SweeperTUI() {
        CommandFactory cmdFactory = new CommandFactory();
        Scanner scanner = new Scanner(System.in);
        String line = "";
        while (!line.equals("4")) {
            outputMenu();
            line = scanner.nextLine();
            CommandParser.parse(line);
            try {
                Command command = cmdFactory.create(CommandParser.getCommandName());
                command.execute(CommandParser.getCommandArgs());
            } catch (Exception ex) {
                System.err.println("Unknown command");
            }
            Console.clear();
        }
    }

    private void outputMenu() {
        System.out.println("Press \"1\" to chose NEW GAME");
        System.out.println("Press \"2\" to chose HIGH SCORES");
        System.out.println("Press \"3\" to chose ABOUT");
        System.out.println("Press \"4\" to chose EXIT");
    }
}

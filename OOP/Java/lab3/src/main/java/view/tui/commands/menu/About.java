package view.tui.commands.menu;

import view.tui.commands.Command;
import view.tui.commands.Console;
import view.tui.parser.CommandParser;

import java.awt.print.Printable;
import java.util.ArrayList;
import java.util.Scanner;

public class About implements Command {
    @Override
    public void execute(ArrayList<String> args) {
        Console.clear();
        System.out.println(generateInfo());
        System.out.println("Press \"4\" to chose EXIT");
        Scanner scanner = new Scanner(System.in);
        String line;
        while (!(line = scanner.nextLine()).equals("4")) {}
        Console.clear();
    }

    private String generateInfo() {
        return  "Minesweeper rules\n\n" +
                "Your task is to open all the non-mined cells on the field.\n" +
                "Your task is to open all the non-mined cells on the field.\n" +
                "The numbers on the cage show how many bombs are around.\n" +
                "Place flags on the cells with potential bombs.\n\n" +
                "Write \"open <i> <j>\" to open the cell.\n " +
                "Write \"flag <i> <j>\" to place/remove the flag.\n\n " +
                "If you open a cell with a bomb, you will lose. " +
                "Good luck!\n";
    }
}

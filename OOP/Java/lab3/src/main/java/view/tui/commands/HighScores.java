package view.tui.commands;

import java.util.ArrayList;

public class HighScores implements Command {
    @Override
    public void execute(ArrayList<String> args) {
        System.out.println("HIGH SCORES");
    }
}

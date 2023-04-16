package view.tui.commands;

import java.util.ArrayList;

public class About implements Command{
    @Override
    public void execute(ArrayList<String> args) {
        System.out.println("ABOUT");
    }
}

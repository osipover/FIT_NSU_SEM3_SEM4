package view.tui.commands;


import java.util.ArrayList;

public interface Command {
    void execute(ArrayList<String> args);
}
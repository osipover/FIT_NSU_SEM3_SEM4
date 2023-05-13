package view.tui.parser;

import java.util.ArrayList;
import java.util.Arrays;

public class CommandParser {

    private static String commandName;
    private static ArrayList<String> commandArgs;

    public static void parse(String line){
        ArrayList<String> list = new ArrayList<>(Arrays.asList(line.split(" ")));
        commandName = list.get(0);
        list.remove(0);
        commandArgs = list;
    }

    public static String getCommandName(){
        return commandName;
    }

    public static ArrayList<String> getCommandArgs(){
        return commandArgs;
    }
}
package com.parser;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class CommandParser {
    private String cmdName;
    private ArrayList<String> cmdArgs;

    public void parse(String line){
        ArrayList<String> list = new ArrayList<>(Arrays.asList(line.split(" ")));
        this.cmdName = list.get(0);
        list.remove(0);
        this.cmdArgs = list;
    }
    public String getCmdName(){
        return this.cmdName;
    }
    public ArrayList<String> getCmdArgs(){
        return this.cmdArgs;
    }

}

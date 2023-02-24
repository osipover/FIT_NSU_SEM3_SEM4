package com.calculator;

import java.io.*;
import com.command_factory.CommandFactory;
import com.command_factory.exception.CommandFactoryException;
import com.commands.exceptions.*;
import com.parser.CommandParser;
import com.commands.Command;
import com.context.Context;

public class Calculator {
    private final BufferedReader reader;
    private final Context context;

    public Calculator(InputStream in) {
        this.reader = new BufferedReader(new InputStreamReader(in));
        this.context = new Context();
    }
    public void start() {
        try {
            CommandParser cmdParser = new CommandParser();
            CommandFactory commandFactory = new CommandFactory();
            String line;
            while ((line = reader.readLine()) != null){
                cmdParser.parse(line);
                String cmdName = cmdParser.getCmdName();
                if (cmdName.equals("#")) continue;
                try {
                    Command command = commandFactory.create(cmdName);
                    command.execute(cmdParser.getCmdArgs(), context);
                } catch (CommandException | CommandFactoryException ex) {
                    System.err.println(ex.getMessage());
                }
            }
        } catch (IOException ex) {
            System.err.println(ex.getMessage());
            System.exit(1);
        }
    }
}

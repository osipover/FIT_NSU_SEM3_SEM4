package com.commands;

import com.commands.exceptions.*;
import com.context.Context;
import java.util.ArrayList;

public class Define implements Command{
    @Override
    public void execute(ArrayList<String> args, Context context) throws CommandException {
        try {
            if (args.size() != 2) throw new ArgumentsNumberException("DEFINE");
            String definition = parseDefinition(args.get(0));
            Double value = parseDouble(args.get(1));
            context.define(definition, value);
        } catch(IllegalArgumentException ex) {
            throw new DefineException(ex.getMessage());
        }
    }

    private String parseDefinition(String str) throws IllegalArgumentException {
        try {
            Double.parseDouble(str);
            throw new IllegalArgumentException("define: " + str);
        } catch (NumberFormatException ex){
            return str;
        }
    }

    private Double parseDouble(String str) throws IllegalArgumentException {
        try {
            return Double.parseDouble(str);
        } catch (NumberFormatException ex){
            throw new IllegalArgumentException("value: " + str);
        }
    }
}

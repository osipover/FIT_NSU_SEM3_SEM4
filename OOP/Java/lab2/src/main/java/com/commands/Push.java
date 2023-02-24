package com.commands;

import com.commands.exceptions.*;
import com.context.Context;
import java.util.ArrayList;

public class Push implements Command{
    @Override
    public void execute(ArrayList<String> args, Context context) throws CommandException {
        if (args.isEmpty()) throw new ArgumentsNumberException("PUSH");
        for (String argument : args ){
            Double num = parseDouble(argument, context);
            if (num == null) throw new PushException(argument);
            context.getStack().push(num);
        }
    }
    private Double parseDouble(String str, Context context){
        try {
            return Double.parseDouble(str);
        } catch (NumberFormatException ex) {
            return context.getDefines().get(str);
        }
    }

}

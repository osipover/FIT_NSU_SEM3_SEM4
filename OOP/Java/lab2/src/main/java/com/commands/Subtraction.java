package com.commands;

import com.commands.exceptions.ArgumentsNumberException;
import com.commands.exceptions.CommandException;
import com.context.Context;
import java.util.ArrayList;
import java.util.EmptyStackException;

public class Subtraction implements Command {
    @Override
    public void execute(ArrayList<String> args, Context context) throws CommandException {
        try {
            Double value1 = context.pop();
            Double value2 = context.pop();
            Double result = value1 - value2;
            context.push(result);
        } catch (EmptyStackException ex) {
            throw new ArgumentsNumberException("-");
        }
    }
}

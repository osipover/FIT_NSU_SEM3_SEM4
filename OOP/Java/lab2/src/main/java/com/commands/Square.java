package com.commands;

import com.commands.exceptions.ArgumentsNumberException;
import com.commands.exceptions.CommandException;
import com.commands.exceptions.NotEnoughStackException;
import com.context.Context;
import java.util.ArrayList;
import java.util.EmptyStackException;

import static java.lang.Double.NaN;

public class Square implements Command{
    @Override
    public void execute(ArrayList<String> args, Context context) throws CommandException {
        try {
            Double value = context.pop();
            Double result = Math.sqrt(value);
            // if (result.equals(NaN)) t
            context.push(result);
        } catch (EmptyStackException ex){
            throw new ArgumentsNumberException("SQUARE");
        }
    }
}

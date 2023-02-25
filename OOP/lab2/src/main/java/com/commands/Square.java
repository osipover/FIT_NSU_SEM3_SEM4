package com.commands;

import com.commands.exceptions.CommandException;
import com.commands.exceptions.NotEnoughStackException;
import com.context.Context;
import java.util.ArrayList;
import java.util.EmptyStackException;

public class Square implements Command{
    @Override
    public void execute(ArrayList<String> args, Context context) throws CommandException {
        try {
            Double value = context.pop();
            Double result = Math.sqrt(value);
            context.push(result);
        } catch (EmptyStackException ex){
            throw new NotEnoughStackException("SQUARE");
        }
    }
}

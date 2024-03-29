package com.commands;

import com.commands.exceptions.*;
import com.context.Context;
import java.util.ArrayList;
import java.util.EmptyStackException;

public class Division implements Command{
    @Override
    public void execute(ArrayList<String> args, Context context) throws CommandException {
        try {
            Double value1 = context.pop();
            Double value2 = context.pop();
            if (value2.equals(0.0)) throw new DivisionByZeroException();
            Double result = value1 / value2;
            context.push(result);
        } catch (EmptyStackException ex) {
            throw new ArgumentsNumberException("/");
        }
    }
}

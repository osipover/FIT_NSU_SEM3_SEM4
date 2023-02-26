package com.commands;

import com.commands.exceptions.*;
import com.context.Context;
import java.util.ArrayList;
import java.util.EmptyStackException;

public class Print implements Command{
    @Override
    public void execute(ArrayList<String> args, Context context) throws CommandException {
        try {
            Double num = context.getLastArgument();
            System.out.println(num);
        } catch (EmptyStackException ex){
            throw new NotEnoughStackException("PRINT");
        }
    }
}

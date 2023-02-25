package com.commands;

import com.commands.exceptions.*;
import com.context.Context;
import java.util.ArrayList;
import java.util.EmptyStackException;

public class Pop implements Command{
    @Override
    public void execute(ArrayList<String> args, Context context) throws CommandException {
        try{
            if (!args.isEmpty()) throw new ArgumentsNumberException("POP");
            context.pop();
        } catch (EmptyStackException ex){
            throw new NotEnoughStackException("POP");
        }
    }
}

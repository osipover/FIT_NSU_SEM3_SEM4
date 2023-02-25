package com.commands;

import java.util.ArrayList;
import com.commands.exceptions.CommandException;
import com.context.Context;

public interface Command {
    void execute(ArrayList<String> args, Context context) throws CommandException;
}

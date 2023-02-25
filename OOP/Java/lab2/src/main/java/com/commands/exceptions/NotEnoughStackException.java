package com.commands.exceptions;

public class NotEnoughStackException extends CommandException {
    public NotEnoughStackException(String cmdName) {
        super("Not enough arguments in stack to apply " +  "\"" + cmdName + "\"");
    }
}

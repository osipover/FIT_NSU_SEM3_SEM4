package com.commands.exceptions;

public class PushException extends CommandException{
    public PushException(String argument) {
        super("You try to push nonexistent parameter \"" + argument + "\"");
    }
}

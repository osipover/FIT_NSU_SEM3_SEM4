package com.commands.exceptions;

public class ArgumentsNumberException extends CommandException {
    public ArgumentsNumberException(String cmdName) {
        super("Incorrect number of arguments by " + "\"" + cmdName + "\"");
    }
}

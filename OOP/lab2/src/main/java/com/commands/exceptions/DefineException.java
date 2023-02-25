package com.commands.exceptions;

public class DefineException extends CommandException {
    public DefineException(String message) {
        super("Incorrect definition " + "(" + message + ")");
    }
}

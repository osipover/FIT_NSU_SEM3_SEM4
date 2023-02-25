package com.commands.exceptions;

public class CommandException extends Exception {
    public CommandException() {
    }
    public CommandException(String message){
        super(message);
    }
}

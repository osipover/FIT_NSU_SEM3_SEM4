package com.commands.exceptions;

public class DivisionByZeroException extends CommandException {
    public DivisionByZeroException() {
        super("You divided by zero");
    }
}

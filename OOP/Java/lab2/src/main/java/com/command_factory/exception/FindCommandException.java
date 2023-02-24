package com.command_factory.exception;


public class FindCommandException extends CommandFactoryException {
    public FindCommandException(String cmdName) {
        super("Using a non-existent command " + "\"" + cmdName + "\"");
    }
}

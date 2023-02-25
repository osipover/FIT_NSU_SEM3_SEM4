package com.command_factory.exception;

public class LoadFactoryException extends CommandFactoryException {
    public LoadFactoryException(){
        super("Unable to load commands factory");
    }
}

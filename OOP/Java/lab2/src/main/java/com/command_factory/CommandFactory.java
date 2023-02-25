package com.command_factory;

import com.command_factory.exception.*;
import com.commands.Command;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class CommandFactory {
    private final Properties properties;

    public CommandFactory() throws CommandFactoryException {
        try {
            InputStream is = getClass().getClassLoader().getResourceAsStream("commands.properties");
            this.properties = new Properties();
            this.properties.load(is);
        } catch (IOException ex) {
            throw new LoadFactoryException();
        }

    }
    public Command create(String cmdName) throws CommandFactoryException{
        try {
            Class<?> clazz = Class.forName(properties.getProperty(cmdName));
            return (Command)clazz.newInstance();
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException ex) {
            throw new FindCommandException(cmdName);
        }
    }

}



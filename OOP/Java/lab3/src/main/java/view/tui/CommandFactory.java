package view.tui;


import view.tui.commands.Command;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class CommandFactory {
    private final Properties properties = new Properties();

    public CommandFactory()  {
        try {
            InputStream is = getClass().getClassLoader().getResourceAsStream("commands.properties");
            this.properties.load(is);
        } catch (IOException ex) {
            //throw new LoadFactoryException();
        }

    }
    public Command create(String cmdName)  {
        try {
            Class<?> clazz = Class.forName(properties.getProperty(cmdName));
            return (Command)clazz.newInstance();
        } catch (NullPointerException |ClassNotFoundException | InstantiationException | IllegalAccessException ex) {
            // throw new FindCommandException(cmdName);
        }
        return null;
    }

}
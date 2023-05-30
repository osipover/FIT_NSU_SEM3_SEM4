package connection.commands.factory;

import connection.commands.Command;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class CommandFactory {
    private Properties properties;

    public CommandFactory() {
        InputStream is = getClass().getClassLoader().getResourceAsStream("commands.properties");
        this.properties = new Properties();
        try {
            this.properties.load(is);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public Command create(String msgTitle) {
        try {
            Class<?> clazz = Class.forName(properties.getProperty(msgTitle));
            return (Command)clazz.newInstance();
        } catch (NullPointerException |ClassNotFoundException | InstantiationException | IllegalAccessException ex) {
            return null;
        }
    }
}

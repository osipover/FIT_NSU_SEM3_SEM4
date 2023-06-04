package server.connection.commands.factory;

import server.connection.commands.ServerCommand;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class CommandFactory {
    private Properties properties;

    public CommandFactory() {
        InputStream is = getClass().getClassLoader().getResourceAsStream("server-commands.properties");
        this.properties = new Properties();
        try {
            this.properties.load(is);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public ServerCommand create(String msgTitle) {
        try {
            System.out.println(msgTitle);
            Class<?> clazz = Class.forName(properties.getProperty(msgTitle));
            return (ServerCommand)clazz.newInstance();
        } catch (NullPointerException |ClassNotFoundException | InstantiationException | IllegalAccessException ex) {
            return null;
        }
    }
}

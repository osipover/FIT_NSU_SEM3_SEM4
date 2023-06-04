package client.model.commands;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class ClientCommandFactory {
    private Properties properties;

    public ClientCommandFactory() {
        InputStream is = getClass().getClassLoader().getResourceAsStream("client-commands.properties");
        this.properties = new Properties();
        try {
            this.properties.load(is);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public ClientCommand create(String msgTitle) {
        try {
            Class<?> clazz = Class.forName(properties.getProperty(msgTitle));
            return (ClientCommand)clazz.newInstance();
        } catch (NullPointerException |ClassNotFoundException | InstantiationException | IllegalAccessException ex) {
            return null;
        }
    }
}

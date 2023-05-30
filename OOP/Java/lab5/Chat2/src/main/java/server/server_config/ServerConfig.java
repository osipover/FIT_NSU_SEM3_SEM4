package server.server_config;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class ServerConfig {
    private static int port;
    private static int timeout;
    private static int messageStorageCapacity;

    private static final String PATH_TO_PROP = "/serverconf.properties";

    public static void init() {
        Properties prop = new Properties();
        try (InputStream inputStream = ServerConfig.class.getResourceAsStream(PATH_TO_PROP)) {
            prop.load(inputStream);
            port = Integer.parseInt(prop.getProperty("port"));
            timeout = Integer.parseInt(prop.getProperty("timeout"));
            messageStorageCapacity = Integer.parseInt(prop.getProperty("message.storage.capacity"));
        } catch (IOException ex) {}
    }

    public static int getPort() {
        return port;
    }

    public static int getTimeout() {
        return timeout;
    }

    public static int getMessageStorageCapacity() {
        return messageStorageCapacity;
    }
}

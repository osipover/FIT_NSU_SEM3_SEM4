package server.server_config;

import network.protocol.ProtocolType;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class ServerConfig {
    private int port;
    private int timeout;
    private int messageStorageCapacity;
    private ProtocolType protocolType;

    private static final String PATH_TO_PROP = "/chatconf.properties";

    public ServerConfig() {
        Properties prop = new Properties();
        try (InputStream inputStream = ServerConfig.class.getResourceAsStream(PATH_TO_PROP)) {
            prop.load(inputStream);
            port = Integer.parseInt(prop.getProperty("port"));
            timeout = Integer.parseInt(prop.getProperty("timeout"));
            messageStorageCapacity = Integer.parseInt(prop.getProperty("message.storage.capacity"));
            protocolType = ProtocolType.valueOf(prop.getProperty("protocol.type").toUpperCase());
        } catch (IOException ex) {}
    }

    public int getPort() {
        return port;
    }

    public int getTimeout() {
        return timeout;
    }

    public int getMessageStorageCapacity() {
        return messageStorageCapacity;
    }

    public ProtocolType getProtocolType() {
        return protocolType;
    }


}

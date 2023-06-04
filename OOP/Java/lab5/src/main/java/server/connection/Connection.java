package server.connection;

import server.connection.commands.ServerCommand;
import server.connection.commands.factory.CommandFactory;
import network.packet.Packet;
import network.protocol.Protocol;
import network.protocol.ProtocolBuilder;
import server.ChatServer;
import java.io.IOException;
import java.net.Socket;

public class Connection extends Thread {
    private ChatServer server;
    private Socket socket;
    private String username;
    private final CommandFactory commandFactory = new CommandFactory();
    private final Protocol protocol;

    private boolean isUserOnline = true;
    private int countOffline = 0;
    private long lastActivity = 0;

    public Connection(ChatServer server, Socket socket) throws IOException {
        this.server = server;
        this.socket = socket;
        this.protocol = ProtocolBuilder.create(server.getConfig().getProtocolType(), socket);
    }

    @Override
    public void run() {
        while (!Thread.currentThread().isInterrupted()) {
            Packet packet;
            try {
                packet = protocol.read();
            } catch (IOException | ClassNotFoundException e) {
                packet = null;
                isUserOnline = false;
                sendPacket(new Packet(Packet.PING, null, null));
                countOffline++;
            }

            if (packet != null) {
                lastActivity = System.currentTimeMillis();
                ServerCommand command = commandFactory.create(packet.getTitle());
                command.execute(Connection.this, packet);
            }

            if (!isUserOnline && countOffline == 5) {
                server.sendOfflineNotification(Connection.this);
            }

            long timeout = server.getConfig().getTimeout() * 1000L;
            if (System.currentTimeMillis() - lastActivity > timeout) {
                server.onDisconnect(Connection.this);
            }
        }
    }

    public void setOnline() {
        this.isUserOnline = true;
        this.countOffline = 0;
    }

    public ChatServer getServer() {
        return this.server;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void sendPacket(Packet packet) {
        try {
            protocol.write(packet);
        } catch (IOException ex) {

        }
    }

    public String getUsername() {
        return this.username;
    }

    public void disconnect() {
        try {
            socket.close();
        } catch (IOException ex) {}
        interrupt();
    }

    @Override
    public String toString() {
        return "Connection: " + socket.getInetAddress() + socket.getPort();
    }

}

package server.connection.commands;

import server.connection.Connection;
import network.packet.Packet;
import server.ChatServer;

public class RegisterCommand implements ServerCommand {
    @Override
    public void execute(Connection connection, Packet packet) {
        ChatServer server = connection.getServer();
        connection.setUsername(packet.getUsername());
        server.registerNewUser(connection, packet.getUsername());
    }
}

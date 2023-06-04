package server.connection.commands;

import server.connection.Connection;
import network.packet.Packet;
import server.ChatServer;

public class ReceiveMessageCommand implements ServerCommand {
    @Override
    public void execute(Connection connection, Packet packet) {
        ChatServer server = connection.getServer();
        server.receiveMessage(new Packet(Packet.MSG, connection.getUsername(), packet.getContent()));
    }
}

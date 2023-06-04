package server.connection.commands;

import server.connection.Connection;
import network.packet.Packet;

public class PingCommand implements ServerCommand {
    @Override
    public void execute(Connection connection, Packet message) {
        connection.setOnline();
    }
}

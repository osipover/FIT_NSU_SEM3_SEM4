package server.connection.commands;

import server.connection.Connection;
import network.packet.Packet;

public interface ServerCommand {
    void execute(Connection connection, Packet message);
}

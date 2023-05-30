package connection.commands;

import connection.Connection;
import connection.packet.Packet;

public interface Command {
    void execute(Connection connection, Packet message);
}

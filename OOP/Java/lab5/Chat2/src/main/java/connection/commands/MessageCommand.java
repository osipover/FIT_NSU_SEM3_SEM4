package connection.commands;

import connection.Connection;
import connection.packet.Packet;
import server.ChatServer;

public class MessageCommand implements Command {
    @Override
    public void execute(Connection connection, Packet message) {
        ChatServer server = connection.getServer();
        server.receiveMessage(message);
    }
}

package connection.commands;

import connection.Connection;
import connection.packet.Packet;
import server.ChatServer;

public class RegisterCommand implements Command {
    @Override
    public void execute(Connection connection, Packet message) {
        ChatServer server = connection.getServer();
        connection.setUsername(message.getUsername());
        server.registerNewUser(connection, message.getUsername());
    }
}

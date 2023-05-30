package connection.commands;

import connection.Connection;
import connection.packet.Packet;
import server.ChatServer;

import java.util.ArrayList;

public class SendUserListCommand implements Command {
    @Override
    public void execute(Connection connection, Packet packet) {
        ChatServer chatServer = connection.getServer();
        ArrayList<String> usersList = chatServer.getUsersList();
        connection.sendUsersList(usersList);
    }
}

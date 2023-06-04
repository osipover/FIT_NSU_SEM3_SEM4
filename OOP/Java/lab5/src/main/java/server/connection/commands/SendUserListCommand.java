package server.connection.commands;

import network.packet.Packet;
import server.connection.Connection;

public class SendUserListCommand implements ServerCommand{
    @Override
    public void execute(Connection connection, Packet message) {
        connection.sendPacket(new Packet(Packet.USERS_LIST, null, connection.getServer().getUsersList()));
    }
}

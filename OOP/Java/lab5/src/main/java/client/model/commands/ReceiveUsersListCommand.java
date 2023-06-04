package client.model.commands;

import client.model.Client;
import client.model.Receiver;
import network.packet.Packet;
import java.util.ArrayList;

public class ReceiveUsersListCommand implements ClientCommand {
    @Override
    public void execute(Receiver receiver, Packet packet) {
        Client client = receiver.getClient();
        client.addUsersList((ArrayList<String>) packet.getContent());
    }
}

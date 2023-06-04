package client.model.commands;

import client.model.Receiver;
import network.packet.Packet;
import java.io.IOException;

public class PingCommand implements ClientCommand {
    @Override
    public void execute(Receiver receiver, Packet packet) throws IOException {
        receiver.getClient().sendPacket(packet);
    }
}

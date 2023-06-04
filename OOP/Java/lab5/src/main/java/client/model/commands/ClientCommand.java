package client.model.commands;

import client.model.Receiver;
import network.packet.Packet;

import java.io.IOException;

public interface ClientCommand {
    public void execute(Receiver receiver, Packet packet) throws IOException;
}

package network.protocol;

import network.packet.Packet;

import java.io.IOException;

public interface Protocol {
    Packet read() throws IOException, ClassNotFoundException;
    void write(Packet packet) throws IOException;
}

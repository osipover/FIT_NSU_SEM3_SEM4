package network.protocol.serialize;

import network.packet.Packet;
import network.protocol.Protocol;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class SerializeProtocol implements Protocol {
    private ObjectInputStream reader;
    private ObjectOutputStream writer;

    public SerializeProtocol(Socket socket) throws IOException {
        this.writer = new ObjectOutputStream(socket.getOutputStream());
        this.reader = new ObjectInputStream(socket.getInputStream());
    }

    @Override
    public Packet read() throws IOException, ClassNotFoundException {
        Packet packet = (Packet) reader.readObject();
        return packet;
    }

    @Override
    public void write(Packet packet) throws IOException {
        writer.writeObject(packet);
    }
}

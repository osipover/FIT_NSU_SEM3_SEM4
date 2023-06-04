package network.protocol.json;

import com.google.gson.Gson;
import network.packet.Packet;
import network.protocol.Protocol;

import java.io.*;
import java.net.Socket;

public class JsonProtocol implements Protocol {
    private BufferedReader reader;
    private PrintWriter writer;
    private Gson gson = new Gson();

    public JsonProtocol(Socket socket) throws IOException {
        reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        writer = new PrintWriter(socket.getOutputStream(), true);
    }

    @Override
    public Packet read() throws IOException {
        String jsonPacket = reader.readLine();
        Packet packet = gson.fromJson(jsonPacket, Packet.class);
        return packet;
    }

    @Override
    public void write(Packet packet) {
        String jsonPacket = gson.toJson(packet);
        writer.println(jsonPacket);
    }
}

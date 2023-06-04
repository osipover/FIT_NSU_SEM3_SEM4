package client.model;

import network.packet.Packet;
import network.protocol.Protocol;
import network.protocol.ProtocolBuilder;
import server.server_config.ServerConfig;

import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.util.concurrent.ArrayBlockingQueue;

public class Client implements Closeable {
    private final String USERNAME;
    private final String IP;
    private final int PORT;
    private Socket socket;
    private Protocol protocol;
    private ServerConfig config = new ServerConfig();
    private ArrayBlockingQueue<ArrayList<String>> usersList = new ArrayBlockingQueue<>(1);

    public Client(String username, String ip, int port) {
        USERNAME = username;
        IP = ip;
        PORT = port;
    }

    public Packet receivePacket() throws IOException {
        Packet packet;
        try {
            packet = protocol.read();
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
        return packet;
    }

    public void connectToServer() {
        try {
            socket = new Socket(IP, PORT);
            protocol = ProtocolBuilder.create(config.getProtocolType(), socket);
            protocol.write(new Packet(Packet.REG, USERNAME, null));

        } catch (IOException e) {
            System.out.println("Client exception: " + e);
            throw new RuntimeException(e);
        }
    }

    public void sendPacket(Packet packet) throws IOException {
        protocol.write(packet);
    }

    public String getUsername() {
        return USERNAME;
    }

    public void addUsersList(ArrayList<String> users) {
        usersList.add(users);
    }

    public ArrayList<String> getUsers() {
        ArrayList<String> users = null;
        try {
            users = usersList.take();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        return users;
    }


    @Override
    public void close() {
        try {
            socket.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

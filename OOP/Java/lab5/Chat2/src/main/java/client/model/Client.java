package client.model;

import connection.packet.Packet;

import java.io.Closeable;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;

public class Client implements Closeable {
    private Socket socket;
    private ObjectInputStream reader;
    private ObjectOutputStream writer;

    private final String USERNAME;
    private final String IP;
    private final int PORT;

    public Client(String username, String ip, int port) {
        USERNAME = username;
        IP = ip;
        PORT = port;
    }

    public String receiveMessage() {
        String message;
        try {
            message = (String) reader.readObject();
        } catch (IOException e) {
            throw new RuntimeException(e);
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
        return message;
    }

    public void connectToServer() {
        try {
            socket = new Socket(IP, PORT);
            writer = new ObjectOutputStream(socket.getOutputStream());
            reader = new ObjectInputStream(socket.getInputStream());
            writer.writeObject(new Packet(Packet.REG, USERNAME, "connect"));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void sendMessage(String message) {
        Packet packet = new Packet(Packet.MSG, USERNAME, message);
        try {
            writer.writeObject(packet);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public ArrayList<String> requestUsersList() {
        ArrayList<String> usersList = null;
        try {
            writer.writeObject(new Packet(Packet.USERS_LIST, USERNAME, null));
            usersList = (ArrayList<String>)reader.readObject();
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
        return usersList;
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

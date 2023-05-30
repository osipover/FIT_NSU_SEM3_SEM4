package connection;

import connection.commands.Command;
import connection.commands.factory.CommandFactory;
import connection.packet.Packet;
import server.ChatServer;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class Connection extends Thread {
    private final Socket socket;
    private String username;
    private final CommandFactory commandFactory = new CommandFactory();
    private final ChatServer server;
    private final ObjectInputStream inputStream;
    private final ObjectOutputStream outputStream;

    public Connection(ChatServer server, Socket socket) throws IOException {
        this.server = server;
        this.socket = socket;
        this.inputStream = new ObjectInputStream(socket.getInputStream());
        this.outputStream = new ObjectOutputStream(socket.getOutputStream());
    }

    @Override
    public void run() {
        try {
            while (!isInterrupted()) {
                Packet packet = (Packet) inputStream.readObject();
                Command command = commandFactory.create(packet.getTitle());
                command.execute(this, packet);
            }
        } catch (IOException | ClassNotFoundException ex) {
            server.onException(this, ex);

        } finally {
            server.onDisconnect(this);
        }
    }

    public ChatServer getServer() {
        return this.server;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void sendMessage(String message) {
        try {
            outputStream.writeObject(message);
        } catch (IOException ex) {
            server.onException(this, ex);
        }
    }

    public void sendUsersList(ArrayList<String> usersList) {
        try {
            outputStream.writeObject(usersList);
        } catch (IOException e) {
            server.onException(this, e);
        }
    }

    public String getUsername() {
        return this.username;
    }

    public void disconnect() throws IOException {
        interrupt();
        try {
            socket.close();
        } catch (IOException ex) {
            server.onException(this, ex);
        }
    }

    @Override
    public String toString() {
        return "Connection: " + socket.getInetAddress() + socket.getPort();
    }

}





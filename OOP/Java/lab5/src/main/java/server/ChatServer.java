package server;

import server.connection.Connection;
import network.packet.Packet;
import org.apache.log4j.Logger;
import server.limited_queue.LimitedQueue;
import server.server_config.ServerConfig;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class ChatServer {
    private static final Logger log = Logger.getLogger(ChatServer.class);
    private final ArrayList<Connection> connections = new ArrayList<>();
    private final LimitedQueue<Packet> lastMessages;
    private final ServerConfig config = new ServerConfig();

    public static void main(String[] args) {
        new ChatServer();
    }

    private ChatServer() {
        log.info("Server is running");
        lastMessages = new LimitedQueue<>(config.getMessageStorageCapacity());
        try {
            ServerSocket comminacatorServerSocket = new ServerSocket(config.getPort());
            while (true) {
                Socket communicatorSocket = comminacatorServerSocket.accept();
                communicatorSocket.setSoTimeout(1000);
                Connection connection = new Connection(ChatServer.this, communicatorSocket);
                connection.start();
                log.info("New client accepted");
            }
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }
    }

    public synchronized void registerNewUser(Connection connection, String username) {
        log.info(username + " was connected");
        connections.add(connection);
        sendLastMessagesToConnection(connection);
        sendToAllConnections(new Packet(Packet.MSG, username, "was connected"));
    }

    private void sendLastMessagesToConnection(Connection connection) {
        for (Packet message : lastMessages.getQueue()) {
            connection.sendPacket(message);
        }
    }

    public synchronized void receiveMessage(Packet packet) {
        lastMessages.add(packet);
        sendToAllConnections(packet);
    }

    public synchronized void onDisconnect(Connection connection) {
        String username = connection.getUsername();
        connection.disconnect();
        connections.remove(connection);
        sendToAllConnections(new Packet(Packet.MSG, username, " was disconnected for timeout"));
        log.info(username + " was disconnected");
    }

    public synchronized void onException(Connection connection, Exception ex) {
        log.warn(connection.getUsername() + " exception: " + ex);
    }

    public ArrayList<String> getUsersList() {
        ArrayList<String> usersList = new ArrayList<>();
        for (Connection connection : connections) {
            usersList.add(connection.getUsername());
        }
        return usersList;
    }

    public void sendToAllConnections(Packet message) {
        for (Connection connection : connections) {
            connection.sendPacket(message);
        }
    }

    public void sendOfflineNotification(Connection offlineConnection) {
        for (Connection connection : connections) {
            if (connection != offlineConnection) {
                connection.sendPacket(new Packet(Packet.MSG, offlineConnection.getUsername(), " is offline"));
            }
        }
    }

    public ServerConfig getConfig() {
        return config;
    }


//    public void sendUsersList(Connection connection) {
//        ArrayList<String> usersList = new ArrayList<>();
//        for (Connection connect : connections) {
//            usersList.add(connect.getUsername());
//        }
//    }
}
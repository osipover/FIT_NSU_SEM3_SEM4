package server;

import connection.Connection;
import connection.packet.Packet;
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
    private final LimitedQueue<String> lastMessages;

    public static void main(String[] args) {
        new ChatServer();
    }

    private ChatServer() {
        log.info("Server is running");
        ServerConfig.init();
        lastMessages = new LimitedQueue<>(ServerConfig.getMessageStorageCapacity());

        try {
            ServerSocket serverSocket = new ServerSocket(ServerConfig.getPort());
            ServerSocket echoServerSocket = new ServerSocket(1000);
            while (true) {
                Socket clientSocket = serverSocket.accept();
                Socket echoClientSocket = echoServerSocket.accept();
                echoClientSocket.setSoTimeout(ServerConfig.getTimeout());

                new Connection(this, clientSocket).start;
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
        sendToAllConnections(username + " was connected");
    }

    private void sendLastMessagesToConnection(Connection connection) {
        for (String message : lastMessages.getQueue()) {
            connection.sendMessage(message);
        }
    }

    public synchronized void receiveMessage(Packet packet) {
        lastMessages.add(packet.getUsername() + ": " + packet.getMessage());
        sendToAllConnections(packet.getUsername() + ": " + packet.getMessage());
    }

    public synchronized void onDisconnect(Connection connection) {
        String username = connection.getUsername();
        connections.remove(connection);
        sendToAllConnections(username + " was disconnected");
    }

    public synchronized void onException(Connection connection, Exception ex) {
        System.out.println("Connection exception: " + ex);

    }

    public ArrayList<String> getUsersList() {
        ArrayList<String> usersList = new ArrayList<>();
        for (Connection connection : connections) {
            usersList.add(connection.getUsername());
        }
        return usersList;
    }

    private void sendToAllConnections(String message) {
        for (Connection connection : connections) {
            connection.sendMessage(message);
        }
    }

    public void sendUsersList(Connection connection) {
        ArrayList<String> usersList = new ArrayList<>();
        for (Connection connect: connections) {
            usersList.add(connect.getUsername());
        }
        connection.sendUsersList(usersList);
    }

}
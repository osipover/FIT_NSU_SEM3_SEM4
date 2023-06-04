package client.controller;

import client.model.Client;
import client.model.Receiver;
import network.packet.Packet;

import javax.swing.*;
import java.io.IOException;
import java.util.ArrayList;

public class ControllerGUI {
    private Client client;

    public ControllerGUI(String username, String ip, int port) {
        client = new Client(username, ip, port);
    }

    public void connectToServer() {
        client.connectToServer();
    }

    public void sendMessage(String msg) throws IOException {
        client.sendPacket(new Packet(Packet.MSG, null, msg));
    }

    public String getUsername() {
        return client.getUsername();
    }

    public void requestUsersList() throws IOException {
        client.sendPacket(new Packet(Packet.USERS_LIST, null, null));
    }

    public void initMessageReceiver(Receiver messageReceiver, JTextArea chatArea) {
        messageReceiver.setClient(client);
        messageReceiver.setChatArea(chatArea);
    }

    public ArrayList<String> getUsers() {
        return client.getUsers();
    }
}

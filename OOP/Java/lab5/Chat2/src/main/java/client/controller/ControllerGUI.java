package client.controller;

import client.model.Client;
import client.model.MessageReceiver;

import javax.swing.*;
import java.util.ArrayList;

public class ControllerGUI {
    private Client client;

    public ControllerGUI(String username, String ip, int port) {
        client = new Client(username, ip, port);
    }

    public void connectToServer() {
        client.connectToServer();
    }

    public void sendMessage(String msg) {
        client.sendMessage(msg);
    }

    public ArrayList<String> requestUsersList() {
        return client.requestUsersList();
    }

    public void initMessageReceiver(MessageReceiver messageReceiver, JTextArea chatArea) {
        messageReceiver.setClient(client);
        messageReceiver.setChatArea(chatArea);
    }
}

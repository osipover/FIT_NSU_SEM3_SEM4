package client.model;

import client.model.commands.ClientCommand;
import client.model.commands.ClientCommandFactory;
import network.packet.Packet;

import javax.swing.*;
import java.io.IOException;

public class Receiver extends Thread {
    private Client client;
    private JTextArea chatArea;
    private ClientCommandFactory commandFactory = new ClientCommandFactory();

    public Receiver() { }

    public Client getClient() {
        return client;
    }

    public JTextArea getChatArea() {
        return chatArea;
    }

    @Override
    public void run() {
         while (!isInterrupted()) {
             try {
                 Packet packet = client.receivePacket();
                 ClientCommand command = commandFactory.create(packet.getTitle());
                 command.execute(this, packet);
             } catch (IOException ex) {
                 chatArea.append("No connection\n");
                 interrupt();
             }
         }
    }

    public void setClient(Client client) {
        this.client = client;
    }

    public void setChatArea(JTextArea chatArea) {
        this.chatArea = chatArea;
    }
}

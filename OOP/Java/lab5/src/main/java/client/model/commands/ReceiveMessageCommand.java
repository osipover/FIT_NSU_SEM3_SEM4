package client.model.commands;


import client.model.Receiver;
import network.packet.Packet;
import javax.swing.*;

public class ReceiveMessageCommand implements ClientCommand{
    @Override
    public void execute(Receiver receiver, Packet packet) {
        JTextArea chat = receiver.getChatArea();
        chat.append(packet.getUsername() + ": " + packet.getContent() + "\n");
        chat.setCaretPosition(chat.getDocument().getLength());
    }
}

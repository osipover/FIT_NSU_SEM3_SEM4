package client.model;

import javax.swing.*;

public class MessageReceiver extends Thread {
    private Client client;
    private JTextArea chat;

    public MessageReceiver( ) {

    }

    @Override
    public void run() {
         while (!isInterrupted()) {
             Object o = client.receiveMessage();
             if (o instanceof String) {
                 chat.append(o + "\n");
                 chat.setCaretPosition(chat.getDocument().getLength());
             }

         }
    }

    public void setClient(Client client) {
        this.client = client;
    }

    public void setChatArea(JTextArea chatArea) {
        this.chat = chatArea;
    }
}

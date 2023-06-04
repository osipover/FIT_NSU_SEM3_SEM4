package client.GUI;

import client.controller.ControllerGUI;
import client.model.Receiver;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class ChatWindow extends JFrame {
    private final int WIDTH = 600;
    private final int HEIGHT = 400;

    private ControllerGUI controller;
    private Receiver messageReceiver = new Receiver();

    private JPanel mainPanel;
    private JTextArea chatArea;
    private JTextField inputField;
    private JLabel usernameLabel;
    private JButton sendButton;
    private JButton usersButton;

    public ChatWindow(String username, String ip, int port) {
        controller = new ControllerGUI(username, ip, port);
        controller.connectToServer();
        controller.initMessageReceiver(messageReceiver, chatArea);
        messageReceiver.start();

        initUsernameLabel();
        initChatArea();
        initInputField();
        initSendButton();
        initUsersButton();
        initFrame();
    }

    private void initUsernameLabel() {
        usernameLabel.setText(controller.getUsername());
    }

    private void initUsersButton() {
        usersButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new UsersDialog(ChatWindow.this, controller);
            }
        });
    }

    private void initSendButton() {
        sendButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String message = inputField.getText();
                if (message.equals("")) return;
                inputField.setText(null);
                try {
                    controller.sendMessage(message);
                } catch (IOException ex) {
                    chatArea.append("No connection\n");
                }
            }
        });
    }

    private void initChatArea() {
        chatArea.setEditable(false);
        chatArea.setLineWrap(true);
    }

    private void initInputField() {
        inputField.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String msg = inputField.getText();
                if (msg.equals("")) return;
                inputField.setText(null);
                try {
                    controller.sendMessage(msg);
                } catch (IOException ex) {
                    chatArea.append("No connection\n");
                }
            }
        });
    }

    void initFrame() {
        setContentPane(mainPanel);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setSize(WIDTH, HEIGHT);
        setLocationRelativeTo(null);
        setVisible(true);
    }
}

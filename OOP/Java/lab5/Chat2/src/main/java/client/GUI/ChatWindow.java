package client.GUI;

import client.GUI.users_dialog.UsersDialog;
import client.controller.ControllerGUI;
import client.model.MessageReceiver;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChatWindow extends JFrame {
    private final int WIDTH = 600;
    private final int HEIGHT = 400;

    private ControllerGUI controller;
    private MessageReceiver messageReceiver = new MessageReceiver();

    private JPanel mainPanel;
    private JTextArea chatArea;
    private JTextField inputField;
    private JLabel chatLabel;
    private JButton sendButton;
    private JButton usersButton;

    public ChatWindow(String username, String ip, int port) {
        controller = new ControllerGUI(username, ip, port);
        controller.connectToServer();
        controller.initMessageReceiver(messageReceiver, chatArea);
        messageReceiver.start();

        initChatArea();
        initInputField();
        initSendButton();
        initUsersButton();
        initFrame();
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
                controller.sendMessage(message);
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
                controller.sendMessage(msg);
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

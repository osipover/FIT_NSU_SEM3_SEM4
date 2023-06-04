package client.GUI;

import client.GUI.ChatWindow;
import client.controller.ControllerGUI;

import javax.swing.*;
import java.io.IOException;
import java.util.ArrayList;

public class UsersDialog extends JDialog{

    private JPanel mainPanel;
    private JLabel usersLabel;
    private JTextArea usersArea;
    private JButton closeButton;

    public UsersDialog(ChatWindow chatWindow, ControllerGUI controller) {
        initUsersArea(controller);

        initDialog();
    }

    private void initUsersArea(ControllerGUI controller) {
        try {
            controller.requestUsersList();
            usersArea.setEditable(false);
            usersArea.setLineWrap(true);

            ArrayList<String> usersList = null;

            usersList = controller.getUsers();
            if (usersList == null) return;
            for (String user : usersList) {
                usersArea.append(user + "\n");
                usersArea.setCaretPosition(usersArea.getDocument().getLength());
            }
        } catch (IOException e) {
            usersArea.append("No connection\n");
            usersArea.setCaretPosition(usersArea.getDocument().getLength());
        }
    }

    private void initDialog() {
        setContentPane(mainPanel);
        setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        setSize(360, 160);
        setLocationRelativeTo(null);
        setVisible(true);
    }
}

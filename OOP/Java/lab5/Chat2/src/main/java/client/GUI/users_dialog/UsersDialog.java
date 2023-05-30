package client.GUI.users_dialog;

import client.GUI.ChatWindow;
import client.controller.ControllerGUI;

import javax.swing.*;
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
        usersArea.setEditable(false);
        usersArea.setLineWrap(true);

        ArrayList<String> usersList = controller.requestUsersList();
        if (usersList == null) return;
        for (String user : usersList) {
            usersArea.append(user + "\n");
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

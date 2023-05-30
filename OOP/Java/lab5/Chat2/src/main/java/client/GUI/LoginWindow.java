package client.GUI;



import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginWindow extends JFrame {
    private JPanel loginPanel;
    private JTextField fieldUsername;
    private JTextField fieldServerIP;
    private JTextField fieldPort;
    private JButton connectButton;
    private JPanel panelUsername;
    private JPanel panelServerIP;
    private JPanel panelServerPort;
    private JLabel labelServerIP;
    private JLabel labelServerPort;
    private JLabel labelUsername;
    private JPanel buttonPanel;

    public LoginWindow() {
        connectButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = fieldUsername.getText();
                String serverIP = fieldServerIP.getText();
                int serverPort = Integer.parseInt(fieldPort.getText());

                new ChatWindow(username, serverIP, serverPort);            }
        });

        setContentPane(loginPanel);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setSize(300, 200);
        setLocationRelativeTo(null);
        setVisible(true);
    }
}

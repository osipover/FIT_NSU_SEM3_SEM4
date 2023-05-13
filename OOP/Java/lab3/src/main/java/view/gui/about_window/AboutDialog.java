package view.gui.about_window;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AboutDialog extends JDialog {
    private static String info;

    public AboutDialog(JFrame owner) {
        super(owner, "About", true);
        generateInfo();
        add(new JLabel(info), BorderLayout.CENTER);

        JButton okButton = new JButton("OK");
        okButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });

        JPanel panel = new JPanel();
        panel.add(okButton);
        add(panel, BorderLayout.SOUTH);
        setSize(360, 400);
        setLocationRelativeTo(null);
    }

    private static void generateInfo() {
        info = """
                <html>
                    <h2>Minesweeper rules</h2>
                    <h3>
                        Your task is to open all the non-mined cells on the field.
                        Your task is to open all the non-mined cells on the field.
                        The numbers on the cage show how many bombs are around.
                        Place flags on the cells with potential bombs.
                    </h3>
                    <h3>
                        Press LMB to open the cell.<br>
                        Press RMB to place/remove the flag.
                    </h3>
                    <h3>If you open a cell with a bomb, you will lose.</h3>
                    <h3>Good luck!</h3>
                   
                </html>
                """;
    }
}

package view.gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Stopwatch extends Label implements ActionListener {
    private Timer timer;
    private int hours, minutes, seconds;

    public Stopwatch() {
        super("00:00:00", SwingConstants.CENTER);
        setSize(300, 200);
        timer = new Timer(1000, this);
    }

    public void start() {
        timer.start();
    }

    public void stop() {
        timer.stop();
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        seconds++;
        if (seconds >= 60) {
            seconds = 0;
            minutes++;
        }
        if (minutes >= 60) {
            minutes = 0;
            hours++;
        }
        updateLabel();
    }

    private void updateLabel() {
        String str = String.format("%02d:%02d:%02d", hours, minutes, seconds);
        setText(str);
    }
}

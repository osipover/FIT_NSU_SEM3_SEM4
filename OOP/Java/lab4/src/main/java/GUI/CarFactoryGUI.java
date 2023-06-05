package GUI;

import GUI.components.*;
import GUI.controllerGUI.ControllerGUI;
import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CarFactoryGUI extends JFrame {
    private ControllerGUI controller;

    private JPanel suppliersSliderPanel;
    private JPanel dealerSliderPanel;
    private JPanel buttonsPanel;

    private CarInfoPanel carInfoPanel;
    private EngineInfoPanel engineInfoPanel;
    private BodyInfoPanel bodyInfoPanel;
    private AccessoryInfoPanel accessoryInfoPanel;

    public CarFactoryGUI() {
        controller = new ControllerGUI();
        controller.initFactory();

        initSuppliersSliderPanel();
        initDealerSliderPanel();
        initProductsInfoPanels();
        initButtonsPanel();
        initFrame();
    }

    private void initProductsInfoPanels() {
        carInfoPanel = new CarInfoPanel(controller);
        add(carInfoPanel);

        engineInfoPanel = new EngineInfoPanel(controller);
        add(engineInfoPanel);

        bodyInfoPanel = new BodyInfoPanel(controller);
        add(bodyInfoPanel);

        accessoryInfoPanel = new AccessoryInfoPanel(controller);
        add(accessoryInfoPanel);
    }

    private void initButtonsPanel() {
        buttonsPanel = new JPanel();
        JButton startButton = createStartButton();
        JButton stopButton = createStopButton();

        buttonsPanel.add(startButton);
        buttonsPanel.add(stopButton);

        buttonsPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        add(buttonsPanel, BorderLayout.SOUTH);
    }

    private JButton createStopButton() {
        JButton stopButton = new JButton("Stop");
        stopButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.stopFactory();
            }
        });
        return stopButton;
    }

    private JButton createStartButton() {
        JButton startButton = new JButton("Start");
        startButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.startFactory();
            }
        });
        return startButton;
    }

    private void initDealerSliderPanel() {
        dealerSliderPanel = new JPanel();
        suppliersSliderPanel.setLayout(new FlowLayout());

        JSlider speedDealerSlider = createSlider();
        speedDealerSlider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                JSlider source = (JSlider) e.getSource();
                controller.setDealerSpeed(source.getValue());
            }
        });
        dealerSliderPanel.add(speedDealerSlider);

        dealerSliderPanel.setPreferredSize(new Dimension(250, 250));
        dealerSliderPanel.setMaximumSize(new Dimension(250, 250));
        dealerSliderPanel.setBorder(BorderFactory.createTitledBorder("Dealer's delay"));
        add(dealerSliderPanel);

    }

    private void initSuppliersSliderPanel() {
        suppliersSliderPanel = new JPanel();
        suppliersSliderPanel.setLayout(new FlowLayout());

        JSlider speedEngineSupplier = createSlider();
        speedEngineSupplier.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                JSlider source = (JSlider) e.getSource();
                controller.setEngineSupplierSpeed(source.getValue());
            }
        });

        JSlider speedBodySupplier = createSlider();
        speedBodySupplier.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                JSlider source = (JSlider) e.getSource();
                controller.setBodySupplierSpeed(source.getValue());
            }
        });

        JSlider speedAccessorySupplier = createSlider();
        speedAccessorySupplier.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                JSlider source = (JSlider) e.getSource();
                controller.setAccessorySupplierSpeed(source.getValue());
            }
        });

        suppliersSliderPanel.add(speedEngineSupplier);
        suppliersSliderPanel.add(speedBodySupplier);
        suppliersSliderPanel.add(speedAccessorySupplier);

        suppliersSliderPanel.setPreferredSize(new Dimension(250, 250));
        suppliersSliderPanel.setMaximumSize(new Dimension(250, 250));
        suppliersSliderPanel.setBorder(BorderFactory.createTitledBorder("Delay: engine, body, accessory"));
        add(suppliersSliderPanel);
    }

    private JSlider createSlider() {
        JSlider slider = new JSlider(JSlider.VERTICAL, 0, 1000, 100);
        slider.setMajorTickSpacing(250);
        slider.setMinorTickSpacing(50);
        slider.setPaintLabels(true);
        slider.setPaintTicks(true);
        return slider;
    }

    void initFrame() {
        setLayout(new FlowLayout(FlowLayout.LEFT));
        setSize(new Dimension(600, 400));
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setResizable(false);
        setVisible(true);
    }
}

package GUI.components;

import GUI.controllerGUI.ControllerGUI;

import javax.swing.*;

public class CarInfoPanel extends ProductInfoPanel {
    public CarInfoPanel(ControllerGUI controller) {
        super();
        controller.setCarWarehouseObserver(this);
        setBorder(BorderFactory.createTitledBorder("Cars"));
    }
}

package GUI.components;

import GUI.controllerGUI.ControllerGUI;

import javax.swing.*;

public class BodyInfoPanel extends ProductInfoPanel {
    public BodyInfoPanel(ControllerGUI controller) {
        super();
        controller.setBodyWarehouseObserver(this);
        setBorder(BorderFactory.createTitledBorder("Bodies"));
    }
}

package GUI.components;

import GUI.controllerGUI.ControllerGUI;

import javax.swing.*;

public class AccessoryInfoPanel extends ProductInfoPanel {
    public AccessoryInfoPanel(ControllerGUI controller) {
        super();
        controller.setAccessoryWarehouseObserver(this);
        setBorder(BorderFactory.createTitledBorder("Accessories"));
    }
}

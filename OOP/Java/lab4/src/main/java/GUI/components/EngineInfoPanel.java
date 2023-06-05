package GUI.components;

import GUI.controllerGUI.ControllerGUI;

import javax.swing.*;

public class EngineInfoPanel extends ProductInfoPanel {
    public EngineInfoPanel(ControllerGUI controller) {
        super();
        controller.setEngineWarehouseObserver(this);
        setBorder(BorderFactory.createTitledBorder("Engines"));
    }
}

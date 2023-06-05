package GUI.controllerGUI;

import factory.Factory;
import observer.Observer;

public class ControllerGUI {
    private Factory factory;

    public ControllerGUI() { }

    public void initFactory() {
        this.factory = new Factory();
    }

    public void startFactory() {
        factory.start();
    }

    public void stopFactory() {
        factory.stop();
    }

    public void setEngineSupplierSpeed(int value) {
        factory.setEngineSupplierSpeed(value);
    }

    public void setBodySupplierSpeed(int value) {
        factory.setBodySupplierSpeed(value);
    }

    public void setAccessorySupplierSpeed(int value) {
        factory.setAccessorySupplierSpeed(value);
    }

    public void setDealerSpeed(int value) {
        factory.setDealerSpeed(value);
    }

    public void setEngineWarehouseObserver(Observer observer) {
        factory.setEngineWarehouseObserver(observer);
    }

    public void setBodyWarehouseObserver(Observer observer) {
        factory.setBodyWarehouseObserver(observer);
    }

    public void setAccessoryWarehouseObserver(Observer observer) {
        factory.setAccessoryWarehouseObserver(observer);
    }

    public void setCarWarehouseObserver(Observer observer) {
        factory.setCarWarehouseObserver(observer);
    }
}

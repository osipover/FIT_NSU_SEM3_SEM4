package factory;

import factory.assembly.AssemblyDepartment;
import factory.controller.CarWarehouseController;
import factory.dealer.Dealer;
import factory.product.details.Accessory;
import factory.product.details.Body;
import factory.product.Car;
import factory.product.details.Engine;
import factory.supplier.Supplier;
import factory.warehouse.Warehouse;
import factory.factory_config.FactoryConfig;
import observer.Observer;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import java.util.ArrayList;

public class Factory {
    private static final Logger log = LogManager.getLogger(Factory.class);

    private final Warehouse<Body> bodyWarehouse;
    private final Warehouse<Engine> engineWarehouse;
    private final Warehouse<Accessory> accessoryWarehouse;
    private final Warehouse<Car> carWarehouse;
    private final Supplier<Body> bodySupplier;
    private final Supplier<Engine> engineSupplier;
    private final ArrayList<Supplier<Accessory>> accessorySuppliers = new ArrayList<>();
    private final ArrayList<Dealer> dealers = new ArrayList<>();
    private final AssemblyDepartment carAssemblyDepartment;
    private final CarWarehouseController controller;

    public Factory() {
        FactoryConfig.init();
        this.bodyWarehouse = new Warehouse<>(FactoryConfig.getWarehouseBodySize());
        this.engineWarehouse = new Warehouse<>(FactoryConfig.getWarehouseEngineSize());
        this.accessoryWarehouse = new Warehouse<>(FactoryConfig.getWarehouseAccessorySize());
        this.carWarehouse = new Warehouse<>(FactoryConfig.getWarehouseCarSize());

        this.bodySupplier = new Supplier<>(bodyWarehouse, Body.class);
        this.engineSupplier = new Supplier<>(engineWarehouse, Engine.class);
        this.carAssemblyDepartment = new AssemblyDepartment(FactoryConfig.getNumOfWorkers());

        for (int i = 0; i < FactoryConfig.getNumOfAccessorySuppliers(); ++i) {
            accessorySuppliers.add(new Supplier<>(accessoryWarehouse, Accessory.class));
        }
        for (int i = 0; i < FactoryConfig.getNumOfDealers(); ++i) {
            dealers.add(new Dealer(carWarehouse, i));
        }

        controller = new CarWarehouseController(bodyWarehouse,
                engineWarehouse,
                accessoryWarehouse,
                carWarehouse,
                carAssemblyDepartment);

        log.info("Factory was created");
    }

    public void start() {
        log.info("Factory was started");

        bodySupplier.start();
        engineSupplier.start();
        for (Supplier<Accessory> accessorySupplier : accessorySuppliers) {
            accessorySupplier.start();
        }
        for (Dealer dealer : dealers) {
            dealer.start();
        }
        carAssemblyDepartment.start();
    }

    public void stop() {
        for (Dealer dealer : dealers) {
            dealer.interrupt();
        }
        carAssemblyDepartment.stop();
        bodySupplier.interrupt();
        engineSupplier.interrupt();
        for (Supplier<Accessory> accessorySupplier : accessorySuppliers) {
            accessorySupplier.interrupt();
        }

        log.info("Factory was stopped");
    }

    public void setEngineSupplierSpeed(int value) {
        engineSupplier.setSpeed(value);
    }

    public void setBodySupplierSpeed(int value) {
        bodySupplier.setSpeed(value);
    }

    public void setAccessorySupplierSpeed(int value) {
        for (Supplier<Accessory> supplier : accessorySuppliers) {
            supplier.setSpeed(value);
        }
    }

    public void setDealerSpeed(int value) {
        for (Dealer dealer : dealers) {
            dealer.setSpeed(value);
        }
    }

    public void setEngineWarehouseObserver(Observer observer) {
        engineWarehouse.registerObserver(observer);
    }

    public void setBodyWarehouseObserver(Observer observer) {
        bodyWarehouse.registerObserver(observer);
    }

    public void setAccessoryWarehouseObserver(Observer observer) {
        accessoryWarehouse.registerObserver(observer);
    }

    public void setCarWarehouseObserver(Observer observer) {
        carWarehouse.registerObserver(observer);
    }
}

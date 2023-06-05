package factory.controller;

import factory.assembly.AssemblyDepartment;
import factory.assembly.CarAssemblyTask;
import factory.product.Car;
import factory.product.details.Accessory;
import factory.product.details.Body;
import factory.product.details.Engine;
import factory.warehouse.Warehouse;
import observer.Observer;

public class CarWarehouseController implements Observer{
    private Warehouse<Body> bodyWarehouse;
    private Warehouse<Engine> engineWarehouse;
    private Warehouse<Accessory> accessoryWarehouse;
    private Warehouse<Car> carWarehouse;
    private final AssemblyDepartment assemblyDepartment;

    public CarWarehouseController(Warehouse<Body> bodyWarehouse,
                                  Warehouse<Engine> engineWarehouse,
                                  Warehouse<Accessory> accessoryWarehouse,
                                  Warehouse<Car> carWarehouse,
                                  AssemblyDepartment assemblyDepartment) {
        this.bodyWarehouse = bodyWarehouse;
        this.engineWarehouse = engineWarehouse;
        this.accessoryWarehouse = accessoryWarehouse;
        this.carWarehouse = carWarehouse;
        this.assemblyDepartment = assemblyDepartment;

        carWarehouse.registerObserver(this);

        for (int i = 0; i < carWarehouse.capacity(); ++i) {
            assignTask();
        }
    }

    private void assignTask() {
        assemblyDepartment.addTask(new CarAssemblyTask(bodyWarehouse,
                engineWarehouse,
                accessoryWarehouse,
                carWarehouse ));
    }

    @Override
    public void update(int totalProducts, int currentNumProducts) {
        int numOfAssemblingCar = assemblyDepartment.getNumOfTasks();
        int numOfCarsInWarehouse = carWarehouse.getNumOfProducts();
        int capacityOfCarWarehouse = carWarehouse.capacity();

        if (numOfAssemblingCar + numOfCarsInWarehouse < capacityOfCarWarehouse) {
            for (int i = 0; i < capacityOfCarWarehouse - numOfCarsInWarehouse - numOfAssemblingCar; ++i) {
                assignTask();
            }
        }
    }
}

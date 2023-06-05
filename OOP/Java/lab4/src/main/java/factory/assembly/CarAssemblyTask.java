package factory.assembly;

import factory.product.Car;
import factory.product.details.Accessory;
import factory.product.details.Body;
import factory.product.details.Engine;
import factory.warehouse.Warehouse;
import threadpool.Task;

public class CarAssemblyTask implements Task {
    private Warehouse<Body> bodyWarehouse;
    private Warehouse<Engine> engineWarehouse;
    private Warehouse<Accessory> accessoryWarehouse;
    private Warehouse<Car> carWarehouse;

    public CarAssemblyTask(Warehouse<Body> bodyWarehouse,
                           Warehouse<Engine> engineWarehouse,
                           Warehouse<Accessory> accessoryWarehouse,
                           Warehouse<Car> carWarehouse) {
        this.bodyWarehouse = bodyWarehouse;
        this.engineWarehouse = engineWarehouse;
        this.accessoryWarehouse = accessoryWarehouse;
        this.carWarehouse = carWarehouse;
    }

    @Override
    public void execute() {
        Body body = bodyWarehouse.takeProduct();
        Engine engine = engineWarehouse.takeProduct();
        Accessory accessory = accessoryWarehouse.takeProduct();

        if (body == null || engine == null || accessory == null) {
            bodyWarehouse.putProduct(body);
            engineWarehouse.putProduct(engine);
            accessoryWarehouse.putProduct(accessory);
            return;
        }

        Car car = new Car(body, engine, accessory);
        carWarehouse.putProduct(car);
    }
}

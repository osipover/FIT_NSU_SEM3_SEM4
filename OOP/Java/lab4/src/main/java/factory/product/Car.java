package factory.product;

import factory.product.details.Accessory;
import factory.product.details.Body;
import factory.product.details.Engine;
import factory.product.details.Product;
import java.util.concurrent.atomic.AtomicInteger;

public class Car extends Product {
    private static AtomicInteger countOfCars = new AtomicInteger(1);
    private final int id;
    private Body body;
    private Engine engine;
    private Accessory accessory;

    public Car(Body body, Engine engine, Accessory accessory) {
        this.body = body;
        this.engine = engine;
        this.accessory = accessory;
        this.id = countOfCars.getAndIncrement();
    }

    @Override
    public String toString() {
        String str = String.format("Auto %d (Body: %d, Engine: %d, Accessory: %d)", id, body.getId(), engine.getId(), accessory.getId());
        return str;
    }
}

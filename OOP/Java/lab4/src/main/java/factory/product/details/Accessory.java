package factory.product.details;

import factory.product.details.Detail;

import java.util.UUID;
import java.util.concurrent.atomic.AtomicInteger;

public class Accessory extends Detail {
    private static AtomicInteger countOfAccessories = new AtomicInteger(1);
    private final int id;

    public Accessory() {
        id = countOfAccessories.getAndIncrement();
    }

    public int getId() {
        return this.id;
    }
}

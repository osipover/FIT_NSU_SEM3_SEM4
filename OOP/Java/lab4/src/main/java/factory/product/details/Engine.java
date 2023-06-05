package factory.product.details;

import factory.product.details.Detail;

import java.util.UUID;
import java.util.concurrent.atomic.AtomicInteger;

public class Engine extends Detail {
    private static AtomicInteger countOfEngines = new AtomicInteger(1);
    private final int id;

    public Engine() {
        id = countOfEngines.getAndIncrement();
    }

    public int getId() {
        return this.id;
    }
}

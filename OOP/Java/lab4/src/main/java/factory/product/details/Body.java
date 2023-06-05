package factory.product.details;

import java.util.concurrent.atomic.AtomicInteger;

public class Body extends Detail {
    private static AtomicInteger countOfBodies = new AtomicInteger(1);
    private final int id;

    public Body() {
        id = countOfBodies.getAndIncrement();
    }

    public int getId() {
        return id;
    }
}

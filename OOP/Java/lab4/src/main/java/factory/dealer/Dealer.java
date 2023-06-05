package factory.dealer;

import factory.Factory;
import factory.product.Car;
import factory.warehouse.Warehouse;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

public class Dealer extends Thread {
    private static final Logger log = LogManager.getLogger(Factory.class);
    private final int DEFAULT_SPEED = 20;
    private final Warehouse<Car> warehouseCar ;
    private int speed;

    public Dealer(Warehouse<Car> warehouseCar, Integer number) {
        super(number.toString());
        this.warehouseCar = warehouseCar;
        this.speed = DEFAULT_SPEED;
    }

    public void setSpeed(int value) {
        this.speed = value;
    }

    @Override
    public void run() {
        while (!Thread.interrupted()) {
            try {
                sleep(speed);
                Car car = warehouseCar.takeProduct();
                if (car != null) {
                    log.info("Dealer" + currentThread().getName() + ":" + car.toString());
                }
            } catch (InterruptedException ex) {
                return;
            }
        }
    }

}

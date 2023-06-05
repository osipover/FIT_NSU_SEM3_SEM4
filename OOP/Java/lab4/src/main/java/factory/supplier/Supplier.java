package factory.supplier;

import factory.product.details.Detail;
import factory.warehouse.Warehouse;

public class Supplier <T extends Detail> extends Thread {
    private final int DEFAULT_SPEED = 20;
    private final Warehouse<T> warehouse;
    private final Class<T> typeOfDetail;
    private int speed;

    public Supplier(Warehouse<T> warehouse, Class<T> typeOfDetail) {
        super(typeOfDetail.getName());
        this.warehouse = warehouse;
        this.typeOfDetail = typeOfDetail;
        this.speed = DEFAULT_SPEED;
    }

    public void setSpeed(int value) {
        this.speed = value;
    }

    @Override
    public void run() {
        while (!Thread.interrupted()) {
            try  {
                Thread.sleep(speed);
                T item = typeOfDetail.getDeclaredConstructor().newInstance();
                warehouse.putProduct(item);
            }
            catch (InterruptedException ex) {
                return;
            }
            catch (RuntimeException ex) {}
            catch (ReflectiveOperationException ex) {}
        }
    }



}

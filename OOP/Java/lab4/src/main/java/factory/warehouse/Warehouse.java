package factory.warehouse;

import factory.product.Car;
import factory.product.details.Product;
import observer.Observable;
import observer.Observer;
import java.util.ArrayList;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.atomic.AtomicInteger;

public class Warehouse<T extends Product> implements Observable {
    private ArrayList<Observer> observers;
    private final ArrayBlockingQueue<T> storage;
    private final int capacity;
    private AtomicInteger totalProducts;

    public Warehouse(int capacity) {
        this.storage = new ArrayBlockingQueue<>(capacity);
        this.capacity = capacity;
        this.totalProducts = new AtomicInteger(0);
        this.observers = new ArrayList<>();
    }

    public void putProduct(T item) {
        if (item == null) return;
        synchronized (storage) {
            while (isStorageFull() && !Thread.currentThread().isInterrupted()) {
                try {
                    storage.wait();
                } catch (InterruptedException ex) {
                    return;
                }
            }
            storage.add(item);
            storage.notifyAll();
            notifyObservers(totalProducts.incrementAndGet(), storage.size());
        }
    }

    public T takeProduct() {
        T product = null;
        synchronized (storage) {
            while (isStorageEmpty() && !Thread.currentThread().isInterrupted()) {
                try {
                    storage.wait();
                } catch (InterruptedException ex) {
                    return product;
                }
            }
            product = storage.remove();
            storage.notifyAll();
            if (product instanceof Car) {
                notifyObservers(totalProducts.get(), getNumOfProducts());
            }
        }
        return product;
    }

    public boolean isStorageEmpty() {
        return storage.isEmpty();
    }

    public boolean isStorageFull() {
        return storage.remainingCapacity() == 0;
    }

    public int getNumOfProducts() {
        return storage.size();
    }

    public int capacity() {
        return capacity;
    }

    @Override
    public void registerObserver(Observer observer) {
        observers.add(observer);
    }

    @Override
    public void unregisterObserver(Observer observer) {
        observers.remove(observer);
    }

    @Override
    public void notifyObservers(int totalProducts, int currentNumProducts) {
        for (Observer observer : observers) {
            observer.update(totalProducts, currentNumProducts);
        }
    }
}

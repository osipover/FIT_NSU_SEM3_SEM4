package server.limited_queue;

import java.util.concurrent.ArrayBlockingQueue;

public class LimitedQueue<T>  {
    private ArrayBlockingQueue<T> queue;
    private int capacity;


    public LimitedQueue(int capacity) {
        queue = new ArrayBlockingQueue<>(capacity);
        this.capacity = capacity;
    }

    public void add(T item) {
        if (queue.size() == capacity) {
            try {
                queue.take();
            } catch (InterruptedException ex) {}
        }
        queue.add(item);
    }

    public ArrayBlockingQueue<T> getQueue() {
        return queue;
    }

}

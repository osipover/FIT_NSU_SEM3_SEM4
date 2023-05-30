package server.limited_queue;

import java.util.Iterator;
import java.util.Queue;
import java.util.Spliterator;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.function.Consumer;

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

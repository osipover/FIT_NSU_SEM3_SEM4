package threadpool;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ThreadPool {
    private BlockingQueue<Task> tasks;
    private List<WorkerThread> threads;

    public ThreadPool(int numThreads) {
        this.tasks = new LinkedBlockingQueue<>();
        this.threads = new ArrayList<>(numThreads);
    }

    public void addThread(WorkerThread thread) {
        thread.setTasks(tasks);
        threads.add(thread);
    }

    public void start() {
        for (WorkerThread thread : threads) {
            thread.start();
        }
    }

    public void addTask(Task task) {
        tasks.add(task);
    }

    public void stop() {
        for (WorkerThread thread : threads) {
            thread.interrupt();
        }
    }


    public int getNumOfTasks() {
        return tasks.size();
    }

}

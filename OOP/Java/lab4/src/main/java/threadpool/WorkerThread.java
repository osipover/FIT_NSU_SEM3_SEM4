package threadpool;

import java.util.concurrent.BlockingQueue;

public class WorkerThread extends Thread {
    private BlockingQueue<Task> tasks;

    void setTasks(BlockingQueue<Task> tasks) {
        this.tasks = tasks;
    }

    @Override
    public void run() {
        while(!Thread.interrupted()) {
            Task task;
            try {
                task = tasks.take();
                task.execute();
            } catch (InterruptedException ex) {
                return;
            }
        }
    }
}

package factory.assembly;

import threadpool.ThreadPool;

public class AssemblyDepartment {
    private final ThreadPool workers;

    public AssemblyDepartment(int numOfWorkers) {
        workers = new ThreadPool(numOfWorkers);
        for (int i = 0; i < numOfWorkers; ++i) {
            workers.addThread(new Worker());
        }
    }

    public int getNumOfTasks() {
        return workers.getNumOfTasks();
    }

    public void addTask(CarAssemblyTask task) {
        workers.addTask(task);
    }

    public void start() {
        workers.start();
    }

    public void stop() {
        workers.stop();
    }
}

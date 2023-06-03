#include <iostream>
#include <mpi.h>
#include <pthread.h>
#include <memory>
#include <math.h>
#include "tasklist.h"

#define L 800
#define ITER_MAX 20

typedef struct ContextMPI{
    int rank;
    int numProc;
} ContextMPI;

pthread_barrier_t barrier;

pthread_mutex_t mutex;

pthread_cond_t condWait;
pthread_cond_t condWork;

bool isThreadRunning;

std::unique_ptr<TaskList> taskList;

double globalRes = 0;

void generateTaskList(ContextMPI *contextmpi, int numTasks, int iterCounter) {
    for (int i = contextmpi->rank * numTasks; i < contextmpi->rank * numTasks + numTasks; ++i) {
        int task = abs(50 - (i % 100)) * abs(contextmpi->rank - (iterCounter % contextmpi->numProc)) * L;
        taskList->push(task);
    }
}

void* sender(void* context) {
    ContextMPI *contextmpi = (ContextMPI *) context;

    MPI_Status status;
    int rankSender;

    for (int i = 0; i < ITER_MAX; ++i) {
        pthread_barrier_wait(&barrier);

        while(isThreadRunning) {
            MPI_Recv(&rankSender, 1, MPI_INT, MPI_ANY_SOURCE, TAG_REQUEST_TASK, MPI_COMM_WORLD, &status);
            if(rankSender == STOP_WORK) continue;
            int task = taskList->pop();
            MPI_Send(&task, 1, MPI_INT, rankSender, TAG_SEND_TASK, MPI_COMM_WORLD);
        }
    }
    return nullptr;
}

void finishWork(ContextMPI *contextmpi, const int recvTask) {
    MPI_Barrier(MPI_COMM_WORLD);
    isThreadRunning = false;

    MPI_Send(&recvTask, 1, MPI_INT, contextmpi->rank, TAG_REQUEST_TASK, MPI_COMM_WORLD);

    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&condWork);
    pthread_mutex_unlock(&mutex);
}

void* receiver(void* context) {
    ContextMPI *contextmpi = (ContextMPI *) context;
    
    int recvTask;
    MPI_Status status;

    for (int i = 0; i < ITER_MAX; ++i) {
        pthread_barrier_wait(&barrier);

        while(isThreadRunning) {
            while (!taskList->empty()) {
                pthread_mutex_lock(&mutex);
                pthread_cond_signal(&condWork);
                pthread_cond_wait(&condWait, &mutex);
                pthread_mutex_unlock(&mutex);
            }
            int numCompletedProc = 0;
            for (int i = 0; i < contextmpi->numProc; ++i) {
                if(i == contextmpi->rank) continue;
                MPI_Send(&contextmpi->rank, 1, MPI_INT, i, TAG_REQUEST_TASK, MPI_COMM_WORLD);
                MPI_Recv(&recvTask, 1, MPI_INT, i, TAG_SEND_TASK, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if (recvTask != LIST_EMPTY) {
                    taskList->push(recvTask);
                } else { ++numCompletedProc; }
            }
            if(numCompletedProc == contextmpi->numProc - 1)
                finishWork(contextmpi, STOP_WORK);
        }
    }
    return nullptr;
}

void taskExecute(int repeatNum) {
    for (int i = 0; i < repeatNum; ++i) {
        globalRes += sin(i);
    }
}

void printResult(ContextMPI *contextmpi, int i, int countExecutedTasks, double timeToIter) {
    double maxTime = 0;
    double minTime = 0;

    MPI_Reduce(&timeToIter, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&timeToIter, &minTime, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);

    double imbalance = maxTime - minTime;

    printf("ITER: %d, RANK: %d, countExecutedTasks: %d, globalRes: %f, timeToIter: %f\n", i, contextmpi->rank, countExecutedTasks, globalRes, timeToIter);
    if (contextmpi->rank == ROOT) {
        printf("ITER: %d, imbalance: %f, proportion of imbalance: %f %\n", i, imbalance, (imbalance / maxTime) * 100);
    }
}

void worker(void* context) {
    ContextMPI *contextmpi = (ContextMPI *) context;

    for (int i = 0; i < ITER_MAX; ++i) {

        generateTaskList(contextmpi, contextmpi->numProc * 1000, i);
        isThreadRunning = true;
        pthread_barrier_wait(&barrier);

        double startTime = MPI_Wtime();
        int countExecutedTasks = 0;

        while (isThreadRunning) {
            while(true) {
                int task = taskList->pop();
                if (task == LIST_EMPTY) break;
                taskExecute(task);
                ++countExecutedTasks;
            }

            while(taskList->empty() && isThreadRunning) {
                pthread_mutex_lock(&mutex);
                pthread_cond_signal(&condWait);
                pthread_cond_wait(&condWork, &mutex);
                pthread_mutex_unlock(&mutex);
            }
        }
        double endTime = MPI_Wtime();
        printResult(contextmpi, i, countExecutedTasks, endTime - startTime);
    }
}

void run(ContextMPI *contextmpi) {
    pthread_mutex_init(&mutex, nullptr);

    pthread_barrier_init(&barrier, NULL, 3);

    pthread_attr_t attrs;
    pthread_attr_init(&attrs);
    pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_JOINABLE);

    pthread_t threadReceiver;
    pthread_t threadSender;

    pthread_cond_init(&condWait, nullptr);
    pthread_cond_init(&condWork, nullptr);

    taskList = std::make_unique<TaskList>(&mutex, &condWork);

    MPI_Barrier(MPI_COMM_WORLD);

    pthread_create(&threadReceiver, &attrs, receiver, contextmpi);
    pthread_create(&threadSender, &attrs, sender, contextmpi);
    worker(contextmpi);

    pthread_join(threadReceiver, nullptr);
    pthread_join(threadSender, nullptr);

    pthread_attr_destroy(&attrs);
    pthread_cond_destroy(&condWait);
    pthread_cond_destroy(&condWork);
}

int main(int argc, char **argv) {
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);

    ContextMPI contextmpi;
    MPI_Comm_rank(MPI_COMM_WORLD, &contextmpi.rank);
    MPI_Comm_size(MPI_COMM_WORLD, &contextmpi.numProc);

    double startTime = MPI_Wtime();
    run(&contextmpi);
    double endTime = MPI_Wtime();

    if (contextmpi.rank == ROOT)
        printf("\nTIME: %f seconds\n", endTime - startTime);

    MPI_Finalize();

    return 0;
}

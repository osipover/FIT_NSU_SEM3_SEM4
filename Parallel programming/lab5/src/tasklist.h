#pragma once

#include <queue>
#include <pthread.h>

enum {
    TAG_REQUEST_TASK = 0,
    TAG_SEND_TASK = 1,
    ROOT = 0,
    STOP_WORK = -1,
    LIST_EMPTY = -1
};

class TaskList {
private:
    std::queue<int> queue;
    pthread_mutex_t* mutex;
    pthread_cond_t* cond;

public:
    TaskList(pthread_mutex_t* mutex, pthread_cond_t* cond) {
        this->mutex = mutex;
        this->cond = cond;
    }

    void push(const int &task) {
        pthread_mutex_lock(mutex);
        queue.push(task);
        pthread_cond_signal(cond);
        pthread_mutex_unlock(mutex);
    }

    int pop() {
        int task;
        pthread_mutex_lock(mutex);
        if (!queue.empty()) {
            task = queue.front();
            queue.pop();
        } else {
            task = LIST_EMPTY;
        }
        pthread_mutex_unlock(mutex);
        return task;
    }

    bool empty() {
        pthread_mutex_lock(mutex);
        bool isEmpty = queue.empty();
        pthread_mutex_unlock(mutex);

        return isEmpty;
    }
};

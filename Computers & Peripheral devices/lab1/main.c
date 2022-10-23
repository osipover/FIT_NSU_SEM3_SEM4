#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

double PiByGregoryLeibniz(long long int N){
    double pi = 1.0;
    double pow = -1;
    for (long long int i = 1; i <= N; ++i){
        pi += pow/(2*i+1);
        pow *= (-1);
    }
    pi *= 4;
    return pi; 
}

void TestClockGettime(long long int N){
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    double pi = PiByGregoryLeibniz(N);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("Pi: %f\n", pi);
    printf("Time taken by clock_gettime: %lf sec.\n", \
    end.tv_sec - start.tv_sec + 0.000000001*(end.tv_nsec - start.tv_nsec));
}

int main(int argc, char** argv){
    long long int N = 0;
    N = atoll(argv[1]);
    TestClockGettime(N);
    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#define NUM 1000000
#define NUM2 10000000

float time_diff(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

float time_sum(struct timeval *time){
    return(time->tv_sec) + 1e-6*(time->tv_usec);
}

void loopFunc(size_t num)
{
    int tmp = 0;
    for (int i = 0; i < num; ++i) {
        tmp += 1;
    }
}

int main() {
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    loopFunc(NUM);
    gettimeofday(&end, NULL);

    printf("loopFunc(%d)  time spent: %0.8f sec\n",
           NUM, time_diff(&start, &end));


    gettimeofday(&start, NULL);
    printf("Antes %0.8f sec\n", time_sum(&start));
    loopFunc(NUM2);
    gettimeofday(&end, NULL);
    printf("Despues %0.8f sec\n", time_sum(&end));

    printf("loopFunc(%d) time spent: %0.8f sec\n",
           NUM2, time_diff(&start, &end));

    exit(EXIT_SUCCESS);
}
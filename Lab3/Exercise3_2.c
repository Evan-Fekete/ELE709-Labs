#define _POSIX_C_SOURCE 200112L
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

struct thread_info {
    double exec_time; // execution time per iteration in nsec
    int maxitr; // number of iterations to be performed
    char op; // math operation to be performed +,-,*,/
    double a, b, c; // a, b are factors and c is result
};

typedef struct thread_info thread_info_t;

void *func(void *arg)
    {
    struct timespec time_1, time_2;
    int i, maxitr;
    double exec_time;
    thread_info_t *info;

    info = (thread_info_t *)arg;
    maxitr = info->maxitr;

    info->a = 2.3; info->b = 4.5;

    info->exec_time = 0.0;

    clock_gettime(CLOCK_REALTIME, &time_1);

    for (i = 0; i < maxitr ; i++) {
        switch(info->op){
            case '+':
                info->c = info->a + info->b;
                break;
            case '-':
                info->c = info->a - info->b;
                break;
            case '*':
                info->c = info->a * info->b;
                break;
            case '/':
                info->c = info->a / info->b;
                break;
        }
    }
            
    clock_gettime(CLOCK_REALTIME, &time_2);

    exec_time = (time_2.tv_sec - time_1.tv_sec)*1.0e9;
    exec_time = exec_time + (time_2.tv_nsec - time_1.tv_nsec);
    info->exec_time = exec_time/maxitr;

    pthread_exit(NULL);
    
}

int main(void)
{
    pthread_t thread[4];
    thread_info_t *info[4];
    int  maxitr;
    char arithmetic_op[] = {'+','-','*','/'};

    // Create four threads to run arithmetic operations
    for(int i = 0; i < 4; i++){
        // Allocate memory with malloc, done to store threads more efficiently
        info[i] = malloc(sizeof(thread_info_t));

        if (info[i] == NULL) {
            printf("Error allocating memory in thread %d", i+1);
            exit(1);
        }

        maxitr = 5.0e8;
        info[i]->maxitr = (int)maxitr;
        info[i]->op = arithmetic_op[i];

        if (pthread_create(&thread[i], NULL, &func, info[i]) != 0) {
            printf("Error in creating thread %d\n",i+1);
            exit(1);
        }
    }

    // Join threads started in for loop after completion
    for (int i = 0 ; i < 4 ; i++) {
        pthread_join(thread[i], NULL);
        printf("Exec time for %c Operation Thread = %lf nsec\n", arithmetic_op[i], info[i]->exec_time);
    }

    // Free allocated memory
    for (int i = 0; i < 4; i++) {
        free(info[i]);
    }

    return 0;
}

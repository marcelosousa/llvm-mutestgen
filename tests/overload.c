#include <pthread.h>
#include <stdio.h>

int pthread_mutex_lock_ov(pthread_mutex_t *mutex, int cond){
    printf("Mutation number is %d\n",cond);
    return pthread_mutex_lock(mutex);
}
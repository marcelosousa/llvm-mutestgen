#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int getMuNum(){
  char *munum = getenv("MUNUM");
  int num = 0;
  if(munum){
    num = atoi(munum);
  }
  return num;
}

int pthread_mutex_lock_ov(pthread_mutex_t *mutex, int cond){
  int mnum = getMuNum();
  
  if(mnum==cond){
    printf("Mutating %d\n",mnum);
    
  }
  
  return pthread_mutex_lock(mutex);  
}
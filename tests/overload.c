/*
Overloaded PThread Library

Contact: Marcelo Sousa <dipython@gmail.com>

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "overload.h"

// Helper function that retrieves the MUNUM environment variable
int getMuNum(){
  char *munum = getenv("MUNUM");
  int num = 0;
  if(munum){
    num = atoi(munum);
  }
  return num;
}

int   pthread_attr_destroy_ov(pthread_attr_t *attr, int mutid){
  return pthread_attr_destroy(attr);
}

int   pthread_attr_getdetachstate_ov(const pthread_attr_t *attr, int *st, int mutid){
  return pthread_attr_getdetachstate(attr, st);
}

int   pthread_attr_getguardsize_ov(const pthread_attr_t *attr, size_t *s, int mutid){
  return pthread_attr_getguardsize(attr, s);
}

int   pthread_attr_getinheritsched_ov(const pthread_attr_t *attr, int *s, int mutid){
  return pthread_attr_getinheritsched(attr, s);
}

int   pthread_attr_getschedparam_ov(const pthread_attr_t *attr, struct sched_param *param, int mutid){
  return pthread_attr_getschedparam(attr, param);
}

int   pthread_attr_getschedpolicy_ov(const pthread_attr_t *attr, int *s, int mutid){
  return pthread_attr_getschedpolicy(attr, s);
}

int   pthread_attr_getscope_ov(const pthread_attr_t *attr, int *s, int mutid){
  return pthread_attr_getscope(attr, s);
}

int   pthread_attr_getstackaddr_ov(const pthread_attr_t *attr, void **addr, int mutid){
  return pthread_attr_getstackaddr(attr, addr);
}

int   pthread_attr_getstacksize_ov(const pthread_attr_t *attr, size_t *size, int mutid){
  return pthread_attr_getstacksize(attr, size);
}

int   pthread_attr_init_ov(pthread_attr_t *attr, int mutid){
  return pthread_attr_init(attr);
}

int   pthread_attr_setdetachstate_ov(pthread_attr_t *attr, int state, int mutid){
  return pthread_attr_setdetachstate(attr, state);
}

int   pthread_attr_setguardsize_ov(pthread_attr_t *attr, size_t size, int mutid){
  return pthread_attr_setguardsize(attr, size);
}

int   pthread_attr_setinheritsched_ov(pthread_attr_t *attr, int sched, int mutid){
  return pthread_attr_setinheritsched(attr, sched);
}

int   pthread_attr_setschedparam_ov(pthread_attr_t *attr, const struct sched_param *param, int mutid){
  return pthread_attr_setschedparam(attr, param);
}

int   pthread_attr_setschedpolicy_ov(pthread_attr_t *attr, int sched, int mutid){
  return pthread_attr_setschedpolicy(attr, sched);
}

int   pthread_attr_setscope_ov(pthread_attr_t *attr, int scope, int mutid){
  return pthread_attr_setscope(attr, scope);
}

int   pthread_attr_setstackaddr_ov(pthread_attr_t *attr, void *addr, int mutid){
  return pthread_attr_setstackaddr(attr, addr);
}

int   pthread_attr_setstacksize_ov(pthread_attr_t *attr, size_t size, int mutid){
  return pthread_attr_setstacksize(attr, size);
}

int   pthread_cancel_ov(pthread_t thread, int mutid){
  return pthread_cancel(thread);
}

//void  pthread_cleanup_push_ov(void (*routine)(void*), void *arg, int mutid){
//  pthread_cleanup_push(routine, arg);
//}

//void  pthread_cleanup_pop_ov(int execute, int mutid){
//  pthread_cleanup_pop(execute);
//}

int   pthread_cond_broadcast_ov(pthread_cond_t *cond, int mutid){
  return pthread_cond_broadcast(cond);
}

int   pthread_cond_destroy_ov(pthread_cond_t *cond, int mutid){
  return pthread_cond_destroy(cond);
}

int   pthread_cond_init_ov(pthread_cond_t *cond, const pthread_condattr_t *attr, int mutid){
  return pthread_cond_init(cond, attr);
}

int   pthread_cond_signal_ov(pthread_cond_t *cond, int mutid){
  return pthread_cond_signal(cond);
}

int   pthread_cond_timedwait_ov(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *duration, int mutid){
  return pthread_cond_timedwait(cond, mutex, duration);
}

int   pthread_cond_wait_ov(pthread_cond_t *cond, pthread_mutex_t *mutex, int mutid){
  return pthread_cond_wait(cond, mutex);
}

int   pthread_condattr_destroy_ov(pthread_condattr_t *attr, int mutid){
  return pthread_condattr_destroy(attr);
}

int   pthread_condattr_getpshared_ov(const pthread_condattr_t *attr, int *pshared, int mutid){
  return pthread_condattr_getpshared(attr, pshared);
}

int   pthread_condattr_init_ov(pthread_condattr_t *attr, int mutid){
  return pthread_condattr_init(attr);
}

int   pthread_condattr_setpshared_ov(pthread_condattr_t *attr, int pshared, int mutid){
  return pthread_condattr_setpshared(attr, pshared);
}

int   pthread_create_ov(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg, int mutid){
  return pthread_create(thread, attr, start_routine, arg);
}

int   pthread_detach_ov(pthread_t thread, int mutid){
  return pthread_detach(thread);
}

int   pthread_equal_ov(pthread_t t1, pthread_t t2, int mutid){
  return pthread_equal(t1, t2);
}

void  pthread_exit_ov(void *value_ptr, int mutid){
  pthread_exit(pthread_exit);
}

int   pthread_getconcurrency_ov(int mutid){
  return pthread_getconcurrency();
}

int   pthread_getschedparam_ov(pthread_t thread, int *policy, struct sched_param *param, int mutid){
  return pthread_getschedparam(thread, policy, param);
}

void *pthread_getspecific_ov(pthread_key_t key, int mutid){
  return pthread_getspecific(key);
}

int   pthread_join_ov(pthread_t thread, void **value_ptr, int mutid){
  return pthread_join(thread, value_ptr);
}

int   pthread_key_create_ov(pthread_key_t *key, void (*destructor)(void *), int mutid){
  return pthread_key_create(key,destructor);
}

int   pthread_key_delete_ov(pthread_key_t key, int mutid){
  return pthread_key_delete(key);
}

int   pthread_mutex_destroy_ov(pthread_mutex_t *mutex, int mutid){
  return pthread_mutex_destroy(mutex);
}

int   pthread_mutex_getprioceiling_ov(const pthread_mutex_t *mutex, int *prioceiling, int mutid){
  return pthread_mutex_getprioceiling(mutex, prioceiling);
}

int   pthread_mutex_init_ov(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr, int mutid){
  return pthread_mutex_init(mutex, attr);
}

int pthread_mutex_lock_ov(pthread_mutex_t *mutex, int mutid){
  int mnum = getMuNum();
  
  if(mnum==mutid){
    printf("Mutating %d\n",mnum);
    
  }
  
  return pthread_mutex_lock(mutex);  
}

int   pthread_mutex_setprioceiling_ov(pthread_mutex_t *mutex, int prioceiling, int *old_ceiling, int mutid){
  return pthread_mutex_setprioceiling(mutex, prioceiling, old_ceiling);
}

int   pthread_mutex_trylock_ov(pthread_mutex_t *mutex, int mutid){
  return pthread_mutex_trylock(mutex);
}

int   pthread_mutex_unlock_ov(pthread_mutex_t *mutex, int mutid){
  return pthread_mutex_unlock(mutex);
}

int   pthread_mutexattr_destroy_ov(pthread_mutexattr_t *attr, int mutid){
  return pthread_mutexattr_destroy(attr);
}

int   pthread_mutexattr_getprioceiling_ov(const pthread_mutexattr_t *attr, int *prioceiling, int mutid){
  return pthread_mutexattr_getprioceiling(attr, prioceiling);
}

int   pthread_mutexattr_getprotocol_ov(const pthread_mutexattr_t *attr, int *protocol, int mutid){
  return pthread_mutexattr_getprotocol(attr, protocol);
}

int   pthread_mutexattr_getpshared_ov(const pthread_mutexattr_t *attr, int *pshared, int mutid){
  return pthread_mutexattr_getpshared(attr, pshared);
}

int   pthread_mutexattr_gettype_ov(const pthread_mutexattr_t *attr, int *type, int mutid){
  return pthread_mutexattr_gettype(attr, type);
}

int   pthread_mutexattr_init_ov(pthread_mutexattr_t *attr, int mutid){
  return pthread_mutexattr_init(attr);
}

int   pthread_mutexattr_setprioceiling_ov(pthread_mutexattr_t *attr, int prioceiling, int mutid){
  return pthread_mutexattr_setprioceiling(attr, prioceiling);
}

int   pthread_mutexattr_setprotocol_ov(pthread_mutexattr_t *attr, int protocol, int mutid){
  return pthread_mutexattr_setprotocol(attr, protocol);
}

int   pthread_mutexattr_setpshared_ov(pthread_mutexattr_t *attr, int pshared, int mutid){
  return pthread_mutexattr_setpshared(attr, pshared);
}

int   pthread_mutexattr_settype_ov(pthread_mutexattr_t *attr, int type, int mutid){
  return pthread_mutexattr_settype(attr, type);
}

int   pthread_once_ov(pthread_once_t *once_control, void (*init_routine)(void), int mutid){
  return pthread_once(once_control, init_routine);
}

int   pthread_rwlock_destroy_ov(pthread_rwlock_t *rwlock, int mutid){
  return pthread_rwlock_destroy(rwlock);
}

int   pthread_rwlock_init_ov(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr, int mutid){
  return pthread_rwlock_init(rwlock, attr);
}

int   pthread_rwlock_rdlock_ov(pthread_rwlock_t *rwlock, int mutid){
  return pthread_rwlock_rdlock(rwlock);
}

int   pthread_rwlock_tryrdlock_ov(pthread_rwlock_t *rwlock, int mutid){
  return pthread_rwlock_tryrdlock(rwlock);
}

int   pthread_rwlock_trywrlock_ov(pthread_rwlock_t *rwlock, int mutid){
  return pthread_rwlock_trywrlock(rwlock);
}

int   pthread_rwlock_unlock_ov(pthread_rwlock_t *rwlock, int mutid){
  return pthread_rwlock_unlock(rwlock);
}

int   pthread_rwlock_wrlock_ov(pthread_rwlock_t *rwlock, int mutid){
  return pthread_rwlock_wrlock(rwlock);
}

int   pthread_rwlockattr_destroy_ov(pthread_rwlockattr_t *attr, int mutid){
  return pthread_rwlockattr_destroy(attr);
}

int   pthread_rwlockattr_getpshared_ov(const pthread_rwlockattr_t *attr, int *pshared, int mutid){
  return pthread_rwlockattr_getpshared(attr, pshared);
}

int   pthread_rwlockattr_init_ov(pthread_rwlockattr_t *attr, int mutid){
  return pthread_rwlockattr_init(attr);
}

int   pthread_rwlockattr_setpshared_ov(pthread_rwlockattr_t *attr, int pshared, int mutid){
  return pthread_rwlockattr_setpshared(attr, pshared);
}

pthread_t pthread_self_ov(int mutid){
  return pthread_self();
}

int   pthread_setcancelstate_ov(int state, int *oldstate, int mutid){
  return pthread_setcancelstate(state, oldstate);
}

int   pthread_setcanceltype_ov(int type, int *oldtype, int mutid){
  return pthread_setcanceltype(type, oldtype);
}

int   pthread_setconcurrency_ov(int conc, int mutid){
  return pthread_setconcurrency(conc);
}

int   pthread_setschedparam_ov(pthread_t thread, int policy, const struct sched_param *param, int mutid){
  return pthread_setschedparam(thread, policy, param);
}

int   pthread_setspecific_ov(pthread_key_t key, const void *value, int mutid){
  return pthread_setspecific(key, value);
}

void  pthread_testcancel_ov(int mutid){
  pthread_testcancel();
}

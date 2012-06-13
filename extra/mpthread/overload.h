/*

Overloaded PThread Library

Contact: Marcelo Sousa <dipython@gmail.com>

*/

int getMuNum();

int   pthread_attr_destroy_ov(pthread_attr_t *, int);
int   pthread_attr_getdetachstate_ov(const pthread_attr_t *, int *, int);
int   pthread_attr_getguardsize_ov(const pthread_attr_t *, size_t *, int);
int   pthread_attr_getinheritsched_ov(const pthread_attr_t *, int *, int);
int   pthread_attr_getschedparam_ov(const pthread_attr_t *, struct sched_param *, int);
int   pthread_attr_getschedpolicy_ov(const pthread_attr_t *, int *, int);
int   pthread_attr_getscope_ov(const pthread_attr_t *, int *, int);
int   pthread_attr_getstackaddr_ov(const pthread_attr_t *, void **, int);
int   pthread_attr_getstacksize_ov(const pthread_attr_t *, size_t *, int);
int   pthread_attr_init_ov(pthread_attr_t *, int);
int   pthread_attr_setdetachstate_ov(pthread_attr_t *, int, int);
int   pthread_attr_setguardsize_ov(pthread_attr_t *, size_t, int);
int   pthread_attr_setinheritsched_ov(pthread_attr_t *, int, int);
int   pthread_attr_setschedparam_ov(pthread_attr_t *, const struct sched_param *, int);
int   pthread_attr_setschedpolicy_ov(pthread_attr_t *, int, int);
int   pthread_attr_setscope_ov(pthread_attr_t *, int, int);
int   pthread_attr_setstackaddr_ov(pthread_attr_t *, void *, int);
int   pthread_attr_setstacksize_ov(pthread_attr_t *, size_t, int);
int   pthread_cancel_ov(pthread_t, int);
//void  pthread_cleanup_push_ov(void (*routine)(void*), void *arg, int);
//void  pthread_cleanup_pop_ov(int, int);
int   pthread_cond_broadcast_ov(pthread_cond_t *, int);
int   pthread_cond_destroy_ov(pthread_cond_t *, int);
int   pthread_cond_init_ov(pthread_cond_t *, const pthread_condattr_t *, int);
int   pthread_cond_signal_ov(pthread_cond_t *, int);
int   pthread_cond_timedwait_ov(pthread_cond_t *, pthread_mutex_t *, const struct timespec *, int);
int   pthread_cond_wait_ov(pthread_cond_t *, pthread_mutex_t *, int);
int   pthread_condattr_destroy_ov(pthread_condattr_t *, int);
int   pthread_condattr_getpshared_ov(const pthread_condattr_t *, int *, int);
int   pthread_condattr_init_ov(pthread_condattr_t *, int);
int   pthread_condattr_setpshared_ov(pthread_condattr_t *, int, int);
int   pthread_create_ov(pthread_t *, const pthread_attr_t *, void *(*)(void *), void *, int);
int   pthread_detach_ov(pthread_t, int);
int   pthread_equal_ov(pthread_t, pthread_t, int);
void  pthread_exit_ov(void *, int);
int   pthread_getconcurrency_ov(int);
int   pthread_getschedparam_ov(pthread_t, int *, struct sched_param *, int);
void *pthread_getspecific_ov(pthread_key_t, int);
int   pthread_join_ov(pthread_t, void **, int);
int   pthread_key_create_ov(pthread_key_t *, void (*)(void *), int);
int   pthread_key_delete_ov(pthread_key_t, int);
int   pthread_mutex_destroy_ov(pthread_mutex_t *, int);
int   pthread_mutex_getprioceiling_ov(const pthread_mutex_t *, int *, int);
int   pthread_mutex_init_ov(pthread_mutex_t *, const pthread_mutexattr_t *, int);
int   pthread_mutex_lock_ov(pthread_mutex_t *, int);
int   pthread_mutex_setprioceiling_ov(pthread_mutex_t *, int, int *, int);
int   pthread_mutex_trylock_ov(pthread_mutex_t *, int);
int   pthread_mutex_unlock_ov(pthread_mutex_t *, int);
int   pthread_mutexattr_destroy_ov(pthread_mutexattr_t *, int);
int   pthread_mutexattr_getprioceiling_ov(const pthread_mutexattr_t *,int *, int);
int   pthread_mutexattr_getprotocol_ov(const pthread_mutexattr_t *, int *, int);
int   pthread_mutexattr_getpshared_ov(const pthread_mutexattr_t *, int *, int);
int   pthread_mutexattr_gettype_ov(const pthread_mutexattr_t *, int *, int);
int   pthread_mutexattr_init_ov(pthread_mutexattr_t *, int);
int   pthread_mutexattr_setprioceiling_ov(pthread_mutexattr_t *, int, int);
int   pthread_mutexattr_setprotocol_ov(pthread_mutexattr_t *, int, int);
int   pthread_mutexattr_setpshared_ov(pthread_mutexattr_t *, int, int);
int   pthread_mutexattr_settype_ov(pthread_mutexattr_t *, int, int);
int   pthread_once_ov(pthread_once_t *, void (*)(void), int);
int   pthread_rwlock_destroy_ov(pthread_rwlock_t *, int);
int   pthread_rwlock_init_ov(pthread_rwlock_t *,const pthread_rwlockattr_t *, int);
int   pthread_rwlock_rdlock_ov(pthread_rwlock_t *, int);
int   pthread_rwlock_tryrdlock_ov(pthread_rwlock_t *, int);
int   pthread_rwlock_trywrlock_ov(pthread_rwlock_t *, int);
int   pthread_rwlock_unlock_ov(pthread_rwlock_t *, int);
int   pthread_rwlock_wrlock_ov(pthread_rwlock_t *, int);
int   pthread_rwlockattr_destroy_ov(pthread_rwlockattr_t *, int);
int   pthread_rwlockattr_getpshared_ov(const pthread_rwlockattr_t *,int *, int);
int   pthread_rwlockattr_init_ov(pthread_rwlockattr_t *, int);
int   pthread_rwlockattr_setpshared_ov(pthread_rwlockattr_t *, int, int);
pthread_t pthread_self_ov(int);
int   pthread_setcancelstate_ov(int, int *, int);
int   pthread_setcanceltype_ov(int, int *, int);
int   pthread_setconcurrency_ov(int, int);
int   pthread_setschedparam_ov(pthread_t, int, const struct sched_param *, int);
int   pthread_setspecific_ov(pthread_key_t, const void *, int);
void  pthread_testcancel_ov(int);

//
#include <pthread.h>

struct rwlock_t{
    pthread mutex_t mutex;

    pthread_cond_t read;
    pthread_cond_t write;

    int read_now;
    int read_wait;
    int write_now;
    int write_wait;
}

void rwlock_init(rwlock_t* rwlock);
void rwlock_destroy(rwlock_t* rwlock);
void rwlock_rdlock(rwlock_t* rwlock);
void rwlock_wrlock(rwlock_t* rwlock);
void rwlock_unlock(rwlock_t* rwlock);
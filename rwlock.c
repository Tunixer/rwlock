#include "rwlock.h"
void rwlock_init(rwlock_t* rwlock){
    pthread_mutex_init(&(rwlock->mutex), NULL);
    
    pthread_cond_init(&(rwlock->read), NULL);
    pthread_cond_init(&(rwlock->write), NULL);

    rwlock->read_now = 0;
    rwlock->read_wait = 0;
    rwlock->write_now = 0;
    rwlock->write_wait = 0;
}

void rwlock_destroy(rwlock_t* rwlock){
    pthread_mutex_destroy(&(rwlock->mutex));
    pthread_cond_destroy(&(rwlock->read));
    pthread_cond_destroy(&(rwlock->write));
}

void rwlock_rdlock(rwlock_t* rwlock){
    pthread_mutex_lock(&(rwlock->mutex));
    if(rwlock->write_now == 0) rwlock->read_now += 1;
    else{
        rwlock->read_wait += 1;
        pthread_cond_wait(&(rwlock->read), &(rwlock->mutex));

        rwlock->read_wait = rwlock->read_wait - 1;
        rwlock->read_now = rwlock->read_now + 1;
    }
    pthread_mutex_unlock(&(rwlock->mutex));
}

void rwlock_wrlock(rwlock_t* rwlock){
    pthread_mutex_lock(&(rwlock->mutex));    
    //No write and read
    if(rwlock->read_now == 0 && rwlock->write_now) rwlock->write_now += 1;
    else{
        pthread_cond_wait(&(rwlock->write),&(rwlock->mutex));

        rwlock->write_wait -= 1;
        rwlock->write_now += 1;
    }
    pthread_mutex_unlock(&(rwlock->mutex));
}

void rwlock_unlock(rwlock_t* rwlock){
    pthread_mutex_lock(&(rwlock->mutex)); 
    if(rwlock->read_now > 1) rwlock->read_now --;
    else if (rwlock->read_now == 1){
        rwlock->read_now--;
        if(rwlock->write_wait > 0) pthread_cond_signal(&(rwlock->write));
    }else{
        rwlock->write_now--;
    }
    pthread_mutex_unlock(&(rwlock->mutex));
}

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "ListNode.h"

#define NUM_THREADS 8
#define NUM_ITER 10

typedef struct{
	int	threadId;
    ListNode* listHead;
    rwlock_t* rwlock_;
} threadParm_t;


void Print(ListNode* head){
    ListNode* p = head->next;
    printf("List: ");
    for(; p != NULL; p = p->next){
        printf("%d ",p->val);
    }
    printf("\n");
}


int n_iter = NUM_ITER;

void *rwlock_Find(void *parm)
{
    threadParm_t *p = (threadParm_t *) parm;
    int r = p->threadId;
    ListNode* ListHead = p->listHead;
    rwlock_t* rwlock_ = p->rwlock_;

    for(int i = 0; i < n_iter; i++){
        int x = rand()% NUM_ITER ;
        rw_Find(ListHead, rwlock_, &x, 0);
        //printf("Thread: %d, In Iter: %d, find %d\n\n",r,i,x);
    }

    pthread_exit(NULL);
}

void *rwlock_Insert(void *parm)
{
    threadParm_t *p = (threadParm_t *) parm;
    int r = p->threadId;
    ListNode* ListHead = p->listHead;
    rwlock_t* rwlock_ = p->rwlock_;

    for(int i = 0; i < n_iter; i++){
        int x = rand()% (NUM_ITER*1000);
        rw_Insert(ListHead, rwlock_, x, 0);
        //printf("In Iter: %d, Insert %d\n",i,x);
    }

    pthread_exit(NULL);
}

void *rwlock_Delete(void *parm)
{
    threadParm_t *p = (threadParm_t *) parm;
    int r = p->threadId;
    ListNode* ListHead = p->listHead;
    rwlock_t* rwlock_ = p->rwlock_;

    for(int i = 0; i < n_iter; i++){
        //int x = rand();
        printf("Thread: %d, In Iter: %d, Delete Address: %u\n\n",r,i,ListHead->next);
        rw_Delete(ListHead, rwlock_, 0);

    }

    pthread_exit(NULL);
}



int main(){
    ListNode* dummy_head = (ListNode*) malloc(sizeof(ListNode));
    dummy_head->len = 0;
    rwlock_t * rwlock_ = (rwlock_t *) malloc(sizeof(rwlock_t));
    rwlock_init(rwlock_);

    pthread_t	thread[NUM_THREADS];
    threadParm_t	threadParm[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++){
        threadParm[i].threadId = i;
        threadParm[i].listHead = dummy_head;
        threadParm[i].rwlock_ = rwlock_;

        if((i % 2) == 0){
            pthread_create(&thread[i], NULL, rwlock_Find, (void *)&threadParm[i]);
        }


        if((i % 4) == 1){
            pthread_create(&thread[i], NULL, rwlock_Insert, (void *)&threadParm[i]);
        }
        if((i % 4) == 3)    pthread_create(&thread[i], NULL, rwlock_Delete, (void *)&threadParm[i]);
    }

	for (int i=0; i<NUM_THREADS; i++)
	{
		pthread_join(thread[i], NULL);
	}


    //free(dummy_head);
    rwlock_destroy(rwlock_);
    //free(rwlock_);
    return 0;    
}
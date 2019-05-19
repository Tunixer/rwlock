#include <pthread.h>
#include <stdlib.h>

#include "ListNode.h"

int main(){
    ListNode* dummy_head = (ListNode*) malloc(sizeof(ListNode));
    dummy_head->val = 0xffff;
    rwlock_t * rwlock_ = (rwlock_t *) malloc(sizeof(rwlock_t));
    rwlock_init(rwlock_);
    rw_Insert(dummy_head, rwlock_, 2, 0);
    rw_Insert(dummy_head, rwlock_, 3, 0);
    rw_Insert(dummy_head, rwlock_, 4, 0);
    rw_Delete(dummy_head, rwlock_, 0);
    rw_Insert(dummy_head, rwlock_, 4, 0);
    rw_Delete(dummy_head, rwlock_, 0);
    rw_Insert(dummy_head, rwlock_, 2, 0);
    rw_Insert(dummy_head, rwlock_, 3, 0);
    rw_Insert(dummy_head, rwlock_, 4, 0);
    rw_Delete(dummy_head, rwlock_, 0);
    rw_Delete(dummy_head, rwlock_, 0);
    rw_Insert(dummy_head, rwlock_, 4, 0);
    rw_Delete(dummy_head, rwlock_, 0);
    rw_Insert(dummy_head, rwlock_, 2, 0);
    rw_Insert(dummy_head, rwlock_, 3, 0);
    rw_Insert(dummy_head, rwlock_, 4, 0);
    rw_Insert(dummy_head, rwlock_, 4, 0);
    rw_Delete(dummy_head, rwlock_, 0);
    rwlock_destroy(rwlock_);
    free(rwlock_);
    return 0;    
}
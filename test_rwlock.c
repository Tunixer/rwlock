#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "ListNode.h"


void Print(ListNode* head){
    ListNode* p = head->next;
    printf("List: ");
    for(; p != NULL; p = p->next){
        printf("%d ",p->val);
    }
    printf("\n");
}

int main(){
    ListNode* dummy_head = (ListNode*) malloc(sizeof(ListNode));
    int find_val;
    bool isFind;
    dummy_head->val = 0xffff;
    rwlock_t * rwlock_ = (rwlock_t *) malloc(sizeof(rwlock_t));
    rwlock_init(rwlock_);
    //Test the correctness of Insert
    rw_Insert(dummy_head, rwlock_, 2, 0);
    rw_Insert(dummy_head, rwlock_, 3, 0);
    rw_Insert(dummy_head, rwlock_, 4, 0);
    Print(dummy_head);
    //Delete # of elements larger than length of LinkedList
    rw_Delete(dummy_head, rwlock_, 0);
    rw_Delete(dummy_head, rwlock_, 0);
    rw_Delete(dummy_head, rwlock_, 0);
    rw_Delete(dummy_head, rwlock_, 0);
    rw_Delete(dummy_head, rwlock_, 0);
    Print(dummy_head);
    rw_Insert(dummy_head, rwlock_, 4, 0);
    rw_Delete(dummy_head, rwlock_, 0);
    rw_Insert(dummy_head, rwlock_, 2, 0);
    rw_Insert(dummy_head, rwlock_, 3, 0);
    rw_Insert(dummy_head, rwlock_, 4, 0);

    //Test the correctness of Find
    Print(dummy_head);
    isFind = rw_Find(dummy_head, rwlock_, &find_val, 3);
    if(isFind) printf("Find value: %d\n",find_val);
    else printf("Failure to Find\n");

    rw_Delete(dummy_head, rwlock_, 0);
    rw_Delete(dummy_head, rwlock_, 0);
    rw_Insert(dummy_head, rwlock_, 4, 0);
    rw_Delete(dummy_head, rwlock_, 0);

    Print(dummy_head);
    isFind = rw_Find(dummy_head, rwlock_, &find_val, 0);
    if(isFind) printf("Find value: %d\n",find_val);
    else printf("Failure to Find\n");
    
    rw_Insert(dummy_head, rwlock_, 2, 0);
    rw_Insert(dummy_head, rwlock_, 3, 0);
    rw_Insert(dummy_head, rwlock_, 4, 0);
    rw_Insert(dummy_head, rwlock_, 4, 0);
    rw_Delete(dummy_head, rwlock_, 0);
    //Free all the information of LinkedList
    Print(dummy_head);
    while(rw_Delete(dummy_head, rwlock_, 0));
    Print(dummy_head);
    free(dummy_head);
    rwlock_destroy(rwlock_);
    free(rwlock_);
    return 0;    
}
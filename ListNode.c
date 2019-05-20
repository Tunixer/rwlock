#include "ListNode.h"
#include <stdlib.h>
#include <stdio.h>
/*
if pos > len(List) then Insert value to the end of list
Insert value to the pos
*/
bool rw_Insert(ListNode* head, rwlock_t* rwlock, int value, int pos){
    ListNode *p = head,*tmp = (ListNode*) malloc(sizeof(ListNode));
    tmp->val = value;
    printf("rw_Insert try to get lock....\n");
    rwlock_wrlock(rwlock);
    printf("rw_Insert Got lock!!!!!\n");
    for(int i = 1; i <= pos; i++){
        if(p->next != NULL){
            p = p->next;
        }else{
            break;
        }
    }
    ListNode *ptr = p->next;
    p->next = tmp;
    tmp->next = ptr;

    rwlock_unlock(rwlock);
    printf("rw_Insert Release lock!!!!!\n");
    return true;
}
//Find the value of element at pos
bool rw_Find(ListNode* head, rwlock_t* rwlock, int *value, int pos){
    ListNode *p = head;
    printf("rw_Find try to get lock....\n");
    rwlock_rdlock(rwlock);
    printf("rw_Find Got lock!!!!!\n");
    for(int i = 1; i <= pos; i++){
        if(p->next != NULL){
            p = p->next;
        }else{
            break;
        }
    }
    if(p->next == NULL){
        rwlock_unlock(rwlock);
        return false;
    }
    *value = p->next->val;
    rwlock_unlock(rwlock);
    printf("rw_Find Release lock!!!!!\n");
    return true;
}
/*
Delete the element in the pos(thus the element of p->next)
*/
bool rw_Delete(ListNode* head, rwlock_t* rwlock, int pos){
    ListNode *p = head, *tmp;
    printf("rw_Delete try to get lock....\n");
    rwlock_wrlock(rwlock);

    for(int i = 1; i <= pos; i++){
        if(p->next != NULL){
            p = p->next;
        }else{
            break;
        }
    }
    if(p->next == NULL){
        rwlock_unlock(rwlock);
        return false;   
    }
    tmp = p->next->next;
    free(p->next);
    p->next = tmp;
    rwlock_unlock(rwlock);
    return true;
}
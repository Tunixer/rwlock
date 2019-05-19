#include "ListNode.h"
#include <stdlib.h>
/*
if pos > len(List) then Insert value to the end of list
Insert value to the pos
*/
bool rw_Insert(ListNode* head, rwlock_t* rwlock, int value, int pos){
    ListNode *p = head,*tmp = (ListNode*) malloc(sizeof(ListNode));
    tmp->val = value;

    rwlock_wrlock(rwlock);

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
    return true;
}
//Find the value of element at pos
bool rw_Find(ListNode* head, rwlock_t* rwlock, int *value, int pos){
    ListNode *p = head;
    rwlock_rdlock(rwlock);

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
    return true;
}
/*
Delete the element in the pos(thus the element of p->next)
*/
bool rw_Delete(ListNode* head, rwlock_t* rwlock, int pos){
    ListNode *p = head, *tmp;

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
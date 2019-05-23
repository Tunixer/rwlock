#include "ListNode.h"
#include <stdlib.h>
#include <stdio.h>
/*
if pos > len(List) then Insert value to the end of list
Insert value to the pos
*/
bool rw_Insert(ListNode* head, rwlock_t* rwlock, int value, int pos, int threadID){
    rwlock_wrlock(rwlock);
    ListNode *p = head,*tmp = (ListNode*) malloc(sizeof(ListNode));
    tmp->val = value;
    tmp->next = head->next;
    head->next = tmp;
    head->len++;
    rwlock_unlock(rwlock);
    return true;
}
//Find the value of element at pos
bool rw_Find(ListNode* head, rwlock_t* rwlock, int *value, int pos, int threadID){
    rwlock_rdlock(rwlock);
    ListNode *p = head;
    if(head->next == NULL || head == NULL){
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
bool rw_Delete(ListNode* head, rwlock_t* rwlock, int pos, int threadID){
    rwlock_wrlock(rwlock);
    // printf("%d GOT write lock\n", threadID);
    if(head->next == NULL || head == NULL){
        rwlock_unlock(rwlock);
        return true;        
    }
    ListNode* tmp = head->next;
    printf("%d want to free address: %u\n", threadID, tmp);
    head->next = tmp->next;
    head->len--;
    free(tmp);
    // printf("%d want to free address: %u\n", threadID, tmp);
    //free(tmp);
    // printf("%d want to RELEASE write lock\n", threadID);
    rwlock_unlock(rwlock);
    return true;
}
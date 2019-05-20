#include "ListNode.h"
#include <stdlib.h>
#include <stdio.h>
/*
if pos > len(List) then Insert value to the end of list
Insert value to the pos
*/
bool rw_Insert(ListNode* head, rwlock_t* rwlock, int value, int pos){
    rwlock_wrlock(rwlock);
    ListNode *p = head,*tmp = (ListNode*) malloc(sizeof(ListNode));
    tmp->val = value;
    int i = 0;
    while(i < pos){
        if(p->next != NULL){
            p = p->next;
        }else{
            break;
        }
        i++;
    }
    ListNode *ptr = p->next;
    p->next = tmp;
    tmp->next = ptr;
    head->len++;
    printf("Insert value: %d, address: %u\n",tmp->val,(unsigned int)(tmp));
    rwlock_unlock(rwlock);
    return true;
}
//Find the value of element at pos
bool rw_Find(ListNode* head, rwlock_t* rwlock, int *value, int pos){
    rwlock_rdlock(rwlock);
    ListNode *p = head;
    int i = 0;
    while(i < pos){
        if(p->next != NULL){
            p = p->next;
        }else{
            break;
        }
        i++;
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
    rwlock_wrlock(rwlock);
    ListNode *p = head, *tmp;

    if(head->len == 0){
        rwlock_unlock(rwlock);
        return false; 
    }
    int i = 0;
    while(i < pos){
        if(p->next != NULL){
            p = p->next;
        }else{
            break;
        }
        i++;
    }
    if(p->next == NULL){
        rwlock_unlock(rwlock);
        return false;  
    }
    tmp = p->next->next;
    printf("Delete value: %d, address: %u\n",p->next->val,(unsigned int)(p->next));
    free(p->next);
    p->next = tmp;
    head->len--;
    printf("Linked List len: %d\n",head->len);
    rwlock_unlock(rwlock);
    return true;
}
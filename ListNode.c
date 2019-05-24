#include "ListNode.h"
#include <stdlib.h>
#include <stdio.h>
Node* search(PNode pHeader, int k);
int insert(PNode pHeader, PNode pNew, int k);
int deleteNode(PNode pHeader, int k);

bool rw_Insert(PNode head, rwlock_t* rwlock, int value, int pos, int threadID){
    rwlock_wrlock(rwlock);
    PNode tmp = (PNode) malloc(sizeof(Node));
    tmp->data = value;
    int ans = insert(head, tmp, pos);
    rwlock_unlock(rwlock);
    return (bool)ans;
}
bool rw_Find(PNode head, rwlock_t* rwlock, int *value, int pos, int threadID){
    rwlock_rdlock(rwlock);
    Node* ans = search(head, pos);
    rwlock_unlock(rwlock);
    if(ans == NULL) return false;
    return true;  
}
bool rw_Delete(PNode head, rwlock_t* rwlock, int pos, int threadID){
    rwlock_wrlock(rwlock);
    int ans = deleteNode(head, pos);
    rwlock_unlock(rwlock);
    return (bool)ans;
}


Node* search(PNode pHeader, int k)
{
  PNode p = pHeader->next;
  int i = 1;
  //printf("search\n");
  while(p && (i < k))
  {
    p = p->next;
    i++;
  }
  if (p && (i == k)) // 这步的i == k是必须的，
  // 因为如果一开始的时候 i就 >= k并且pHeader->next还不为NULL这一步就会必过，导致返回的是第一个元素的值
  {
    return p;
  }
  return NULL;
}
 
int insert(PNode pHeader, PNode pNew, int k)
{
  PNode p = NULL;
  //printf("insert\n");
  if ( 1 == k )
  {
    p = pHeader;
  }
  else
  {
    //printf("==>");
    p = search(pHeader, k-1);
  }
  if (p)
  {
    // 带头结点和不带头结点的主要区别之一就在这
    // 如果不带头结点，那么在第一个位置插入结点的操作应该是
    // pNew->next = p;
    // p = pNew;
    // 带头结点的操作如下
    pNew->next = p->next;
    p->next = pNew;
    return 1;
  }
  return 0;
}
 
int deleteNode(PNode pHeader, int k)
{
  PNode p = NULL;
  //printf("deleteNode\n");
  if (1 == k)
  {
    p = pHeader->next;
  }
  else
  {
   // printf("==>");
    p = search(pHeader, k-1);
  }
  if (p && p->next)
  {
    // 不带头结点的操作时删除第一个结点的操作
    // Node* temp = p;
    // p = p->next;
    // free(temp);
    // 带头结点的操作如下
    PNode temp = p->next;
    p->next = temp->next;
    free(temp);
    return 1;
  }
  else
  {
    //printf("Not Found\n");
    return 0;
  }
}



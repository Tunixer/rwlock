#include "rwlock.h"
#include <stdbool.h>
typedef struct node
{
  int data;
  struct node* next;// 这个地方注意结构体变量的定义规则
} Node, *PNode;

bool rw_Insert(PNode head, rwlock_t* rwlock, int value, int pos, int threadID);
bool rw_Find(PNode head, rwlock_t* rwlock, int *value, int pos, int threadID);
bool rw_Delete(PNode head, rwlock_t* rwlock, int pos, int threadID);
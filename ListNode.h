#include "rwlock.h"
#include <stdbool.h>
struct ListNode{
    int val;
    int len;
    struct ListNode* next;
};

typedef struct ListNode ListNode;
bool rw_Insert(ListNode* head, rwlock_t* rwlock, int value, int pos);
bool rw_Find(ListNode* head, rwlock_t* rwlock, int *value, int pos);
bool rw_Delete(ListNode* head, rwlock_t* rwlock, int pos);
all : rwlock.o list.o
rwlock.o : rwlock.c rwlock.h
	cc -c rwlock.c -o rwlock.o
list.o : ListNode.c ListNode.h
	cc -c ListNode.c -o list.o
clean :
	rm *.o
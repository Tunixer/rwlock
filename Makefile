all : rwlock.o list.o test_rwlock.o
	cc -o test_rwlock rwlock.o list.o test_rwlock.o -lpthread
rwlock.o : rwlock.c rwlock.h
	cc -c rwlock.c -o rwlock.o
list.o : ListNode.c ListNode.h
	cc -c ListNode.c -o list.o
test_rwlock.o : test_rwlock.c
	cc -c test_rwlock.c -o test_rwlock.o 
clean :
	rm *.o test_rwlock
rwlock : rwlock.o

rwlock.o : rwlock.c rwlock.h
	gcc -c rwlock.c
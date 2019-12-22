CC=gcc
CFILES=../src/lalloc.c ../src/queue.c queue_test.c
CFLAGS=-I../include/
LIBS=-lpthread



all:
	$(CC) $(CFILES) $(CFLAGS) $(LIBS) -o unit_test

test:
	$(CC) $(CFILES) $(CFLAGS) $(LIBS) -o unit_test
	./unit_test
	rm -rf unit_test

clean:
	rm -rf unit_test

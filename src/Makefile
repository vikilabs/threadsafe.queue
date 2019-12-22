CC=gcc
DEPS=lalloc.h queue.h
CFLAGS=-I../include/
ODIR=../lib
LIBS=-lpthread



all:
	$(info [ CREATING DIRECTORY ])
	$(shell mkdir -p $(ODIR))
	$(info [ COMPILING SHARED/DYNAMIC LIBRARY ])
	$(CC) -shared -o $(ODIR)/libqueue.so $(LIBS) $(CFLAGS)  -fPIC   lalloc.c 
	$(CC) -shared -o $(ODIR)/liblalloc.so $(LIBS) $(CFLAGS)  -fPIC   lalloc.c 
	$(info [ CREATING OBJECT FILE ])
	$(CC) -c $(CFLAGS) -o $(ODIR)/queue.o 	queue.c
	$(CC) -c $(CFLAGS) -o $(ODIR)/lalloc.o 	lalloc.c
	$(info [ COMPILING STATIC LIBRARY ])
	ar rcs $(ODIR)/libqueue.a  $(ODIR)/queue.o 
	ar rcs $(ODIR)/liblalloc.a  $(ODIR)/lalloc.o
	$(info [ REMOVING  OBJECT FILE ])
	rm -rf $(ODIR)/queue.o $(ODIR)/lalloc.o

clean:

	$(info [ REMOVING OBJECT FILE ])
	rm -rf $(ODIR)/queue.o
	rm -rf $(ODIR)/lalloc.o
	$(info [ REMOVING SHARED/DYNAMIC LIBRARY ])
	rm -rf $(ODIR)/libqueue.so
	rm -rf $(ODIR)/liblalloc.so
	$(info [ REMOVING STATIC LIBRARY ])
	rm -rf $(ODIR)/libqueue.a
	rm -rf $(ODIR)/liblalloc.a

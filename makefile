CC=gcc
CFLAGS=-Wall -ansi -pedantic -I$(INCDIR)
INCDIR=includes
OBJDIR=bin
SRCDIR=src

a3: a3.o common.o binary.o name.o principals.o title.o
	$(CC) $(CFLAGS) -o $@ $^

a3.o : a3.c
	$(CC) $(CFLAGS) -c -o $@ $<

common.o : common.c common.h
	$(CC) $(CFLAGS) -c -o $@ $<

binary.o : binary.c binary.h common.h
	$(CC) $(CFLAGS) -c -o $@ $<

name.o : name.c name.h binary.h common.h
	$(CC) $(CFLAGS) -c -o $@ $<

principals.o : principals.c principals.h
	$(CC) $(CFLAGS) -c -o $@ $<

title.o : title.c title.h
	$(CC) $(CFLAGS) -c -o $@ $<

run :
	./a3
clean :
	rm a3 *.o

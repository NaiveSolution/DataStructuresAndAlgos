# Makefile for listIteratorInt 

CC = gcc
CFLAGS = -Wall -Werror -g

all : testListIteratorInt

testListIteratorInt : listIteratorInt.o testListIteratorInt.o 
	$(CC) -o testListIteratorInt  listIteratorInt.o testListIteratorInt.o

testListIteratorInt.o: testListIteratorInt.c listIteratorInt.h
	$(CC) $(CFLAGS) -c  testListIteratorInt.c

listIteratorInt.o : listIteratorInt.c  listIteratorInt.h

clean :
	rm -f *.o   testListIteratorInt core


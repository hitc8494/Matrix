# Brett Hitchcock
# Custom Makefile
CC = g++
CFLAGS = -Wall -pthread -std=c++0x

all: test.o matrix.o
	g++ $(CFLAGS) matrix.o test.o -o program

test.o: test.cpp matrix.h 
	g++ $(CFLAGS) -c test.cpp -o test.o

matrix.o: matrix.cpp matrix.h
	g++ $(CFLAGS) -c matrix.cpp -o matrix.o

clean:
	rm -rf *o 
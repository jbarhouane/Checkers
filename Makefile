CC = g++
CFLAGS = -g --std=c++17 -Wall -Werror -pedantic
LIB = -lsfml-graphics -lsfml-window -lsfml-system

all: Checkers lint

lint:
	cpplint --recursive --quiet src/

Checkers: Checkers.o main.o
	$(CC) $(CFLAGS) -o Checkers Checkers.o main.o $(LIB)

Checkers.o: Checkers.cpp Checkers.hpp
	$(CC) $(CFLAGS) -c Checkers.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm Checkers *.o


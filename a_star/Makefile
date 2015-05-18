CC = g++
CFLAGS = -Wall -c -std=gnu++11
LFLAGS = -Wall

all: main.o a_star.o grid.o distance_estimators.o
	$(CC) $(LFLAGS) main.o a_star.o grid.o distance_estimators.o -o main


main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
	

grid.o: grid.cpp
	$(CC) $(CFLAGS) grid.cpp

distance_estimators.o: distance_estimators.cpp
	$(CC) $(CFLAGS) distance_estimators.cpp
	

a_star.o: a_star.cpp
	$(CC) $(CFLAGS) a_star.cpp
	

main.cpp: a_star.h grid.h distance_estimators.h
	

a_star.cpp: a_star.h
	

grid.cpp: grid.h
	

distance_estimators.cpp: distance_estimators.h
	

grid.h:
	

a_star.h:
	

distance_estimators.h:
	

clean:
	rm -rf *.o

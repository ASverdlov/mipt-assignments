CC = g++
CFLAGS = -Wall -c -std=c++0x
LFLAGS = -Wall
SOURCEDIR = src
BINDIR = bin
LIBDIR = $(BINDIR)/lib

all: $(LIBDIR)/main.o $(LIBDIR)/solver.o $(LIBDIR)/grid.o $(LIBDIR)/distance_estimators.o
	$(CC) $(LFLAGS) $(LIBDIR)/main.o $(LIBDIR)/solver.o $(LIBDIR)/grid.o $(LIBDIR)/distance_estimators.o -o $(BINDIR)/main

$(LIBDIR)/main.o: $(SOURCEDIR)/main.cpp
	$(CC) $(CFLAGS) $(SOURCEDIR)/main.cpp -o $(LIBDIR)/main.o
	
$(LIBDIR)/grid.o: $(SOURCEDIR)/grid.cpp
	$(CC) $(CFLAGS) $(SOURCEDIR)/grid.cpp -o $(LIBDIR)/grid.o

$(LIBDIR)/distance_estimators.o: $(SOURCEDIR)/distance_estimators.cpp
	$(CC) $(CFLAGS) $(SOURCEDIR)/distance_estimators.cpp -o $(LIBDIR)/distance_estimators.o
	
$(LIBDIR)/solver.o: $(SOURCEDIR)/solver.cpp
	$(CC) $(CFLAGS) $(SOURCEDIR)/solver.cpp -o $(LIBDIR)/solver.o
	
$(SOURCEDIR)/main.cpp: $(SOURCEDIR)/solver.h $(SOURCEDIR)/grid.h $(SOURCEDIR)/distance_estimators.h
	
$(SOURCEDIR)/solver.cpp: $(SOURCEDIR)/solver.h
	
$(SOURCEDIR)/grid.cpp: $(SOURCEDIR)/grid.h
	
$(SOURCEDIR)/distance_estimators.cpp: $(SOURCEDIR)/distance_estimators.h
	
$(SOURCEDIR)/grid.h:
	
$(SOURCEDIR)/solver.h:
	
$(SOURCEDIR)/distance_estimators.h:
	
clean:
	rm -rf $(LIBDIR)/*.o

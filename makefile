# Sriram Sai Ganesh
# saiganesh.3
UTILDIR = ./util/
SRCDIR = ./src/
OBJDIR = ./obj/
CLASSDIR=./class/
CC=g++
CFLAGS= -pedantic -W -Wall -Wextra -std=c++14
OBJECTS = $(OBJDIR)main.o
all: main


main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ 

$(OBJDIR)main.o: $(SRCDIR)main.cpp $(UTILDIR)*.hpp $(CLASSDIR)*.hpp
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJDIR)%.o: $(SRCDIR)%.cpp $(UTILDIR)*.hpp $(CLASSDIR)*.hpp
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

run:
	make all
	./main

clean:
	rm -f $(OBJDIR)*.o $(SRCDIR)*.exe *.exe $(UTILDIR)*.gch $(CLASSDIR)*.gch *~ core

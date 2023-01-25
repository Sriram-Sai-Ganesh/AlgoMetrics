# Sriram Sai Ganesh
# saiganesh.3

INCLDIR = ./inc
SRCDIR = ./src
OBJDIR = ./obj
CC=g++
CFLAGS= -pedantic -W -Wall -Wextra
# CFLAGS= -I inc

all: main

main: $(OBJDIR)/main.o
	$(CC) $(CFLAGS) -o $@ $^ 

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(INCLDIR)/*.hpp
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLDIR)/*.hpp
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

run:
	make all
	./main

clean:
	rm -f $(OBJDIR)/*.o $(SRCDIR)/*.exe *.exe $(INCLDIR)/*.gch *~ core

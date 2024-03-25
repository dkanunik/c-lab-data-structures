# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Output directory for the executable
BINDIR = $(PWD)/bin

# Headers dir
INC_DIR = $(PWD)/include

# Build directory for object files
BUILDDIR = $(PWD)/build

# Source files directory
SRCDIR = $(PWD)/src

# Tests source files directory
TESTS_SRC_DIR = $(PWD)/tests

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS =  $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

# Test source files
UNITYDIR = /usr/local/src/unity
TEST_SOURCES = $(wildcard $(TESTS_SRC_DIR)/*.c)
UNITY_SOURCE = $(UNITYDIR)/unity.c
TEST_OBJECTS =  $(patsubst $(TESTS_SRC_DIR)/%.c, $(BUILDDIR)/%.o, $(TEST_SOURCES))

# Output executables
EXEC = $(BINDIR)/stack
TEST_EXEC = $(BINDIR)/test_suite

# Default target
all: preparedirs compile compiletests linktests

preparedirs:	
	mkdir -p $(BUILDDIR)		
	mkdir -p $(BINDIR)	

compile: 
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SOURCES) -o $(OBJECTS)

link: 
#	gcc -o my_program obj1.o obj2.o obj3.o
	$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJECTS) -o $(EXEC)

compiletests:
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(UNITYDIR) -c $(TEST_SOURCES) -o $(TEST_OBJECTS)	

linktests: 
#	gcc -o my_program obj1.o obj2.o obj3.o
	$(CC) $(CFLAGS) -I$(INC_DIR) $(UNITY_SOURCE) $(OBJECTS) $(TEST_OBJECTS) -o $(TEST_EXEC)

test: compile compiletests linktests
	$(TEST_EXEC)

# Clean target
clean:
	rm -f $(BUILDDIR)/* $(BINDIR)/*

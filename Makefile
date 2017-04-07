# Makefile

# compiler
CC=gcc

# compiler flags
C_FLAGS=-Wall

# compilable objecs
OBJS=main.c

# includes
#INCLUDE=-I./*.h

# libraries
LIBS=-lncurses

# output name
OUT=./test

all($OBJS):
	$(CC) $(C_FLAGS) $(LIBS) -o $(OUT) $(OBJS)


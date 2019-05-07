

CC = gcc
CFLAGS = -std=c11 -Wall -g -pedantic

all: BIN SRC OBJ INCLUDE TEST

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

INCLUDE:
	if [ ! -d "include" ]; then mkdir include; fi;

SRC: 
	if [ ! -d "src" ]; then mkdir src; fi;

OBJ:
	if [ ! -d "obj" ]; then mkdir obj; fi;

TEST:
	if [ ! -d "test" ]; then mkdir test; fi;

LIB:
	if [ ! -d "lib" ]; then mkdir lib; fi;

ladder: makeladder runladder

makeladder: all
	$(CC) $(CFLAGS) -Iinclude src/LadderLottery.c src/utilities.c src/Numbers.c test/testLadder.c -o ./bin/ladder

runladder:
	./bin/ladder
clean: 
	if [ -d "bin" ]; then rm -rf ./bin/; fi;
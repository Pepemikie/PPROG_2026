# @brief Compile and merge the files needed for the game.
# @file makefile
# @author Jose Miguel Romero Oubina
# @date 23-02-2026
# @version 1

CC=gcc
CFLAGS=-Wall -g -pedantic -ansi
LIBS= -lscreen -L. 
SOURCE =command.c game.c game_actions.c game_loop.c space.c graphic_engine.c game_reader.c object.c player.c character.c set.c
OBJ=	command.o game.o game_actions.o game_loop.o space.o graphic_engine.o game_reader.o object.o player.o character.o set.o
EXE= castle_game

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(EXE)

run:
	./$(EXE) castle.dat
# @brief Compile and merge the files needed for the game.
# @file makefile
# @author Jose Miguel Romero Oubina
# @date 23-02-2026
# @version 1

CC=gcc
CFLAGS=-Wall -g -pedantic
CFLAGS_DEBUG=-Wall -g -pedantic -DDEBUG
LIBS= -lscreen -L. 
SOURCE =command.c game.c game_actions.c game_loop.c space.c graphic_engine.c game_reader.c object.c player.c character.c set.c inventory.c link.c
OBJ=	command.o game.o game_actions.o game_loop.o space.o graphic_engine.o game_reader.o object.o player.o character.o set.o inventory.o link.o
OBJ_DEBUG = command_d.o game_d.o game_actions_d.o game_loop_d.o space_d.o graphic_engine_d.o game_reader_d.o object_d.o player_d.o character_d.o set_d.o inventory_d.o link_d.o

EXE= castle_game
EXE_DEBUG= castle_game_debug
EXE_SET_TEST= set_test
EXE_CHARACTER_TEST= character_test
EXE_SPACE_TEST= space_test

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

debug: $(OBJ_DEBUG)
	$(CC) $(OBJ_DEBUG) -o $(EXE_DEBUG) $(LIBS)

test: $(EXE_SET_TEST) $(EXE_CHARACTER_TEST) $(EXE_SPACE_TEST)

$(EXE_SET_TEST): set_test.o set.o
	$(CC) set_test.o set.o -o $(EXE_SET_TEST) $(LIBS)

$(EXE_CHARACTER_TEST): character_test.o character.o
	$(CC) character_test.o character.o -o $(EXE_CHARACTER_TEST) $(LIBS)

$(EXE_SPACE_TEST): space_test.o space.o set.o
	$(CC) space_test.o space.o set.o -o $(EXE_SPACE_TEST) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%_d.o: %.c
	$(CC) $(CFLAGS_DEBUG) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OBJ_DEBUG) set_test.o character_test.o space_test.o $(EXE) $(EXE_DEBUG) $(EXE_SET_TEST) $(EXE_CHARACTER_TEST) $(EXE_SPACE_TEST)

run:
	./$(EXE) castle.dat

runv:
	valgrind --leak-check=full -s --track-origins=yes ./$(EXE) castle.dat

rundebug:
	./$(EXE_DEBUG) castle.dat

runtest:
	./$(EXE_SET_TEST); ./$(EXE_CHARACTER_TEST); ./$(EXE_SPACE_TEST)
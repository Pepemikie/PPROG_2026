# @brief Compile and merge the files needed for the game.
# @file makefile
# @author Jose Miguel Romero Oubina
# @date 23-02-2026
# @version 4.2

#FLAGS
CC=gcc
CFLAGS=-Wall -g -ansi -pedantic -I./include
CFLAGS_DEBUG=-Wall -g -ansi -pedantic -DDEBUG -I./include
LIBS= -L./lib -lscreen
#FILES AND OBJECTS
OBJ=		obj/command.o obj/game.o obj/game_actions.o obj/game_loop.o obj/space.o obj/graphic_engine.o obj/game_reader.o obj/object.o obj/player.o obj/character.o obj/set.o obj/inventory.o obj/link.o
OBJ_DEBUG = obj/command_d.o obj/game_d.o obj/game_actions_d.o obj/game_loop_d.o obj/space_d.o obj/graphic_engine_d.o obj/game_reader_d.o obj/object_d.o obj/player_d.o obj/character_d.o obj/set_d.o obj/inventory_d.o obj/link_d.o
#EXECUTABLES
EXE= castle_game
EXE_DEBUG= castle_game_debug
EXE_SET_TEST= set_test
EXE_CHARACTER_TEST= character_test
EXE_SPACE_TEST= space_test
EXE_PLAYER_TEST= player_test
EXE_OBJECT_TEST= object_test
EXE_LINK_TEST= link_test
EXE_INVENTORY_TEST= inventory_test

#COMPILE
#Normal compilation and linking
all: $(EXE)
$(EXE): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)

obj/game_loop.o: src/game_loop.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/game_loop.c -o $@

obj/game.o: src/game.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/game.c -o $@

obj/game_actions.o: src/game_actions.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/game_actions.c -o $@

obj/game_reader.o: src/game_reader.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/game_reader.c -o $@

obj/command.o: src/command.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/command.c -o $@

obj/graphic_engine.o: src/graphic_engine.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/graphic_engine.c -o $@

obj/space.o: src/space.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/space.c -o $@

obj/object.o: src/object.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/object.c -o $@

obj/player.o: src/player.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/player.c -o $@

obj/character.o: src/character.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/character.c -o $@

obj/set.o: src/set.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/set.c -o $@

obj/inventory.o: src/inventory.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/inventory.c -o $@

obj/link.o: src/link.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/link.c -o $@


#Debug compilation and linking
debug: $(EXE_DEBUG)
$(EXE_DEBUG): $(OBJ_DEBUG)
	$(CC) -o $(EXE_DEBUG) $(OBJ_DEBUG) $(LIBS)

obj/game_loop_d.o: src/game_loop.c
	mkdir -p obj
	$(CC) $(CFLAGS_DEBUG) -c src/game_loop.c -o $@

obj/game_d.o: src/game.c
	mkdir -p obj
	$(CC) $(CFLAGS_DEBUG) -c src/game.c -o $@

obj/game_actions_d.o: src/game_actions.c
	mkdir -p obj
	$(CC) $(CFLAGS_DEBUG) -c src/game_actions.c -o $@

obj/game_reader_d.o: src/game_reader.c
	mkdir -p obj
	$(CC) $(CFLAGS_DEBUG) -c src/game_reader.c -o $@

obj/command_d.o: src/command.c
	mkdir -p obj
	$(CC) $(CFLAGS_DEBUG) -c src/command.c -o $@

obj/graphic_engine_d.o: src/graphic_engine.c
	mkdir -p obj
	$(CC) $(CFLAGS_DEBUG) -c src/graphic_engine.c -o $@

obj/space_d.o: src/space.c
	mkdir -p obj
	$(CC) $(CFLAGS_DEBUG) -c src/space.c -o $@

obj/object_d.o: src/object.c
	mkdir -p obj
	$(CC) $(CFLAGS_DEBUG) -c src/object.c -o $@

obj/player_d.o: src/player.c
	mkdir -p obj
	$(CC) $(CFLAGS_DEBUG) -c src/player.c -o $@

obj/character_d.o: src/character.c
	mkdir -p obj
	$(CC) $(CFLAGS_DEBUG) -c src/character.c -o $@

obj/set_d.o: src/set.c
	mkdir -p obj
	$(CC) $(CFLAGS_DEBUG) -c src/set.c -o $@

obj/inventory_d.o: src/inventory.c
	mkdir -p obj
	$(CC) $(CFLAGS_DEBUG) -c src/inventory.c -o $@

obj/link_d.o: src/link.c
	mkdir -p obj
	$(CC) $(CFLAGS_DEBUG) -c src/link.c -o $@


#Test compilation and linking
test: $(EXE_SET_TEST) $(EXE_CHARACTER_TEST) $(EXE_SPACE_TEST) $(EXE_PLAYER_TEST) $(EXE_OBJECT_TEST) $(EXE_LINK_TEST) $(EXE_INVENTORY_TEST)

$(EXE_SET_TEST): obj/set_test.o obj/set.o
	$(CC) obj/set_test.o obj/set.o -o $(EXE_SET_TEST) $(LIBS)

$(EXE_CHARACTER_TEST): obj/character_test.o obj/character.o
	$(CC) obj/character_test.o obj/character.o -o $(EXE_CHARACTER_TEST) $(LIBS)

$(EXE_SPACE_TEST): obj/space_test.o obj/space.o obj/set.o
	$(CC) obj/space_test.o obj/space.o obj/set.o -o $(EXE_SPACE_TEST) $(LIBS)

$(EXE_PLAYER_TEST): obj/player_test.o obj/player.o obj/inventory.o obj/set.o
	$(CC) obj/player_test.o obj/player.o obj/inventory.o obj/set.o -o $(EXE_PLAYER_TEST) $(LIBS)

$(EXE_OBJECT_TEST): obj/object_test.o obj/object.o
	$(CC) obj/object_test.o obj/object.o -o $(EXE_OBJECT_TEST) $(LIBS)

$(EXE_LINK_TEST): obj/link_test.o obj/link.o
	$(CC) obj/link_test.o obj/link.o -o $(EXE_LINK_TEST) $(LIBS)

$(EXE_INVENTORY_TEST): obj/inventory_test.o obj/inventory.o obj/set.o
	$(CC) obj/inventory_test.o obj/inventory.o obj/set.o -o $(EXE_INVENTORY_TEST) $(LIBS)

obj/set_test.o: src/set_test.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/set_test.c -o $@

obj/character_test.o: src/character_test.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/character_test.c -o $@

obj/space_test.o: src/space_test.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/space_test.c -o $@

obj/player_test.o: src/player_test.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/player_test.c -o $@

obj/object_test.o: src/object_test.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/object_test.c -o $@

obj/link_test.o: src/link_test.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/link_test.c -o $@

obj/inventory_test.o: src/inventory_test.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/inventory_test.c -o $@


#RUNNING
#Nomal execution
run:
	./$(EXE) castle.dat

#Execution with valgrind
runv:
	valgrind --leak-check=full -s --track-origins=yes ./$(EXE) castle.dat

#Debug execution
rundebug:
	./$(EXE_DEBUG) castle.dat

#Test execution
runtest:
	./$(EXE_SET_TEST); ./$(EXE_CHARACTER_TEST); ./$(EXE_SPACE_TEST); ./$(EXE_PLAYER_TEST); ./$(EXE_OBJECT_TEST); ./$(EXE_LINK_TEST); ./$(EXE_INVENTORY_TEST)

#Run game with specific commands
runcmd1:
	./$(EXE) castle.dat -l output.log < game1.cmd

runcmd2:
	./$(EXE) castle.dat -l output.log < game2.cmd

runcmd3:
	./$(EXE) castle.dat -l output.log < game3.cmd

runcmd4:
	./$(EXE) castle.dat -l output.log < game4.cmd

#CLEANING
#files cleaning
clean:
	rm -rf obj/ $(EXE) $(EXE_DEBUG) $(EXE_SET_TEST) $(EXE_CHARACTER_TEST) $(EXE_SPACE_TEST) $(EXE_PLAYER_TEST) $(EXE_OBJECT_TEST) $(EXE_LINK_TEST) $(EXE_INVENTORY_TEST)

#Documentation from Doxygen cleaning
cleandoc:
	rm -rf doc

#All cleaning
cleanall: clean cleandoc

#DOCUMENTATION
doxygen:
	mkdir -p doc
	doxygen Doxyfile
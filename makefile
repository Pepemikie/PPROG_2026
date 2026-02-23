CC=gcc
CFLAGS=-Wall -pedantic -ansi
LIBS= -lscreen -L.
SOURCE=command.c game.c game_actions.c game_loop.c space.c graphic_engine.c game_reader.c object.c player.c
OBJ=command.o game.o game_actions.o game_loop.o space.o graphic_engine.o game_reader.o object.o player.o
EXE=Iteracion_1


all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(EXE)

run:
	./$(EXE) castle.dat

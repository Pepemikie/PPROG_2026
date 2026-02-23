# @brief Compila y une los archivos necesarios para el juego
# @file makefile
# @author JORGE GARCIA GARRIDO
# @date 10-02-2025
# @version 1


CC = gcc #define el compilador
CFLAGS = -Wall -g -pedantic -ansi #Flags del compilador: -Wall muestra los warnings, .g información para depuración
LIBS = -L. -lscreen #busca librerias en el directorio actual, enlaza con libscreen
SOURCE = command.c game.c game_actions.c game_loop.c space.c graphic_engine.c game_reader.c object.c player.c
OBJ = command.o game.o game_actions.o game_loop.o space.o graphic_engine.o game_reader.o object.o player.o #archivos objeto
EXE = PPROG

all: $(EXE)

#Regla para generar el ejecutable del juego
$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

#Reglas para generar los archivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Regla para limpiar los archivos objeto y ejecutables
clean:
	rm -rf $(OBJ) $(EXE)

run:
	./$(EXE) castle.dat

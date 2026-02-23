# @brief Compila y une los archivos necesarios para el juego
# @file makefile
# @author JORGE GARCIA GARRIDO
# @date 10-02-2025
# @version 1


CC = gcc #define el compilador
CFLAGS = -Wall -g #Flags del compilador: -Wall muestra los warnings, .g información para depuración
LDFLAGS = -L. -lscreen #busca librerias en el directorio actual, enlaza con libscreen
OBJFILES = game_loop.o game.o space.o command.o graphic_engine.o game_actions.o game_reader.o object.o player.o set.o#archivos objeto

#Regla para generar el ejecutable del juego
castle: $(OBJFILES)
	$(CC) $(CFLAGS) -o castle $(OBJFILES) $(LDFLAGS)

#Reglas para generar los archivos objeto
space.o: space.c space.h 
	$(CC) $(CFLAGS) -c space.c

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c

command.o: command.c command.h 
	$(CC) $(CFLAGS) -c command.c

graphic_engine.o: graphic_engine.c graphic_engine.h command.h libscreen.h space.h types.h
	$(CC) $(CFLAGS) -c graphic_engine.c

game_actions.o: game_actions.c game_actions.h 
	$(CC) $(CFLAGS) -c game_actions.c

game_reader.o: game_reader.c game_reader.h
	$(CC) $(CFLAGS) -c game_reader.c

object.o: object.c object.h
	$(CC) $(CFLAGS) -c object.c

player.o: player.c player.h
	$(CC) $(CFLAGS) -c player.c

game_loop.o: game_loop.c game.h command.h game_actions.h graphic_engine.h
	$(CC) $(CFLAGS) -c game_loop.c

set.o: set.c set.h 
	$(CC) $(CFLAGS) -c set.c

#Regla para limpiar los archivos objeto y ejecutables
clean:
	rm -f *.o castle

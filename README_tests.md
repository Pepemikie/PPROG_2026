# Pruebas de Integración para el Proyecto Castle

Este directorio contiene archivos de prueba para realizar pruebas de integración del juego Castle.

## Archivos de Datos

- `castle.dat`: Archivo de datos correcto con espacios, objetos, personajes y enlaces.
- `castle_empty.dat`: Archivo de datos vacío para probar casos extremos.
- `castle_error.dat`: Archivo de datos con líneas erróneas para probar robustez.

## Archivos de Comandos

- `game1.cmd`: Secuencia básica de comandos (move, take, drop, inspect, exit).
- `game2.cmd`: Comandos adicionales incluyendo attack y chat.
- `game3.cmd`: Comandos inválidos para probar manejo de errores.
- `game4.cmd`: Solo exit, usado para pruebas con datos vacíos o erróneos.

## Cómo Ejecutar las Pruebas

Compila el proyecto primero:
```
make all
```

Ejecuta una prueba redirigiendo la entrada estándar:
```
./castle_game castle.dat -l output.log < game1.cmd
```

Los logs generados en `output.log` pueden ser comparados para verificar el comportamiento.

## Casos de Prueba

1. **Datos correctos con comandos válidos**: `castle.dat` con `game1.cmd` y `game2.cmd`.
2. **Datos vacíos**: `castle_empty.dat` con `game4.cmd`.
3. **Datos con errores**: `castle_error.dat` con `game4.cmd`.
4. **Comandos inválidos**: `castle.dat` con `game3.cmd`.
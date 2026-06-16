# Proyecto: Compilador/Traductor (PL)

Este proyecto es una implementación de un compilador/traductor, desarrollado con herramientas estándar de análisis léxico y sintáctico como Flex y Bison.

## Repositorio
- URL: [https://github.com/nickhernd/pl](https://github.com/nickhernd/pl)

## Requisitos
Para compilar y ejecutar este proyecto, necesitas tener instaladas las siguientes herramientas:
- `make`
- `g++` (o un compilador de C++ compatible)
- `gcc`
- `flex`
- `bison`

## Instrucciones de Compilación
El proyecto utiliza un Makefile para gestionar la compilación. Simplemente ejecuta el siguiente comando en la raíz del proyecto:

```bash
make
```

Esto generará los ejecutables necesarios:
- `compiler`
- `m2r`

Para limpiar los archivos generados y los objetos, puedes ejecutar:

```bash
make clean
```

## Estructura del Proyecto
- `src/`: Contiene el código fuente del compilador (`lexer.l`, `parser.y`, implementaciones en C++).
- `include/`: Contiene los archivos de cabecera (`.h`).
- `obj/`: Directorio donde se almacenan los archivos objeto durante la compilación.
- `tests/`: Contiene los casos de prueba (entradas y resultados esperados).
- `docs/`: Documentación adicional sobre el diseño y requisitos del proyecto.

## Uso
Una vez compilado, puedes usar los ejecutables para procesar tus archivos fuente (ej. los archivos en `tests/inputs/`).

```bash
./compiler < tests/inputs/p01.txt
```

---
*Nota: Si encuentras problemas, revisa los issues en el repositorio de GitHub.*

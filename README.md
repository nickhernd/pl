# Proyecto: Compilador/Traductor (PL)

Este proyecto es una implementación de un compilador/traductor, desarrollado con herramientas estándar de análisis léxico y sintáctico como Flex y Bison.

## Nuevas Funcionalidades
- **Manejo de Constantes**: Soporte para la palabra clave `final` y verificación de no reasignación.
- **Funciones y Retornos**: Soporte para múltiples métodos estáticos y verificación semántica de sentencias `return`.
- **Detección de Código Inalcanzable**: Identificación de sentencias que nunca se ejecutarán.

## Repositorio
- URL: [https://github.com/nickhernd/pl](https://github.com/nickhernd/pl)

## Requisitos
Para compilar y ejecutar este proyecto, necesitas tener instaladas las siguientes herramientas:
- `make`, `g++`, `gcc`, `flex`, `bison`

## Flujo de Construcción y Operación

### 1. Construcción (Build)
El proyecto utiliza un Makefile para gestionar la compilación. Ejecuta en la raíz:

```bash
make
```

**Proceso de construcción:**
1.  **Generación:** `flex` (`src/lexer.l`) y `bison` (`src/parser.y`) generan los archivos fuentes C (`lex.yy.c`, `parser.tab.c`, `parser.tab.h`).
2.  **Compilación:** Se compilan los archivos fuente C/C++ (`src/`, `include/`) generando archivos objeto en `obj/`.
3.  **Enlazado:** Se crean dos ejecutables:
    - `compiler`: El compilador principal.
    - `m2r`: El intérprete/VM para el lenguaje.

### 2. Flujo de Operación
Para procesar un programa fuente:
1.  **Compilación:** El `compiler` toma el archivo fuente y genera un archivo intermedio (ej. `output.asm`).
    ```bash
    ./compiler tests/inputs/p01.txt
    ```
2.  **Ejecución:** El intérprete `m2r` ejecuta el código generado:
    ```bash
    ./m2r output.asm
    ```

### 3. Pruebas de Errores Semánticos
Se han incluido 10 tests específicos para verificar los errores semánticos implementados. Puedes ejecutarlos con:

```bash
for f in tests/semantic_errors/*.java; do echo "Testing $f..."; ./compiler "$f"; echo "-----------------------------------"; done
```

## Estructura del Proyecto
- `src/`: Código fuente (`lexer.l`, `parser.y`, implementaciones C/C++).
- `include/`: Archivos de cabecera (`.h`).
- `obj/`: Archivos objeto.
- `tests/`: Casos de prueba.
    - `tests/semantic_errors/`: Casos de prueba para errores semánticos.
- `docs/`: Documentación técnica.

## Limpieza
Para limpiar archivos generados:
```bash
make clean
```

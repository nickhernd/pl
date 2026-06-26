#!/bin/bash
# [BND-14] Verificación de Binarios x86-64
# Compila cada .java -> .s -> binario, ejecuta y compara con .expected

COMPILER="$(dirname "$0")/../compiler"
TMPASM="/tmp/pl_test.s"
TMPBIN="/tmp/pl_test_bin"
PASS=0
FAIL=0
ERROR=0

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

for java_file in "$(dirname "$0")"/backend/*.java; do
    base="${java_file%.java}"
    expected_file="${base}.expected"

    if [ ! -f "$expected_file" ]; then
        echo -e "${RED}SKIP${NC}: $java_file (no .expected)"
        continue
    fi

    # Compilar a ensamblador
    if ! "$COMPILER" "$java_file" > "$TMPASM" 2>/dev/null; then
        echo -e "${RED}ERROR${NC}: $java_file (fallo en compilacion)"
        ERROR=$((ERROR + 1))
        continue
    fi

    # Ensamblar y linkear
    if ! gcc "$TMPASM" -o "$TMPBIN" -no-pie 2>/dev/null; then
        echo -e "${RED}ERROR${NC}: $java_file (fallo en ensamblado/linkeo)"
        ERROR=$((ERROR + 1))
        continue
    fi

    # Ejecutar y capturar salida
    actual=$("$TMPBIN" 2>/dev/null)
    expected=$(cat "$expected_file")

    if [ "$actual" = "$expected" ]; then
        echo -e "${GREEN}PASS${NC}: $(basename "$java_file")"
        PASS=$((PASS + 1))
    else
        echo -e "${RED}FAIL${NC}: $(basename "$java_file")"
        echo "  Esperado: $(echo "$expected" | head -3)"
        echo "  Obtenido: $(echo "$actual"   | head -3)"
        FAIL=$((FAIL + 1))
    fi
done

echo ""
echo "Resultados: ${PASS} PASS, ${FAIL} FAIL, ${ERROR} ERROR"
[ $((FAIL + ERROR)) -eq 0 ] && exit 0 || exit 1

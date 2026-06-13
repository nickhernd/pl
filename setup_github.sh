#!/bin/bash

# Script para configurar el entorno de desarrollo profesional del Compilador
# Requisitos: Tener instalado y autenticado el comando 'gh' (GitHub CLI)

echo "🚀 Iniciando configuración de Issues, Milestones y Tags..."

# 1. Crear Etiquetas (Labels)
echo "🏷️  Creando etiquetas..."
gh label create "teoria" --description "Conceptos teóricos de compiladores" --color "0075ca" --force
gh label create "practica" --description "Tareas de implementación de código" --color "008672" --force
gh label create "verificación" --description "Lógica de Hoare y pruebas formales" --color "d73a4a" --force
gh label create "backend" --description "Generación de código x86-64" --color "cfd3d7" --force
gh label create "arquitectura" --description "Diseño estructural del compilador" --color "a2eeef" --force

# 2. Crear Milestones
echo "📅 Creando hitos (Milestones)..."
gh api repos/:owner/:repo/milestones -f title="Hito 1: Frontend & AST" -f description="Refactorización para generar un Árbol de Sintaxis Abstracta (AST) robusto."
gh api repos/:owner/:repo/milestones -f title="Hito 2: Análisis Semántico & Lógica" -f description="Comprobación de tipos avanzada y pre-condiciones de Hoare."
gh api repos/:owner/:repo/milestones -f title="Hito 3: IR & Optimización" -f description="Representación Intermedia (3AC) y optimizaciones básicas."
gh api repos/:owner/:repo/milestones -f title="Hito 4: Backend x86-64" -f description="Generación de ensamblador real compatible con GCC."
gh api repos/:owner/:repo/milestones -f title="Hito 5: Verificación Formal" -f description="Pruebas de corrección usando lógica de Hoare."

# Función para crear issues con cuerpo detallado
create_issue() {
    title=$1
    body=$2
    milestone=$3
    labels=$4
    gh issue create --title "$title" --body "$body" --milestone "$milestone" --label "$labels"
}

# 3. Crear Issues Detallados
echo "📝 Creando issues con documentación..."

# --- HITO 1 ---
create_issue "Refactorización: Del Parser al AST" \
"### Teoría
Un compilador profesional no genera código directamente desde el parser. Necesitamos un **AST (Abstract Syntax Tree)**.
El AST elimina detalles sintácticos (como paréntesis o puntos y coma) y se queda con la esencia lógica.

### Práctica
1. Crear clases C++ para cada nodo (Node, ExpNode, StmtNode, etc.).
2. Modificar el archivo \`parser.y\` para que las acciones semánticas construyan el árbol en lugar de imprimir ensamblador.
3. Implementar el patrón **Visitor** para recorrer el árbol." \
"Hito 1: Frontend & AST" "arquitectura,practica"

# --- HITO 2 ---
create_issue "Análisis Semántico y Lógica de Hoare (Introducción)" \
"### Teoría
La **Lógica de Hoare** usa tripletas {P} C {Q}.
P: Precondición, C: Comando, Q: Postcondición.
Debemos permitir que el usuario anote el código con estas condiciones.

### Práctica
1. Añadir sintaxis para anotaciones (ej: \`@assert a > 0\`).
2. Ampliar la Tabla de Símbolos para manejar no solo tipos, sino propiedades lógicas.
3. Implementar chequeo de tipos estricto." \
"Hito 2: Análisis Semántico & Lógica" "teoria,verificación"

# --- HITO 3 ---
create_issue "Representación Intermedia (IR) y 3AC" \
"### Teoría
El código de **Tres Direcciones (3AC)** es una etapa intermedia antes del ensamblador real. Facilita las optimizaciones.
Ejemplo: \`t1 = a + b\`.

### Práctica
1. Diseñar un conjunto de instrucciones IR.
2. Implementar un generador de IR que recorra el AST.
3. Crear un visualizador de IR para depuración." \
"Hito 3: IR & Optimización" "practica,teoria"

# --- HITO 4 ---
create_issue "Generación de Código x86-64 (Backend)" \
"### Teoría
Pasamos de una VM idealizada (\`m2r\`) a hardware real.
Debemos gestionar:
- **Stack Frames**: \`rbp\`, \`rsp\`.
- **Calling Convention**: System V AMD64 (rdi, rsi, rdx...).
- **Registros**: Uso eficiente de rax, rbx, etc.

### Práctica
1. Traducir instrucciones IR a x86-64.
2. Manejar la reserva de memoria en la pila para variables locales.
3. Generar un archivo \`.s\` que pueda ensamblarse con \`gcc\` o \`nasm\`." \
"Hito 4: Backend x86-64" "backend,practica"

# --- HITO 5 ---
create_issue "Verificación Formal de Programas" \
"### Teoría
El objetivo final es demostrar que el programa hace lo que dice.
Usaremos el cálculo de **Weakest Precondition (WP)**.

### Práctica
1. Generar condiciones de verificación (VCs) a partir de las tripletas de Hoare.
2. (Opcional) Exportar estas VCs a un probador de teoremas (como Z3 o SMT-Lib).
3. Validar que el código generado mantiene las invariantes del bucle." \
"Hito 5: Verificación Formal" "teoria,verificación"

echo "✅ Configuración finalizada. ¡Revisa tu pestaña de Issues en GitHub!"

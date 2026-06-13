#!/bin/bash

# Script de Granularidad Extrema para Compiladores (60+ Issues)
# Organizado en hitos mensuales para un desarrollo de un año.

echo "🏗️  Configurando hoja de ruta de 60 pasos..."

# 1. Etiquetas y Milestones base
gh label create "teoria" --color "0075ca" --force
gh label create "practica" --color "008672" --force
gh label create "bug" --color "d73a4a" --force

# Milestones (Fases del año)
gh api repos/:owner/:repo/milestones -f title="Fase 1: Infraestructura y AST (Mes 1-2)"
gh api repos/:owner/:repo/milestones -f title="Fase 2: Análisis Semántico (Mes 3-4)"
gh api repos/:owner/:repo/milestones -f title="Fase 3: Representación Intermedia - IR (Mes 5-6)"
gh api repos/:owner/:repo/milestones -f title="Fase 4: Backend x86-64 (Mes 7-9)"
gh api repos/:owner/:repo/milestones -f title="Fase 5: Lógica de Hoare y Verificación (Mes 10-12)"

create_issue() {
    gh issue create --title "$1" --body "$2" --milestone "$3" --label "$4"
}

# --- FASE 1: INFRAESTRUCTURA Y AST (12 pasos) ---
MS1="Fase 1: Infraestructura y AST (Mes 1-2)"

create_issue "[AST-1] Definición de la clase base Node" "Teoría: Polimorfismo en C++. Práctica: Crear Node.h con método virtual accept(Visitor)." "$MS1" "practica,arquitectura"
create_issue "[AST-2] Nodo para Expresiones Binarias" "Teoría: Árboles de expresión. Práctica: Clase BinOpNode (left, op, right)." "$MS1" "practica"
create_issue "[AST-3] Nodo para Literales (Int, Float)" "Teoría: Nodos hoja. Práctica: IntNode y FloatNode." "$MS1" "practica"
create_issue "[AST-4] Nodo para Identificadores" "Teoría: Referencias a símbolos. Práctica: IdNode almacenando el nombre." "$MS1" "practica"
create_issue "[AST-5] Estructura de Sentencias (StmtNode)" "Teoría: Sentencias vs Expresiones. Práctica: Clase base abstracta StmtNode." "$MS1" "practica"
create_issue "[AST-6] Nodo de Asignación" "Teoría: L-Values y R-Values. Práctica: AssignNode(id, expr)." "$MS1" "practica"
create_issue "[AST-7] Nodo de Bloque (Listas de Stmts)" "Teoría: Scopes y secuencias. Práctica: BlockNode con std::vector<StmtNode*>." "$MS1" "practica"
create_issue "[AST-8] Integración Parser: Construcción de AST" "Teoría: Acciones semánticas de Bison. Práctica: Modificar parser.y para retornar Nodos." "$MS1" "practica"
create_issue "[AST-9] Implementación del AST Visualizer" "Teoría: Recorrido de árboles (DFS). Práctica: Clase PrintVisitor que genere formato DOT/Graphviz." "$MS1" "practica"
create_issue "[AST-10] Gestión de Memoria (Smart Pointers)" "Teoría: Ownership. Práctica: Refactorizar AST para usar std::unique_ptr." "$MS1" "arquitectura"
create_issue "[AST-11] Soporte para If/Else en AST" "Teoría: Flujo de control. Práctica: IfNode(cond, thenPart, elsePart)." "$MS1" "practica"
create_issue "[AST-12] Soporte para Bucles While en AST" "Teoría: Iteración. Práctica: WhileNode(cond, body)." "$MS1" "practica"

# --- FASE 2: ANÁLISIS SEMÁNTICO (12 pasos) ---
MS2="Fase 2: Análisis Semántico (Mes 3-4)"

create_issue "[SEM-1] Rediseño de Tabla de Símbolos" "Teoría: Ámbitos anidados. Práctica: Implementar SymbolTable con puntero al padre (Scope)." "$MS2" "practica"
create_issue "[SEM-2] Registro de Declaraciones" "Teoría: L-Attribute Grammars. Práctica: Llenar la tabla al encontrar declaraciones." "$MS2" "practica"
create_issue "[SEM-3] Verificación de Identificadores no declarados" "Teoría: Errores de visibilidad. Práctica: Reportar error si se usa un ID no existente." "$MS2" "practica"
create_issue "[SEM-4] Sistema de Tipos: Clase Type" "Teoría: Type checking. Práctica: Crear clase Type y subclases (IntType, RealType)." "$MS2" "practica"
create_issue "[SEM-5] Inferencia de Tipos en Expresiones" "Teoría: Bottom-up type synthesis. Práctica: Visitor que asigne tipos a cada nodo de expresión." "$MS2" "practica"
create_issue "[SEM-6] Chequeo de Compatibilidad de Tipos" "Teoría: Coerción y Casting. Práctica: Validar asignaciones (int a float, etc)." "$MS2" "practica"
create_issue "[SEM-7] Análisis de L-Values" "Teoría: Mutabilidad. Práctica: Asegurar que el lado izquierdo de una asignación es escribible." "$MS2" "practica"
create_issue "[SEM-8] Control de tipos en If/While" "Teoría: Predicados booleanos. Práctica: Asegurar que las condiciones son booleanas." "$MS2" "practica"
create_issue "[SEM-9] Manejo de Constantes y Literales" "Teoría: Constant folding básico. Práctica: Resolver 2+3 en tiempo de compilación." "$MS2" "practica"
create_issue "[SEM-10] Verificación de Funciones y Retornos" "Teoría: Firma de funciones. Práctica: Validar parámetros y tipos de retorno." "$MS2" "practica"
create_issue "[SEM-11] Detección de código inalcanzable" "Teoría: Control Flow Graph (CFG) básico. Práctica: Warn si hay código tras un return." "$MS2" "practica"
create_issue "[SEM-12] Pruebas Unitarias Semánticas" "Teoría: Test-driven development. Práctica: Crear 10 tests de error semántico." "$MS2" "practica"

# --- FASE 3: REPRESENTACIÓN INTERMEDIA - IR (10 pasos) ---
MS3="Fase 3: Representación Intermedia - IR (Mes 5-6)"

create_issue "[IR-1] Diseño de Cuádruplas (3AC)" "Teoría: Instrucciones de 3 direcciones. Práctica: Definir struct Instruction (op, arg1, arg2, result)." "$MS3" "teoria,practica"
create_issue "[IR-2] Generación de Temporales" "Teoría: Registros virtuales ilimitados. Práctica: Clase TempManager." "$MS3" "practica"
create_issue "[IR-3] Generación de Etiquetas (Labels)" "Teoría: Destinos de salto. Práctica: LabelManager." "$MS3" "practica"
create_issue "[IR-4] Traducción de Expresiones Aritméticas" "Teoría: Linearización. Práctica: Convertir BinOpNode en secuencias de 3AC." "$MS3" "practica"
create_issue "[IR-5] Traducción de Saltos Condicionales" "Teoría: Cortocircuito. Práctica: Generar CMP y JMP para IF/WHILE." "$MS3" "practica"
create_issue "[IR-6] IR para Llamadas a Funciones" "Teoría: Calling sequence. Práctica: Instrucciones PARAM y CALL en IR." "$MS3" "practica"
create_issue "[IR-7] Linearizador de Bloques" "Teoría: Basic Blocks. Práctica: Dividir IR en bloques básicos." "$MS3" "practica"
create_issue "[IR-8] Optimizaciones Locales: Eliminación de código muerto" "Teoría: Dataflow simple. Práctica: Quitar instrucciones que no se usan." "$MS3" "practica"
create_issue "[IR-9] Visualizador de IR" "Teoría: Legibilidad. Práctica: Función que imprima el 3AC de forma legible." "$MS3" "practica"
create_issue "[IR-10] Test Suite de IR" "Teoría: Regresión. Práctica: Comparar IR generado contra archivos .ir esperados." "$MS3" "practica"

# --- FASE 4: BACKEND x86-64 (14 pasos) ---
MS4="Fase 4: Backend x86-64 (Mes 7-9)"

create_issue "[BND-1] Setup: Ensamblador y Linker" "Teoría: x86-64 ISA. Práctica: Crear script para compilar .s con gcc." "$MS4" "backend"
create_issue "[BND-2] Layout de Memoria: El Stack Frame" "Teoría: rbp/rsp. Práctica: Generar prólogo y epílogo de funciones." "$MS4" "backend"
create_issue "[BND-3] Gestión de Registros (Básico)" "Teoría: Registro A (rax). Práctica: Usar rax para resultados inmediatos." "$MS4" "backend"
create_issue "[BND-4] Traducción de Cuádruplas a x86" "Teoría: Mapeo de instrucciones. Práctica: Convertir ADD 3AC a ADDQ x86." "$MS4" "backend"
create_issue "[BND-5] Acceso a Variables Locales" "Teoría: Offset respecto a rbp. Práctica: Mapear IDs a [rbp - offset]." "$MS4" "backend"
create_issue "[BND-6] Manejo de Constantes en x86" "Teoría: Immediates. Práctica: MOVQ $val, %reg." "$MS4" "backend"
create_issue "[BND-7] Implementación de Saltos en Hardware" "Teoría: Flags de condición. Práctica: CMPQ + JE/JNE/JL." "$MS4" "backend"
create_issue "[BND-8] Calling Convention: Pasar parámetros" "Teoría: ABI de Linux (rdi, rsi...). Práctica: Mover Params a registros correctos." "$MS4" "backend"
create_issue "[BND-9] Gestión del Valor de Retorno" "Teoría: RAX. Práctica: Asegurar que el resultado final está en rax." "$MS4" "backend"
create_issue "[BND-10] Soporte para Números Reales (XMM)" "Teoría: Registros SSE. Práctica: Usar xmm0-xmm7 para floats." "$MS4" "backend"
create_issue "[BND-11] Entrada/Salida: printf nativo" "Teoría: Librería estándar C. Práctica: Llamar a printf desde ensamblador." "$MS4" "backend"
create_issue "[BND-12] Entrada/Salida: scanf nativo" "Teoría: Direcciones de memoria. Práctica: Pasar direcciones a scanf." "$MS4" "backend"
create_issue "[BND-13] Optimización de Registros: Grafos" "Teoría: Chaitin-Briggs. Práctica: Implementar coloreado de grafos (Avanzado)." "$MS4" "backend"
create_issue "[BND-14] Verificación de Binarios" "Teoría: Ejecución real. Práctica: Ejecutar y validar salida standard." "$MS4" "backend"

# --- FASE 5: LÓGICA DE HOARE Y VERIFICACIÓN (12 pasos) ---
MS5="Fase 5: LÓGICA DE HOARE Y VERIFICACIÓN (Mes 10-12)"

create_issue "[VER-1] Sintaxis para Pre/Post condiciones" "Teoría: Contratos de software. Práctica: Añadir @pre y @post al parser." "$MS5" "verificación"
create_issue "[VER-2] Representación de Predicados Lógicos" "Teoría: Fórmulas de primer orden. Práctica: AST para lógica (AND, OR, NOT, IMPLIES)." "$MS5" "verificación"
create_issue "[VER-3] Tripletas de Hoare en el AST" "Teoría: Estructura de verificación. Práctica: Vincular sentencias con sus pre/post." "$MS5" "verificación"
create_issue "[VER-4] Regla de la Asignación" "Teoría: Sustitución. Práctica: Implementar WP(x:=e, Q) = Q[e/x]." "$MS5" "verificación"
create_issue "[VER-5] Regla de la Composición" "Teoría: Encadenamiento. Práctica: Propagar condiciones entre sentencias." "$MS5" "verificación"
create_issue "[VER-6] Invariantes de Bucle" "Teoría: Inducción. Práctica: Añadir sintaxis @invariant a los bucles while." "$MS5" "verificación"
create_issue "[VER-7] Generación de Verification Conditions (VCs)" "Teoría: Weakest Precondition. Práctica: Generar fórmulas lógicas globales." "$MS5" "verificación"
create_issue "[VER-8] Interfaz con Solvers SMT (Z3)" "Teoría: Satisfacibilidad. Práctica: Exportar VCs a formato SMT-Lib." "$MS5" "verificación"
create_issue "[VER-9] Verificación de Seguridad en Memoria" "Teoría: Out-of-bounds. Práctica: Generar VCs para accesos a arrays." "$MS5" "verificación"
create_issue "[VER-10] Reporte de Errores de Verificación" "Teoría: Contraejemplos. Práctica: Mostrar por qué una precondición falla." "$MS5" "verificación"
create_issue "[VER-11] Verificación de Terminación" "Teoría: Variantes de bucle. Práctica: Asegurar que el bucle progresa." "$MS5" "verificación"
create_issue "[VER-12] Demo Final: Algoritmo Verificado" "Teoría: Full functional correctness. Práctica: Compilar y verificar un Quicksort." "$MS5" "verificación"

echo "✅ 60 Issues creados. Tu roadmap está listo para un año de desarrollo."

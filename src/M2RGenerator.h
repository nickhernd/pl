#ifndef _M2R_GENERATOR_H
#define _M2R_GENERATOR_H

// Generador de código m2r a partir de la IR (cuádruplas 3AC)
//
// El intérprete m2r tiene:
//   - Registro A (Acumulador): todas las operaciones aritméticas lo usan
//   - Registro B (Base): para indexación
//   - Memoria plana: posiciones 0..16383
//   - Constantes fuente: #n (entero), $r (real)
//
// Patrón general para  result = arg1 op arg2:
//   mov <arg1> A          ; cargar arg1 en A
//   <op>i/<op>r <arg2>    ; A = A op arg2
//   mov A <result>        ; guardar en destino

#include "IR.h"
#include <iostream>
#include <sstream>
#include <string>

class M2RGenerator {
    std::ostream& out;

    // ------------------------------------------------------------------ //
    //  Formateo de argumentos para m2r
    // ------------------------------------------------------------------ //

    // Argumento fuente (puede ser dirección, inmediato, A)
    std::string src(const IRArg& a) const {
        switch (a.kind) {
            case ARG_VAR:
            case ARG_TEMP:       return std::to_string(a.addr);
            case ARG_CONST_INT:  return "#" + std::to_string(a.ival);
            case ARG_CONST_REAL: {
                std::ostringstream os;
                os << "$" << a.rval;
                return os.str();
            }
            case ARG_LABEL:      return a.name;
            default:             return "A";
        }
    }

    // Argumento destino (sólo dirección o A)
    std::string dst(const IRArg& a) const {
        switch (a.kind) {
            case ARG_VAR:
            case ARG_TEMP: return std::to_string(a.addr);
            default:       return "A";
        }
    }

    // Suffix de instrucción según tipo: 'i' para entero/lógico, 'r' para real
    char suffix(int type) const {
        return (type == 1) ? 'r' : 'i';
    }

    void emit(const std::string& instr) {
        out << instr << "\n";
    }

    // ------------------------------------------------------------------ //
    //  Carga arg en el acumulador A
    // ------------------------------------------------------------------ //
    void loadA(const IRArg& a) {
        if (a.kind == ARG_NONE) return;
        emit("mov " + src(a) + " A");
    }

    // ------------------------------------------------------------------ //
    //  Generación por cuádrupla
    // ------------------------------------------------------------------ //

    void genBinary(const IRQuad& q, const std::string& mnem) {
        loadA(q.arg1);
        emit(mnem + suffix(q.type) + " " + src(q.arg2));
        emit("mov A " + dst(q.result));
    }

    void genCmp(const IRQuad& q, const std::string& mnem) {
        // Las comparaciones siempre producen entero (0/1)
        int opType = (q.arg1.type == 1 || q.arg2.type == 1) ? 1 : 0;
        loadA(q.arg1);
        emit(mnem + suffix(opType) + " " + src(q.arg2));
        emit("mov A " + dst(q.result));
    }

public:
    explicit M2RGenerator(std::ostream& o = std::cout) : out(o) {}

    void generate(const IRProgram& prog) {
        for (const auto& q : prog.quads) {
            switch (q.op) {

                // ---- Etiquetas y funciones --------------------------------
                case IR_LABEL:
                    emit(q.arg1.name);
                    break;

                case IR_FUNC_BEGIN:
                    // En m2r no hay prólogo; la etiqueta es el punto de entrada
                    emit("; --- " + q.arg1.name + " ---");
                    break;

                case IR_FUNC_END:
                    emit("; --- fin " + q.arg1.name + " ---");
                    break;

                // ---- Control de flujo ------------------------------------
                case IR_JMP:
                    emit("jmp " + q.arg1.name);
                    break;

                case IR_JZ:
                    loadA(q.arg1);
                    emit("jz " + q.arg2.name);
                    break;

                case IR_JNZ:
                    loadA(q.arg1);
                    emit("jnz " + q.arg2.name);
                    break;

                // ---- Copia -----------------------------------------------
                case IR_COPY:
                    // mov src dst (m2r soporta memoria-a-memoria directamente)
                    if (q.result.kind == ARG_VAR || q.result.kind == ARG_TEMP) {
                        emit("mov " + src(q.arg1) + " " + dst(q.result));
                    }
                    break;

                // ---- Aritmética ------------------------------------------
                case IR_ADD: genBinary(q, "add"); break;
                case IR_SUB: genBinary(q, "sub"); break;
                case IR_MUL: genBinary(q, "mul"); break;
                case IR_DIV: genBinary(q, "div"); break;
                case IR_MOD:
                    // modi sólo existe para enteros
                    loadA(q.arg1);
                    emit("modi " + src(q.arg2));
                    emit("mov A " + dst(q.result));
                    break;

                // ---- Lógicas --------------------------------------------
                case IR_AND: genBinary(q, "and"); break;
                case IR_OR:  genBinary(q, "or");  break;

                case IR_NOT:
                    loadA(q.arg1);
                    emit(std::string("not") + suffix(q.arg1.type));
                    emit("mov A " + dst(q.result));
                    break;

                case IR_NEG:
                    // negación = 0 - arg1
                    if (q.type == 1) {
                        emit("mov $0 A");
                        emit("subr " + src(q.arg1));
                    } else {
                        emit("mov #0 A");
                        emit("subi " + src(q.arg1));
                    }
                    emit("mov A " + dst(q.result));
                    break;

                // ---- Comparaciones --------------------------------------
                case IR_EQ:  genCmp(q, "eql"); break;
                case IR_NEQ: genCmp(q, "neq"); break;
                case IR_GT:  genCmp(q, "gtr"); break;
                case IR_GTE: genCmp(q, "geq"); break;
                case IR_LT:  genCmp(q, "lss"); break;
                case IR_LTE: genCmp(q, "leq"); break;

                // ---- Conversión de tipos --------------------------------
                case IR_ITOR:
                    loadA(q.arg1);
                    emit("itor");
                    emit("mov A " + dst(q.result));
                    break;

                case IR_RTOI:
                    loadA(q.arg1);
                    emit("rtoi");
                    emit("mov A " + dst(q.result));
                    break;

                // ---- E/S ------------------------------------------------
                case IR_PRINT_INT:
                    emit("wri " + src(q.arg1));
                    break;

                case IR_PRINT_REAL:
                    emit("wrr " + src(q.arg1));
                    break;

                case IR_PRINT_NL:
                    emit("wrl");
                    break;

                // ---- Return / Halt --------------------------------------
                case IR_RETURN:
                    if (!q.arg1.isNone())
                        loadA(q.arg1);
                    emit("halt");
                    break;

                case IR_HALT:
                    emit("halt");
                    break;
            }
        }
    }
};

#endif

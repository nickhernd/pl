#ifndef _IR_VISUALIZER_H
#define _IR_VISUALIZER_H

// [IR-9] Visualizador de IR
// Imprime las cuádruplas en formato legible: "result = arg1 op arg2"

#include "IR.h"
#include <iostream>
#include <iomanip>
#include <string>

class IRVisualizer {
    static std::string opSym(IROpcode op) {
        switch (op) {
            case IR_ADD:  return "+";
            case IR_SUB:  return "-";
            case IR_MUL:  return "*";
            case IR_DIV:  return "/";
            case IR_MOD:  return "%";
            case IR_AND:  return "&&";
            case IR_OR:   return "||";
            case IR_EQ:   return "==";
            case IR_NEQ:  return "!=";
            case IR_LT:   return "<";
            case IR_LTE:  return "<=";
            case IR_GT:   return ">";
            case IR_GTE:  return ">=";
            default:      return "?";
        }
    }

    static std::string typeName(int t) {
        if (t == 0) return "int";
        if (t == 1) return "real";
        if (t == 2) return "bool";
        return "";
    }

public:
    static void print(const IRProgram& prog, std::ostream& out = std::cerr) {
        out << "=========================================\n";
        out << "  IR  -  Cuadruplas 3AC\n";
        out << "=========================================\n";

        int idx = 0;
        for (const auto& q : prog.quads) {
            out << std::setw(4) << idx++ << ":  ";

            switch (q.op) {
                case IR_LABEL:
                    out << q.arg1.name << ":";
                    break;

                case IR_FUNC_BEGIN:
                    out << "\n---- funcion " << q.arg1.name << " ----";
                    break;

                case IR_FUNC_END:
                    out << "---- fin " << q.arg1.name << " ----\n";
                    break;

                case IR_JMP:
                    out << "goto " << q.arg1.name;
                    break;

                case IR_JZ:
                    out << "if " << q.arg1.str() << " == 0  goto " << q.arg2.name;
                    break;

                case IR_JNZ:
                    out << "if " << q.arg1.str() << " != 0  goto " << q.arg2.name;
                    break;

                case IR_COPY:
                    out << q.result.str() << " = " << q.arg1.str();
                    break;

                case IR_NEG:
                    out << q.result.str() << " = -" << q.arg1.str();
                    break;

                case IR_NOT:
                    out << q.result.str() << " = !" << q.arg1.str();
                    break;

                case IR_RETURN:
                    out << "return";
                    if (!q.arg1.isNone()) out << " " << q.arg1.str();
                    break;

                case IR_PRINT_INT:
                    out << "print_int  " << q.arg1.str();
                    break;

                case IR_PRINT_REAL:
                    out << "print_real " << q.arg1.str();
                    break;

                case IR_PRINT_NL:
                    out << "print_nl";
                    break;

                case IR_HALT:
                    out << "halt";
                    break;

                case IR_CALL:
                    out << (q.result.isNone() ? "_" : q.result.str())
                        << " = call " << q.arg1.name << "()";
                    break;

                case IR_READ_INT:
                    out << q.result.str() << " = read_int()";
                    break;

                case IR_READ_REAL:
                    out << q.result.str() << " = read_real()";
                    break;

                case IR_ITOR:
                    out << q.result.str() << " = (real) " << q.arg1.str();
                    break;

                case IR_RTOI:
                    out << q.result.str() << " = (int) " << q.arg1.str();
                    break;

                default:
                    // Operaciones binarias aritméticas / comparación
                    out << q.result.str() << " = "
                        << q.arg1.str() << " " << opSym(q.op) << " " << q.arg2.str();
                    if (q.type >= 0)
                        out << "  [" << typeName(q.type) << "]";
                    break;
            }
            out << "\n";
        }
        out << "=========================================\n";
    }
};

#endif

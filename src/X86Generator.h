#ifndef _X86_GENERATOR_H
#define _X86_GENERATOR_H

// Generador de código x86-64 (AT&T syntax) a partir de la IR (cuádruplas 3AC)
//
// Convenciones:
//   - Enteros/booleanos: registro %rax (acumulador), %rbx (scratch)
//   - Reales (double):   registros %xmm0 (primario), %xmm1 (secundario)
//   - Variables y temporales: slots en la pila, dirección -(slot+1)*8(%rbp)
//   - Constantes reales: pool en .data (.FC0, .FC1, ...)

#include "IR.h"
#include "TablaSimbolos.h"
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iomanip>

class X86Generator {
    std::ostream& out;

    // ------------------------------------------------------------------ //
    //  Tabla de slots de pila: addr IR -> índice de slot (compacto)
    // ------------------------------------------------------------------ //
    std::unordered_map<int, int> addrToSlot;
    int slotCount = 0;

    int getSlot(int addr) {
        auto it = addrToSlot.find(addr);
        if (it != addrToSlot.end()) return it->second;
        int slot = slotCount++;
        addrToSlot[addr] = slot;
        return slot;
    }

    std::string mem(int addr) {
        return "-" + std::to_string((getSlot(addr) + 1) * 8) + "(%rbp)";
    }

    // ------------------------------------------------------------------ //
    //  Pool de constantes reales en .data
    // ------------------------------------------------------------------ //
    std::vector<double> floatConsts;
    std::unordered_map<std::string, int> floatConstKey;

    int addFloatConst(float v) {
        std::ostringstream os;
        os << std::fixed << std::setprecision(17) << (double)v;
        std::string key = os.str();
        auto it = floatConstKey.find(key);
        if (it != floatConstKey.end()) return it->second;
        int idx = (int)floatConsts.size();
        floatConsts.push_back((double)v);
        floatConstKey[key] = idx;
        return idx;
    }

    std::string floatLabel(float v) {
        return ".FC" + std::to_string(addFloatConst(v));
    }

    // ------------------------------------------------------------------ //
    //  Emisión de instrucciones
    // ------------------------------------------------------------------ //
    void emit(const std::string& s) { out << "    " << s << "\n"; }
    void label(const std::string& l) { out << l << ":\n"; }

    // ------------------------------------------------------------------ //
    //  Carga/almacenamiento de enteros (%rax)
    // ------------------------------------------------------------------ //
    void loadInt(const IRArg& a) {
        switch (a.kind) {
            case ARG_VAR: case ARG_TEMP:
                emit("movq " + mem(a.addr) + ", %rax");
                break;
            case ARG_CONST_INT:
                emit("movq $" + std::to_string(a.ival) + ", %rax");
                break;
            default: break;
        }
    }

    void storeInt(const IRArg& a) {
        if (a.kind == ARG_VAR || a.kind == ARG_TEMP)
            emit("movq %rax, " + mem(a.addr));
    }

    // ------------------------------------------------------------------ //
    //  Carga/almacenamiento de reales (%xmm0 o %xmm1)
    // ------------------------------------------------------------------ //
    void loadReal(const IRArg& a, int xmm = 0) {
        std::string r = "%xmm" + std::to_string(xmm);
        switch (a.kind) {
            case ARG_VAR: case ARG_TEMP:
                emit("movsd " + mem(a.addr) + ", " + r);
                break;
            case ARG_CONST_REAL:
                emit("movsd " + floatLabel(a.rval) + "(%rip), " + r);
                break;
            default: break;
        }
    }

    void storeReal(const IRArg& a) {
        if (a.kind == ARG_VAR || a.kind == ARG_TEMP)
            emit("movsd %xmm0, " + mem(a.addr));
    }

    // ------------------------------------------------------------------ //
    //  Primer paso: recoge todas las direcciones y constantes reales
    // ------------------------------------------------------------------ //
    void collectAddresses(const IRProgram& prog) {
        for (const auto& q : prog.quads) {
            auto collect = [&](const IRArg& a) {
                if (a.kind == ARG_VAR || a.kind == ARG_TEMP) getSlot(a.addr);
                if (a.kind == ARG_CONST_REAL)                addFloatConst(a.rval);
            };
            collect(q.arg1); collect(q.arg2); collect(q.result);
        }
    }

    // ------------------------------------------------------------------ //
    //  Aritmética entera binaria: arg1 op arg2 -> result
    // ------------------------------------------------------------------ //
    void genIntBinary(const IRQuad& q) {
        loadInt(q.arg1);
        emit("pushq %rax");
        loadInt(q.arg2);
        emit("movq %rax, %rbx");
        emit("popq %rax");
        switch (q.op) {
            case IR_ADD: emit("addq %rbx, %rax"); break;
            case IR_SUB: emit("subq %rbx, %rax"); break;
            case IR_MUL: emit("imulq %rbx, %rax"); break;
            case IR_DIV: emit("cqto"); emit("idivq %rbx"); break;
            case IR_MOD: emit("cqto"); emit("idivq %rbx"); emit("movq %rdx, %rax"); break;
            default: break;
        }
        storeInt(q.result);
    }

    // ------------------------------------------------------------------ //
    //  Aritmética real binaria: xmm0 op xmm1 -> result
    // ------------------------------------------------------------------ //
    void genRealBinary(const IRQuad& q) {
        loadReal(q.arg1, 0);
        loadReal(q.arg2, 1);
        switch (q.op) {
            case IR_ADD: emit("addsd %xmm1, %xmm0"); break;
            case IR_SUB: emit("subsd %xmm1, %xmm0"); break;
            case IR_MUL: emit("mulsd %xmm1, %xmm0"); break;
            case IR_DIV: emit("divsd %xmm1, %xmm0"); break;
            default: break;
        }
        storeReal(q.result);
    }

    // ------------------------------------------------------------------ //
    //  Comparación entera
    // ------------------------------------------------------------------ //
    void genIntCmp(const IRQuad& q) {
        loadInt(q.arg1);
        emit("pushq %rax");
        loadInt(q.arg2);
        emit("movq %rax, %rbx");
        emit("popq %rax");
        emit("cmpq %rbx, %rax");
        switch (q.op) {
            case IR_EQ:  emit("sete %al");  break;
            case IR_NEQ: emit("setne %al"); break;
            case IR_LT:  emit("setl %al");  break;
            case IR_LTE: emit("setle %al"); break;
            case IR_GT:  emit("setg %al");  break;
            case IR_GTE: emit("setge %al"); break;
            default: break;
        }
        emit("movzbq %al, %rax");
        storeInt(q.result);
    }

    // ------------------------------------------------------------------ //
    //  Comparación real (ucomisd: CF para <, ZF para ==)
    // ------------------------------------------------------------------ //
    void genRealCmp(const IRQuad& q) {
        loadReal(q.arg1, 0);
        loadReal(q.arg2, 1);
        emit("ucomisd %xmm1, %xmm0");
        switch (q.op) {
            case IR_EQ:  emit("sete %al");  break;
            case IR_NEQ: emit("setne %al"); break;
            case IR_LT:  emit("setb %al");  break;
            case IR_LTE: emit("setbe %al"); break;
            case IR_GT:  emit("seta %al");  break;
            case IR_GTE: emit("setae %al"); break;
            default: break;
        }
        emit("movzbq %al, %rax");
        storeInt(q.result);
    }

public:
    explicit X86Generator(std::ostream& o = std::cout) : out(o) {}

    void generate(const IRProgram& prog) {
        collectAddresses(prog);

        // Tamaño del marco de pila, alineado a 16 bytes
        int frameSize = ((slotCount * 8 + 15) / 16) * 16;
        if (frameSize < 16) frameSize = 16;

        // Sección de datos
        out << ".section .data\n";
        out << "fmt_int:       .string \"%ld\"\n";
        out << "fmt_real:      .string \"%g\"\n";
        out << "fmt_scanf_int: .string \"%ld\"\n";
        out << "fmt_scanf_real: .string \"%lf\"\n";
        for (int i = 0; i < (int)floatConsts.size(); ++i)
            out << ".FC" << i << ": .double "
                << std::fixed << std::setprecision(17) << floatConsts[i] << "\n";
        out << "\n.section .text\n.globl main\n\n";

        for (const auto& q : prog.quads) {
            switch (q.op) {

                // ---- Funciones -------------------------------------------
                case IR_FUNC_BEGIN:
                    label(q.arg1.name);
                    emit("pushq %rbp");
                    emit("movq %rsp, %rbp");
                    emit("subq $" + std::to_string(frameSize) + ", %rsp");
                    break;

                case IR_FUNC_END:
                    break;

                // ---- Etiquetas y saltos ----------------------------------
                case IR_LABEL:
                    label(q.arg1.name);
                    break;

                case IR_JMP:
                    emit("jmp " + q.arg1.name);
                    break;

                case IR_JZ:
                    loadInt(q.arg1);
                    emit("testq %rax, %rax");
                    emit("je " + q.arg2.name);
                    break;

                case IR_JNZ:
                    loadInt(q.arg1);
                    emit("testq %rax, %rax");
                    emit("jne " + q.arg2.name);
                    break;

                // ---- Copia -----------------------------------------------
                case IR_COPY:
                    if (q.arg1.type == REAL) { loadReal(q.arg1); storeReal(q.result); }
                    else                     { loadInt(q.arg1);  storeInt(q.result);  }
                    break;

                // ---- Aritmética ------------------------------------------
                case IR_ADD: case IR_SUB: case IR_MUL: case IR_DIV: case IR_MOD:
                    if (q.type == REAL) genRealBinary(q); else genIntBinary(q);
                    break;

                // ---- Lógicas ---------------------------------------------
                case IR_AND:
                    loadInt(q.arg1); emit("pushq %rax");
                    loadInt(q.arg2); emit("popq %rbx");
                    emit("andq %rbx, %rax");
                    storeInt(q.result);
                    break;

                case IR_OR:
                    loadInt(q.arg1); emit("pushq %rax");
                    loadInt(q.arg2); emit("popq %rbx");
                    emit("orq %rbx, %rax");
                    storeInt(q.result);
                    break;

                case IR_NOT:
                    loadInt(q.arg1);
                    emit("testq %rax, %rax");
                    emit("sete %al");
                    emit("movzbq %al, %rax");
                    storeInt(q.result);
                    break;

                case IR_NEG:
                    if (q.type == REAL) {
                        // 0.0 - val usando registros XMM
                        loadReal(q.arg1, 0);
                        emit("pxor %xmm1, %xmm1");
                        emit("subsd %xmm0, %xmm1");
                        emit("movapd %xmm1, %xmm0");
                        storeReal(q.result);
                    } else {
                        loadInt(q.arg1);
                        emit("negq %rax");
                        storeInt(q.result);
                    }
                    break;

                // ---- Comparaciones --------------------------------------
                case IR_EQ: case IR_NEQ: case IR_LT: case IR_LTE:
                case IR_GT: case IR_GTE: {
                    bool isReal = (q.arg1.type == REAL || q.arg2.type == REAL);
                    if (isReal) genRealCmp(q); else genIntCmp(q);
                    break;
                }

                // ---- Conversión de tipos --------------------------------
                case IR_ITOR:
                    loadInt(q.arg1);
                    emit("cvtsi2sdq %rax, %xmm0");
                    storeReal(q.result);
                    break;

                case IR_RTOI:
                    loadReal(q.arg1);
                    emit("cvttsd2siq %xmm0, %rax");
                    storeInt(q.result);
                    break;

                // ---- E/S ------------------------------------------------
                case IR_PRINT_INT:
                    loadInt(q.arg1);
                    emit("movq %rax, %rsi");
                    emit("leaq fmt_int(%rip), %rdi");
                    emit("xorl %eax, %eax");
                    emit("call printf@PLT");
                    break;

                case IR_PRINT_REAL:
                    loadReal(q.arg1, 0);
                    emit("leaq fmt_real(%rip), %rdi");
                    emit("movl $1, %eax");
                    emit("call printf@PLT");
                    break;

                case IR_PRINT_NL:
                    emit("movl $10, %edi");
                    emit("call putchar@PLT");
                    break;

                // ---- Return / Halt --------------------------------------
                case IR_RETURN:
                    if (!q.arg1.isNone()) {
                        if (q.arg1.type == REAL) loadReal(q.arg1);
                        else                     loadInt(q.arg1);
                    }
                    emit("movq %rbp, %rsp");
                    emit("popq %rbp");
                    emit("ret");
                    break;

                case IR_HALT:
                    emit("movq %rbp, %rsp");
                    emit("popq %rbp");
                    emit("ret");
                    break;

                // ---- Llamada a función (BND-8) --------------------------
                // Calling convention x86-64 Linux (System V AMD64 ABI):
                //   enteros:  %rdi, %rsi, %rdx, %rcx, %r8, %r9
                //   floats:   %xmm0-%xmm7
                //   retorno:  entero en %rax, float en %xmm0
                // Nuestros métodos no tienen parámetros, solo emitimos call.
                case IR_CALL:
                    emit("call " + q.arg1.name);
                    if (!q.result.isNone()) {
                        if (q.type == REAL) storeReal(q.result);
                        else                storeInt(q.result);
                    }
                    break;

                // ---- Lectura de stdin (BND-12) --------------------------
                // Pasamos la dirección del slot de pila a scanf como segundo
                // argumento (%rsi), siguiendo el ABI: %rdi=formato, %rsi=puntero.
                case IR_READ_INT:
                    emit("leaq " + mem(q.result.addr) + ", %rsi");
                    emit("leaq fmt_scanf_int(%rip), %rdi");
                    emit("xorl %eax, %eax");
                    emit("call scanf@PLT");
                    break;

                case IR_READ_REAL:
                    emit("leaq " + mem(q.result.addr) + ", %rsi");
                    emit("leaq fmt_scanf_real(%rip), %rdi");
                    emit("xorl %eax, %eax");
                    emit("call scanf@PLT");
                    break;
            }
        }
    }
};

#endif

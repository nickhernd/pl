#ifndef _IR_H
#define _IR_H

// [IR-1] Diseño de Cuádruplas (3-Address Code / 3AC)
// Cuádrupla: (op, arg1, arg2, result)

#include <string>
#include <vector>
#include <sstream>

// Opcodes de la IR
enum IROpcode {
    // Aritméticas
    IR_ADD, IR_SUB, IR_MUL, IR_DIV, IR_MOD,
    // Lógicas
    IR_AND, IR_OR, IR_NOT, IR_NEG,
    // Comparación (resultado booleano 0/1)
    IR_EQ, IR_NEQ, IR_LT, IR_LTE, IR_GT, IR_GTE,
    // Copia / asignación
    IR_COPY,
    // Conversión de tipos
    IR_ITOR, IR_RTOI,
    // Control de flujo
    IR_LABEL,   // etiqueta: (arg1 = nombre etiqueta)
    IR_JMP,     // goto L   (arg1 = etiqueta)
    IR_JZ,      // if arg1==0 goto L   (arg2 = etiqueta)
    IR_JNZ,     // if arg1!=0 goto L   (arg2 = etiqueta)
    // Funciones
    IR_FUNC_BEGIN,
    IR_FUNC_END,
    IR_RETURN,
    // E/S
    IR_PRINT_INT,
    IR_PRINT_REAL,
    IR_PRINT_NL,
    // Llamadas a función (BND-8)
    IR_CALL,       // arg1=func, result=dest (ARG_NONE si void)
    // Lectura de stdin (BND-12)
    IR_READ_INT,   // result = scanf("%ld", &result)
    IR_READ_REAL,  // result = scanf("%lf", &result)
    // Fin
    IR_HALT,
};

// [IR-2] Tipos de argumentos en cuádruplas
enum IRArgKind {
    ARG_NONE,
    ARG_VAR,        // variable con dirección en memoria
    ARG_TEMP,       // temporal sintético (tN)
    ARG_CONST_INT,
    ARG_CONST_REAL,
    ARG_LABEL,      // referencia a etiqueta
    ARG_FUNC,       // nombre de función
};

struct IRArg {
    IRArgKind kind = ARG_NONE;
    std::string name;   // para VAR, TEMP, LABEL, FUNC
    int   addr = -1;    // dirección de memoria para VAR y TEMP
    int   ival = 0;     // para CONST_INT
    float rval = 0.0f;  // para CONST_REAL
    int   type = -1;    // ENTERO=0, REAL=1, LOGICO=2

    static IRArg none() { return IRArg{}; }

    static IRArg var(const std::string& n, int a, int t) {
        IRArg arg; arg.kind = ARG_VAR; arg.name = n; arg.addr = a; arg.type = t;
        return arg;
    }
    static IRArg temp(const std::string& n, int a, int t) {
        IRArg arg; arg.kind = ARG_TEMP; arg.name = n; arg.addr = a; arg.type = t;
        return arg;
    }
    static IRArg constInt(int v) {
        IRArg arg; arg.kind = ARG_CONST_INT; arg.ival = v; arg.type = 0;
        return arg;
    }
    static IRArg constReal(float v) {
        IRArg arg; arg.kind = ARG_CONST_REAL; arg.rval = v; arg.type = 1;
        return arg;
    }
    static IRArg label(const std::string& l) {
        IRArg arg; arg.kind = ARG_LABEL; arg.name = l;
        return arg;
    }
    static IRArg func(const std::string& f) {
        IRArg arg; arg.kind = ARG_FUNC; arg.name = f;
        return arg;
    }

    bool isNone() const { return kind == ARG_NONE; }

    // Representación legible para el visualizador de IR
    std::string str() const {
        switch (kind) {
            case ARG_NONE:      return "_";
            case ARG_VAR:       return name + "@" + std::to_string(addr);
            case ARG_TEMP:      return name;
            case ARG_CONST_INT: return std::to_string(ival);
            case ARG_CONST_REAL: {
                std::ostringstream os; os << rval; return os.str();
            }
            case ARG_LABEL: return name;
            case ARG_FUNC:  return name;
        }
        return "?";
    }
};

// [IR-1] La cuádrupla: (op, arg1, arg2, result)
struct IRQuad {
    IROpcode op;
    IRArg    arg1;
    IRArg    arg2;
    IRArg    result;
    int      type = -1;   // tipo del resultado

    IRQuad(IROpcode o,
           IRArg a1 = IRArg{},
           IRArg a2 = IRArg{},
           IRArg r  = IRArg{},
           int   t  = -1)
        : op(o), arg1(a1), arg2(a2), result(r), type(t) {}
};

// Programa IR: lista plana de cuádruplas + contadores
struct IRProgram {
    std::vector<IRQuad> quads;

    // [IR-2] Contador de temporales
    int nextTempId   = 0;
    int nextTempAddr = 16000;   // espacio de memoria para temps (igual que parser.y)

    // [IR-3] Contador de etiquetas
    int nextLabelId  = 0;

    void emit(IROpcode op,
              IRArg a1 = IRArg{},
              IRArg a2 = IRArg{},
              IRArg r  = IRArg{},
              int   t  = -1) {
        quads.emplace_back(op, a1, a2, r, t);
    }

    // [IR-2] Crea un nuevo temporal con dirección asignada
    IRArg newTemp(int type) {
        std::string name = "t" + std::to_string(nextTempId++);
        int addr = nextTempAddr++;
        return IRArg::temp(name, addr, type);
    }

    // [IR-3] Crea una nueva etiqueta única
    std::string newLabel() {
        return "L" + std::to_string(nextLabelId++);
    }
};

#endif

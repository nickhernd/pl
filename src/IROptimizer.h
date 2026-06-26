#ifndef _IR_OPTIMIZER_H
#define _IR_OPTIMIZER_H

// [IR-8] Optimizaciones Locales: Eliminación de código muerto
//
// Un temporal es "muerto" si se define pero nunca se usa como operando.
// Se eliminan las cuádruplas cuyo resultado es un temporal muerto.
// Se hace un punto fijo porque eliminar una cuádrupla puede hacer
// que otros temporales queden también muertos.

#include "IR.h"
#include <unordered_set>
#include <string>

class IROptimizer {
    // Recoge todos los temporales que aparecen como operandos (usados)
    static std::unordered_set<std::string> collectUsed(const IRProgram& prog) {
        std::unordered_set<std::string> used;
        for (const auto& q : prog.quads) {
            if (q.arg1.kind == ARG_TEMP) used.insert(q.arg1.name);
            if (q.arg2.kind == ARG_TEMP) used.insert(q.arg2.name);
            // También los destinos de operaciones de E/S o saltos
            if (q.result.kind == ARG_VAR) { /* variables siempre se conservan */ }
        }
        return used;
    }

public:
    // Eliminación de código muerto (iteración hasta punto fijo)
    static int eliminateDeadCode(IRProgram& prog) {
        int totalRemoved = 0;

        while (true) {
            auto used = collectUsed(prog);

            std::vector<IRQuad> alive;
            alive.reserve(prog.quads.size());
            int removed = 0;

            for (const auto& q : prog.quads) {
                // Una cuádrupla es "muerta" si:
                //   - su resultado es un temporal
                //   - ese temporal nunca se usa
                //   - la instrucción no tiene efectos secundarios (no es salto,
                //     no es print, no es halt, no es return, no es etiqueta)
                bool hasEffect = (q.op == IR_JMP   || q.op == IR_JZ    ||
                                  q.op == IR_JNZ   || q.op == IR_LABEL  ||
                                  q.op == IR_FUNC_BEGIN || q.op == IR_FUNC_END ||
                                  q.op == IR_RETURN || q.op == IR_HALT  ||
                                  q.op == IR_PRINT_INT || q.op == IR_PRINT_REAL ||
                                  q.op == IR_PRINT_NL  || q.op == IR_COPY ||
                                  q.op == IR_CALL   ||
                                  q.op == IR_READ_INT  || q.op == IR_READ_REAL);

                bool isDead = (!hasEffect)                         &&
                              (q.result.kind == ARG_TEMP)          &&
                              (used.find(q.result.name) == used.end());

                if (isDead) {
                    ++removed;
                } else {
                    alive.push_back(q);
                }
            }

            prog.quads = alive;
            totalRemoved += removed;

            if (removed == 0) break;   // punto fijo
        }

        return totalRemoved;
    }
};

#endif

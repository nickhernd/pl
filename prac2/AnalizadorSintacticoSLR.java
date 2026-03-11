import java.util.Stack;

public class AnalizadorSintacticoSLR {

    private AnalizadorLexico al;

    // -----------------------------------------------------------------------
    // Tabla ACTION[estado][token]
    //   Codificacion: 0=error, >0=desplazar (estado=valor-100), <0=reducir
    //   (regla=-valor), 9999=aceptar
    //
    // Tokens (columnas, indices Token.*):
    //   class=0 id=1 lbra=2 rbra=3 fun=4 int=5 float=6 pyc=7
    //   asig=8  print=9 opas=10 numentero=11 numreal=12 EOF=13
    // -----------------------------------------------------------------------
    private static final int[][] ACTION = {
        // 0: class->s2
        { 102,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0 },
        // 1: EOF->accept
        {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 9999 },
        // 2: id->s3
        {   0, 103,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0 },
        // 3: lbra->s4
        {   0,   0, 104,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0 },
        // 4: class->s2 fun->s8 FOLLOW(M)->r4
        { 102,  -4,  -4,  -4, 108,  -4,  -4,   0,   0,  -4,   0,   0,   0,    0 },
        // 5: rbra->s9
        {   0,   0,   0, 109,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0 },
        // 6: (M->Fun.M) class->s2 fun->s8 FOLLOW(M)->r4
        { 102,  -4,  -4,  -4, 108,  -4,  -4,   0,   0,  -4,   0,   0,   0,    0 },
        // 7: (M->S.M)  class->s2 fun->s8 FOLLOW(M)->r4
        { 102,  -4,  -4,  -4, 108,  -4,  -4,   0,   0,  -4,   0,   0,   0,    0 },
        // 8: id->s12
        {   0, 112,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0 },
        // 9: reduce 1 on FOLLOW(S)
        {  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0,   0,  -1,   0,   0,   0,   -1 },
        // 10: reduce 2 on FOLLOW(M)
        {   0,  -2,  -2,  -2,   0,  -2,  -2,   0,   0,  -2,   0,   0,   0,    0 },
        // 11: reduce 3 on FOLLOW(M)
        {   0,  -3,  -3,  -3,   0,  -3,  -3,   0,   0,  -3,   0,   0,   0,    0 },
        // 12: lbra->s13
        {   0,   0, 113,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0 },
        // 13: (Fun->fun id lbra.M Cod rbra) class->s2 fun->s8 FOLLOW(M)->r4
        { 102,  -4,  -4,  -4, 108,  -4,  -4,   0,   0,  -4,   0,   0,   0,    0 },
        // 14: int->s22 float->s23 lbra->s18 id->s19 print->s20
        {   0, 119, 118,   0,   0, 122, 123,   0,   0, 120,   0,   0,   0,    0 },
        // 15: rbra->s24 pyc->s25
        {   0,   0,   0, 124,   0,   0,   0, 125,   0,   0,   0,   0,   0,    0 },
        // 16: reduce 10 on FOLLOW(Cod)
        {   0,   0,   0, -10,   0,   0,   0, -10,   0,   0,   0,   0,   0,    0 },
        // 17: reduce 11 on FOLLOW(I)
        {   0,   0,   0, -11,   0,   0,   0, -11,   0,   0,   0,   0,   0,    0 },
        // 18: (I->lbra.Cod rbra) same shifts as 14
        {   0, 119, 118,   0,   0, 122, 123,   0,   0, 120,   0,   0,   0,    0 },
        // 19: asig->s28
        {   0,   0,   0,   0,   0,   0,   0,   0, 128,   0,   0,   0,   0,    0 },
        // 20: (I->print.E) numentero->s31 numreal->s32 id->s33
        {   0, 133,   0,   0,   0,   0,   0,   0,   0,   0,   0, 131, 132,    0 },
        // 21: id->s37
        {   0, 137,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0 },
        // 22: reduce 7 on FOLLOW(Tipo)={id}
        {   0,  -7,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0 },
        // 23: reduce 8 on FOLLOW(Tipo)={id}
        {   0,  -8,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0 },
        // 24: reduce 5 on FOLLOW(Fun)
        {  -5,  -5,  -5,  -5,  -5,  -5,  -5,   0,   0,  -5,   0,   0,   0,    0 },
        // 25: (Cod->Cod pyc.I) int->s22 float->s23 lbra->s18 id->s19 print->s20
        {   0, 119, 118,   0,   0, 122, 123,   0,   0, 120,   0,   0,   0,    0 },
        // 26: (I->lbra Cod.rbra) rbra->s27 pyc->s25
        {   0,   0,   0, 127,   0,   0,   0, 125,   0,   0,   0,   0,   0,    0 },
        // 27: reduce 12 on FOLLOW(I)
        {   0,   0,   0, -12,   0,   0,   0, -12,   0,   0,   0,   0,   0,    0 },
        // 28: (I->id asig.E) numentero->s31 numreal->s32 id->s33
        {   0, 133,   0,   0,   0,   0,   0,   0,   0,   0,   0, 131, 132,    0 },
        // 29: (I->id asig E.) rbra->r13 pyc->r13 opas->s34
        {   0,   0,   0, -13,   0,   0,   0, -13,   0,   0, 134,   0,   0,    0 },
        // 30: reduce 16 on FOLLOW(E)
        {   0,   0,   0, -16,   0,   0,   0, -16,   0,   0, -16,   0,   0,    0 },
        // 31: reduce 17 on FOLLOW(F)
        {   0,   0,   0, -17,   0,   0,   0, -17,   0,   0, -17,   0,   0,    0 },
        // 32: reduce 18 on FOLLOW(F)
        {   0,   0,   0, -18,   0,   0,   0, -18,   0,   0, -18,   0,   0,    0 },
        // 33: reduce 19 on FOLLOW(F)
        {   0,   0,   0, -19,   0,   0,   0, -19,   0,   0, -19,   0,   0,    0 },
        // 34: (E->E opas.F) numentero->s31 numreal->s32 id->s33
        {   0, 133,   0,   0,   0,   0,   0,   0,   0,   0,   0, 131, 132,    0 },
        // 35: reduce 15 on FOLLOW(E)
        {   0,   0,   0, -15,   0,   0,   0, -15,   0,   0, -15,   0,   0,    0 },
        // 36: (I->print E.) rbra->r14 pyc->r14 opas->s34
        {   0,   0,   0, -14,   0,   0,   0, -14,   0,   0, 134,   0,   0,    0 },
        // 37: reduce 6 on FOLLOW(DV)
        {   0,   0,   0,  -6,   0,   0,   0,  -6,   0,   0,   0,   0,   0,    0 },
        // 38: reduce 9 on FOLLOW(Cod)
        {   0,   0,   0,  -9,   0,   0,   0,  -9,   0,   0,   0,   0,   0,    0 }
    };

    // -----------------------------------------------------------------------
    // Tabla GOTO[estado][no-terminal]
    //   No-terminales: S=0 M=1 Fun=2 DV=3 Tipo=4 Cod=5 I=6 E=7 F=8
    // -----------------------------------------------------------------------
    private static final int[][] GOTO = new int[39][9];

    static {
        GOTO[0][0]  = 1;   // 0: S->1

        GOTO[4][0]  = 7;   // 4: S->7 M->5 Fun->6
        GOTO[4][1]  = 5;
        GOTO[4][2]  = 6;

        GOTO[6][0]  = 7;   // 6: S->7 M->10 Fun->6
        GOTO[6][1]  = 10;
        GOTO[6][2]  = 6;

        GOTO[7][0]  = 7;   // 7: S->7 M->11 Fun->6
        GOTO[7][1]  = 11;
        GOTO[7][2]  = 6;

        GOTO[13][0] = 7;   // 13: S->7 M->14 Fun->6
        GOTO[13][1] = 14;
        GOTO[13][2] = 6;

        GOTO[14][3] = 17;  // 14: DV->17 Tipo->21 Cod->15 I->16
        GOTO[14][4] = 21;
        GOTO[14][5] = 15;
        GOTO[14][6] = 16;

        GOTO[18][3] = 17;  // 18: DV->17 Tipo->21 Cod->26 I->16
        GOTO[18][4] = 21;
        GOTO[18][5] = 26;
        GOTO[18][6] = 16;

        GOTO[20][7] = 36;  // 20: E->36 F->30
        GOTO[20][8] = 30;

        GOTO[25][3] = 17;  // 25: DV->17 Tipo->21 I->38
        GOTO[25][4] = 21;
        GOTO[25][6] = 38;

        GOTO[28][7] = 29;  // 28: E->29 F->30
        GOTO[28][8] = 30;

        GOTO[34][8] = 35;  // 34: F->35
    }

    // -----------------------------------------------------------------------
    // Informacion de las reglas gramaticales: [longitud_lado_derecho, indice_no_terminal]
    // No-terminales: S=0 M=1 Fun=2 DV=3 Tipo=4 Cod=5 I=6 E=7 F=8
    // -----------------------------------------------------------------------
    private static final int[][] RULE = {
        {0, 0},  // dummy regla 0
        {5, 0},  // 1:  S   -> class id lbra M rbra
        {2, 1},  // 2:  M   -> Fun M
        {2, 1},  // 3:  M   -> S M
        {0, 1},  // 4:  M   -> epsilon
        {6, 2},  // 5:  Fun -> fun id lbra M Cod rbra
        {2, 3},  // 6:  DV  -> Tipo id
        {1, 4},  // 7:  Tipo-> int
        {1, 4},  // 8:  Tipo-> float
        {3, 5},  // 9:  Cod -> Cod pyc I
        {1, 5},  // 10: Cod -> I
        {1, 6},  // 11: I   -> DV
        {3, 6},  // 12: I   -> lbra Cod rbra
        {3, 6},  // 13: I   -> id asig E
        {2, 6},  // 14: I   -> print E
        {3, 7},  // 15: E   -> E opas F
        {1, 7},  // 16: E   -> F
        {1, 8},  // 17: F   -> numentero
        {1, 8},  // 18: F   -> numreal
        {1, 8}   // 19: F   -> id
    };

    public AnalizadorSintacticoSLR(AnalizadorLexico al) {
        this.al = al;
    }

    public void analizar() {
        Stack<Integer> pila   = new Stack<>();
        Stack<Integer> reglas = new Stack<>();

        pila.push(0);
        Token token = al.siguienteToken();

        while (true) {
            int estado = pila.peek();
            int tipo   = token.tipo;
            int accion = ACTION[estado][tipo];

            if (accion == 0) {
                error(estado, token);
                return;
            } else if (accion == 9999) {
                // Aceptar: imprimir reglas en orden de derivacion (inverso al de reduccion)
                while (!reglas.isEmpty()) {
                    System.out.print(reglas.pop() + " ");
                }
                System.out.println();
                return;
            } else if (accion > 0) {
                // Desplazamiento
                pila.push(accion - 100);
                token = al.siguienteToken();
            } else {
                // Reduccion
                int regla = -accion;
                reglas.push(regla);
                int len = RULE[regla][0];
                int nt  = RULE[regla][1];
                for (int i = 0; i < len; i++) {
                    pila.pop();
                }
                int topEstado  = pila.peek();
                int estadoSig  = GOTO[topEstado][nt];
                pila.push(estadoSig);
            }
        }
    }

    private void error(int estado, Token token) {
        StringBuilder esperaba = new StringBuilder();
        for (int i = 0; i < 14; i++) {
            int a = ACTION[estado][i];
            if (a != 0 && a != 9999) {
                if (esperaba.length() > 0) esperaba.append(" ");
                esperaba.append(Token.nombreToken.get(i));
            }
        }

        if (token.tipo == Token.EOF) {
            System.err.println("Error sintactico: encontrado fin de fichero, esperaba " + esperaba);
        } else {
            System.err.println("Error sintactico (" + token.fila + "," + token.columna
                    + "): encontrado '" + token.lexema + "', esperaba " + esperaba);
        }
        System.exit(-1);
    }
}

%{
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comun.h"
#include "TablaSimbolos.h"
#include "TablaTipos.h"

using namespace std;

extern int yylex();
extern int nlin, ncol;
extern char *yytext;
extern int findefichero;
extern FILE *yyin;

void msgError(int nerror, int nlin, int ncol, const char *s) {
     switch (nerror) {
         case ERRLEXICO: fprintf(stderr,"Error lexico (%d,%d): caracter '%s' incorrecto\n",nlin,ncol,s);
            break;
         case ERRSINT: fprintf(stderr,"Error sintactico (%d,%d): en '%s'\n",nlin,ncol,s);
            break;
         case ERREOF: fprintf(stderr,"Error sintactico: fin de fichero inesperado\n");
            break;
         case ERRLEXEOF: fprintf(stderr,"Error lexico: fin de fichero inesperado\n");
            break;
         default:
            fprintf(stderr,"Error semantico (%d,%d): ", nlin,ncol);
            switch(nerror) {
             case ERR_YADECL: fprintf(stderr,"simbolo '%s' ya declarado\n",s);
               break;
             case ERR_NODECL: fprintf(stderr,"identificador '%s' no declarado\n",s);
               break;
             case ERR_NOSC: fprintf(stderr,"identificador '%s' no es un Scanner\n",s);
               break;
             case ERR_SCVAR: fprintf(stderr,"identificador '%s' es de tipo Scanner\n",s);
               break;
             case ERR_TIPOSDECLARRAY: fprintf(stderr,"los tipos deben ser iguales en la declaracion del array '%s'\n",s);
               break;
             case ERR_DIMSDECLARRAY: fprintf(stderr,"las dimensiones deben ser iguales en la declaracion del array '%s'\n",s);
               break;
             case ERR_TIPOSASIG: fprintf(stderr,"tipos incompatibles en asignacion\n");
               break;
             case ERR_TIPOS: fprintf(stderr,"tipos incompatibles en '%s'\n",s);
               break;
             case ERR_TIPOSIFW: fprintf(stderr,"la expresion de if/while debe ser booleana\n");
               break;
             case ERR_OPNOBOOL: fprintf(stderr,"los operandos deben ser booleanos\n");
               break;
             case ERR_NUM: fprintf(stderr,"los operandos deben ser numericos\n");
               break;
             case ERR_DIM: fprintf(stderr,"la dimension debe ser mayor que cero\n");
               break;
             case ERR_FALTAN: fprintf(stderr,"faltan indices\n");
               break;
             case ERR_SOBRAN: fprintf(stderr,"sobran indices\n");
               break;
             case ERR_INDICE_ENTERO: fprintf(stderr,"la expresion entre corchetes debe ser de tipo entero\n");
               break;
             case ERR_NOCABE:fprintf(stderr,"la variable '%s' ya no cabe en memoria\n",s);
               break;
             case ERR_MAXTMP:fprintf(stderr,"no hay espacio para variables temporales\n");
               break;
            }
        }
     exit(1);
}

int yyerror(const char *s) {
    if (findefichero) {
       msgError(ERREOF, -1, -1, "");
    } else {  
       msgError(ERRSINT, nlin, ncol-strlen(yytext), yytext);
    }
    return 0;
}

TablaSimbolos *ts = new TablaSimbolos(NULL);
TablaTipos tt;

unsigned next_dir = 0;
unsigned next_tmp = 16000;
unsigned next_label = 1;
int current_type;

string newLabel() {
    return "L" + to_string(next_label++);
}

unsigned getTemp() {
    if (next_tmp >= 16384) {
        msgError(ERR_MAXTMP, nlin, ncol, "");
    }
    return next_tmp++;
}

void releaseTemp(int n = 1) {
    next_tmp -= n;
}

%}

%union {
    char *lexema;
    Atributos *attr;
}

%token <attr> id nentero nreal relop addop mulop ctebool asig cori cord and_token or_token not_token if_token while_token
%token boolean int_type double_type main_token system_token out_token in_token print_token println_token string_token class_token import_token new_token public_token static_token void_token scanner_token nextint nextdouble else_token coma pyc punto pari pard llavei llaved

%type <attr> S Import SecImp Class Main Tipo Bloque BDecl DVar DimSN Dimensiones LIdent Variable SeqInstr Instr Expr EConj ERel Esimple Term Factor Ref IfGuard WhileGuard

%%

S : Import Class {
    cout << $1->codigo << $2->codigo;
}

Import : Import import_token SecImp pyc {
    $$ = $1;
}
| {
    $$ = new Atributos();
}

SecImp : SecImp punto id { $$ = $1; }
| SecImp punto scanner_token { $$ = $1; }
| id { $$ = new Atributos(); }

Class : public_token class_token id llavei Main llaved {
    $$ = $5;
}

Main : public_token static_token void_token main_token pari string_token cori cord id pard Bloque {
    $$ = $11;
    $$->codigo += "halt\n";
}

Tipo : int_type { $$ = new Atributos(); $$->tipo = ENTERO; $$->tam = 1; }
| double_type { $$ = new Atributos(); $$->tipo = REAL; $$->tam = 1; }
| boolean { $$ = new Atributos(); $$->tipo = LOGICO; $$->tam = 1; }

Bloque : llavei {
    ts = new TablaSimbolos(ts);
} BDecl SeqInstr llaved {
    $$ = new Atributos();
    $$->codigo = $3->codigo + $4->codigo;
    TablaSimbolos *old = ts;
    ts = ts->getParent();
    delete old;
}

BDecl : BDecl DVar {
    $$ = $1;
    $$->codigo += $2->codigo;
}
| {
    $$ = new Atributos();
}

DVar : Tipo { current_type = $1->tipo; } LIdent pyc {
    $$ = $3;
}
| Tipo DimSN id asig new_token Tipo Dimensiones pyc {
    if (ts->get($3->lexema)) {
        msgError(ERR_YADECL, $3->nlin, $3->ncol, $3->lexema.c_str());
    }
    if ($1->tipo != $6->tipo) {
        msgError(ERR_TIPOSDECLARRAY, $3->nlin, $3->ncol, $3->lexema.c_str());
    }
    if ($2->ndims != $7->ndims) {
        msgError(ERR_DIMSDECLARRAY, $3->nlin, $3->ncol, $3->lexema.c_str());
    }

    unsigned tbase = $1->tipo;
    unsigned total_tam = 1;
    for (int i = 0; i < $7->ndims; i++) {
        total_tam *= $7->dims[i];
    }

    unsigned tipo_id = tbase;
    for (int i = $7->ndims - 1; i >= 0; i--) {
        tipo_id = tt.nuevoTipoArray($7->dims[i], tipo_id);
    }

    Simbolo s;
    s.nombre = $3->lexema;
    s.tipo = tipo_id;
    s.dir = next_dir;
    s.tam = total_tam;

    if (next_dir + total_tam > 16000) {
        msgError(ERR_NOCABE, $3->nlin, $3->ncol, $3->lexema.c_str());
    }

    ts->set(s);
    next_dir += total_tam;
    $$ = new Atributos();
}
| scanner_token id asig new_token scanner_token pari system_token punto in_token pard pyc {
    Simbolo s;
    s.nombre = $2->lexema;
    s.tipo = SCVAR;
    s.dir = 0;
    s.tam = 0;
    if (!ts->set(s)) {
        msgError(ERR_YADECL, $2->nlin, $2->ncol, $2->lexema.c_str());
    }
    $$ = new Atributos();
}

DimSN : DimSN cori cord {
    $$ = $1;
    $$->ndims++;
}
| cori cord {
    $$ = new Atributos();
    $$->ndims = 1;
}

Dimensiones : cori nentero cord Dimensiones {
    int val = atoi($2->lexema.c_str());
    if (val <= 0) {
        msgError(ERR_DIM, $2->nlin, $2->ncol, $2->lexema.c_str());
    }
    $$ = $4;
    $$->ndims++;
    $$->dims.insert($$->dims.begin(), val);
}
| cori nentero cord {
    int val = atoi($2->lexema.c_str());
    if (val <= 0) {
        msgError(ERR_DIM, $2->nlin, $2->ncol, $2->lexema.c_str());
    }
    $$ = new Atributos();
    $$->ndims = 1;
    $$->dims.push_back(val);
}

LIdent : LIdent coma Variable {
    $$ = $1;
    $$->codigo += $3->codigo;
}
| Variable {
    $$ = $1;
}

Variable : id {
    Simbolo s;
    s.nombre = $1->lexema;
    s.tipo = current_type;
    s.dir = next_dir;
    s.tam = 1;
    if (next_dir + 1 > 16000) {
        msgError(ERR_NOCABE, $1->nlin, $1->ncol, $1->lexema.c_str());
    }
    if (!ts->set(s)) {
        msgError(ERR_YADECL, $1->nlin, $1->ncol, $1->lexema.c_str());
    }
    next_dir++;
    $$ = new Atributos();
}

SeqInstr : SeqInstr Instr {
    $$ = $1;
    $$->codigo += $2->codigo;
}
| {
    $$ = new Atributos();
}

Instr : pyc { $$ = new Atributos(); }
| Bloque { $$ = $1; }
| Ref asig {
    $<attr>$ = new Atributos();
    $<attr>$->dir = ($1->ref == "@A") ? getTemp() : -1;
} Expr pyc {
    int tmp_addr = $<attr>3->dir;
    $$ = new Atributos();
    if ($1->tipo == SCVAR || $4->tipo == SCVAR) {
        msgError(ERR_SCVAR, $1->nlin, $1->ncol, "");
    }
    if (tt.tipos[$1->tipo].clase == TIPOARRAY) {
        msgError(ERR_FALTAN, $1->nlin, $1->ncol, "");
    }
    $$->codigo = $1->codigo;
    if ($1->ref == "@A") {
        $$->codigo += "mov A " + to_string(tmp_addr) + "\n";
        $$->codigo += $4->codigo;
        if ($1->tipo == REAL && $4->tipo == ENTERO) {
            $$->codigo += "itor\n";
        } else if ($1->tipo != $4->tipo) {
            msgError(ERR_TIPOSASIG, $2->nlin, $2->ncol, "");
        }
        $$->codigo += "mov " + to_string(tmp_addr) + " B\n";
        $$->codigo += "mov A @B+0\n";
        releaseTemp();
    } else {
        $$->codigo += $4->codigo;
        if ($1->tipo == REAL && $4->tipo == ENTERO) {
            $$->codigo += "itor\n";
        } else if ($1->tipo != $4->tipo) {
            msgError(ERR_TIPOSASIG, $2->nlin, $2->ncol, "");
        }
        $$->codigo += "mov A " + $1->ref + "\n";
    }
}
| system_token punto out_token punto println_token pari Expr pard pyc {
    $$ = new Atributos();
    $$->codigo = $7->codigo;
    if ($7->tipo == REAL) {
        $$->codigo += "wrr A\n";
    } else {
        $$->codigo += "wri A\n";
    }
    $$->codigo += "wrl\n";
}
| system_token punto out_token punto print_token pari Expr pard pyc {
    $$ = new Atributos();
    $$->codigo = $7->codigo;
    if ($7->tipo == REAL) {
        $$->codigo += "wrr A\n";
    } else {
        $$->codigo += "wri A\n";
    }
}
| IfGuard Instr {
    $$ = new Atributos();
    string label = newLabel();
    $$->codigo = $1->codigo + "jz " + label + "\n" + $2->codigo + label + "\n";
}
| IfGuard Instr else_token Instr {
    $$ = new Atributos();
    string label_else = newLabel();
    string label_end = newLabel();
    $$->codigo = $1->codigo + "jz " + label_else + "\n" + $2->codigo + "jmp " + label_end + "\n" + label_else + "\n" + $4->codigo + label_end + "\n";
}
| WhileGuard Instr {
    $$ = new Atributos();
    string label_start = newLabel();
    string label_end = newLabel();
    $$->codigo = label_start + "\n" + $1->codigo + "jz " + label_end + "\n" + $2->codigo + "jmp " + label_start + "\n" + label_end + "\n";
}

Expr : Expr or_token EConj {
    if ($1->tipo != LOGICO || $3->tipo != LOGICO) msgError(ERR_OPNOBOOL, $2->nlin, $2->ncol, "||");
    $$ = new Atributos();
    unsigned tmp = getTemp();
    $$->codigo = $3->codigo + "mov A " + to_string(tmp) + "\n" + $1->codigo + "ori " + to_string(tmp) + "\n";
    $$->tipo = LOGICO;
    releaseTemp();
}
| EConj { $$ = $1; }

EConj : EConj and_token ERel {
    if ($1->tipo != LOGICO || $3->tipo != LOGICO) msgError(ERR_OPNOBOOL, $2->nlin, $2->ncol, "&&");
    $$ = new Atributos();
    unsigned tmp = getTemp();
    $$->codigo = $3->codigo + "mov A " + to_string(tmp) + "\n" + $1->codigo + "andi " + to_string(tmp) + "\n";
    $$->tipo = LOGICO;
    releaseTemp();
}
| ERel { $$ = $1; }

ERel : Esimple relop Esimple {
    $$ = new Atributos();
    unsigned tmp = getTemp();
    $$->codigo = $3->codigo;
    if ($1->tipo == REAL && $3->tipo == ENTERO) $$->codigo += "itor\n";
    $$->codigo += "mov A " + to_string(tmp) + "\n";
    $$->codigo += $1->codigo;
    if ($1->tipo == ENTERO && $3->tipo == REAL) $$->codigo += "itor\n";

    if (($1->tipo == LOGICO && $3->tipo == LOGICO) || (($1->tipo == ENTERO || $1->tipo == REAL) && ($3->tipo == ENTERO || $3->tipo == REAL))) {
        if ($1->tipo == REAL || $3->tipo == REAL) {
            if ($2->lexema == "==") $$->codigo += "eqlr " + to_string(tmp) + "\n";
            else if ($2->lexema == "!=") $$->codigo += "neqr " + to_string(tmp) + "\n";
            else if ($2->lexema == "<") $$->codigo += "lssr " + to_string(tmp) + "\n";
            else if ($2->lexema == "<=") $$->codigo += "leqr " + to_string(tmp) + "\n";
            else if ($2->lexema == ">") $$->codigo += "gtrr " + to_string(tmp) + "\n";
            else if ($2->lexema == ">=") $$->codigo += "geqr " + to_string(tmp) + "\n";
        } else {
            if ($2->lexema == "==") $$->codigo += "eqli " + to_string(tmp) + "\n";
            else if ($2->lexema == "!=") $$->codigo += "neqi " + to_string(tmp) + "\n";
            else if ($2->lexema == "<") $$->codigo += "lssi " + to_string(tmp) + "\n";
            else if ($2->lexema == "<=") $$->codigo += "leqi " + to_string(tmp) + "\n";
            else if ($2->lexema == ">") $$->codigo += "gtri " + to_string(tmp) + "\n";
            else if ($2->lexema == ">=") $$->codigo += "geqi " + to_string(tmp) + "\n";
        }
    } else {
        msgError(ERR_TIPOS, $2->nlin, $2->ncol, $2->lexema.c_str());
    }
    $$->tipo = LOGICO;
    releaseTemp();
}
| Esimple { $$ = $1; }

Esimple : Esimple addop Term {
    $$ = new Atributos();
    unsigned tmp = getTemp();
    $$->codigo = $3->codigo;
    if ($1->tipo == REAL && $3->tipo == ENTERO) $$->codigo += "itor\n";
    $$->codigo += "mov A " + to_string(tmp) + "\n";
    $$->codigo += $1->codigo;
    if ($1->tipo == ENTERO && $3->tipo == REAL) $$->codigo += "itor\n";

    if ($1->tipo == REAL || $3->tipo == REAL) {
        if ($2->lexema == "+") $$->codigo += "addr " + to_string(tmp) + "\n";
        else $$->codigo += "subr " + to_string(tmp) + "\n";
        $$->tipo = REAL;
    } else if ($1->tipo == ENTERO && $3->tipo == ENTERO) {
        if ($2->lexema == "+") $$->codigo += "addi " + to_string(tmp) + "\n";
        else $$->codigo += "subi " + to_string(tmp) + "\n";
        $$->tipo = ENTERO;
    } else {
        msgError(ERR_NUM, $2->nlin, $2->ncol, $2->lexema.c_str());
    }
    releaseTemp();
}
| Term { $$ = $1; }

Term : Term mulop Factor {
    $$ = new Atributos();
    unsigned tmp = getTemp();
    $$->codigo = $3->codigo;
    if ($1->tipo == REAL && $3->tipo == ENTERO) $$->codigo += "itor\n";
    $$->codigo += "mov A " + to_string(tmp) + "\n";
    $$->codigo += $1->codigo;
    if ($1->tipo == ENTERO && $3->tipo == REAL) $$->codigo += "itor\n";

    if ($1->tipo == REAL || $3->tipo == REAL) {
        if ($2->lexema == "*") $$->codigo += "mulr " + to_string(tmp) + "\n";
        else $$->codigo += "divr " + to_string(tmp) + "\n";
        $$->tipo = REAL;
    } else if ($1->tipo == ENTERO && $3->tipo == ENTERO) {
        if ($2->lexema == "*") $$->codigo += "muli " + to_string(tmp) + "\n";
        else $$->codigo += "divi " + to_string(tmp) + "\n";
        $$->tipo = ENTERO;
    } else {
        msgError(ERR_NUM, $2->nlin, $2->ncol, $2->lexema.c_str());
    }
    releaseTemp();
}
| Factor { $$ = $1; }

Factor : Ref {
    if (tt.tipos[$1->tipo].clase == TIPOARRAY) {
        msgError(ERR_FALTAN, $1->nlin, $1->ncol, "");
    }
    $$ = new Atributos();
    if ($1->ref == "@A") {
        $$->codigo = $1->codigo + "mov @A A\n";
    } else {
        $$->codigo = $1->codigo + "mov " + $1->ref + " A\n";
    }
    $$->tipo = $1->tipo;
}
| id punto nextint pari pard {
    Simbolo *s = ts->get($1->lexema);
    if (!s) msgError(ERR_NODECL, $1->nlin, $1->ncol, $1->lexema.c_str());
    if (s->tipo != SCVAR) msgError(ERR_NOSC, $1->nlin, $1->ncol, $1->lexema.c_str());
    $$ = new Atributos();
    $$->codigo = "rdi A\n";
    $$->tipo = ENTERO;
}
| id punto nextdouble pari pard {
    Simbolo *s = ts->get($1->lexema);
    if (!s) msgError(ERR_NODECL, $1->nlin, $1->ncol, $1->lexema.c_str());
    if (s->tipo != SCVAR) msgError(ERR_NOSC, $1->nlin, $1->ncol, $1->lexema.c_str());
    $$ = new Atributos();
    $$->codigo = "rdr A\n";
    $$->tipo = REAL;
}
| nentero {
    $$ = new Atributos();
    $$->codigo = "mov #" + $1->lexema + " A\n";
    $$->tipo = ENTERO;
}
| nreal {
    $$ = new Atributos();
    $$->codigo = "mov $" + $1->lexema + " A\n";
    $$->tipo = REAL;
}
| ctebool {
    $$ = new Atributos();
    if ($1->lexema == "true") $$->codigo = "mov #1 A\n";
    else $$->codigo = "mov #0 A\n";
    $$->tipo = LOGICO;
}
| pari Expr pard { $$ = $2; }
| not_token Factor {
    if ($2->tipo != LOGICO) msgError(ERR_OPNOBOOL, $1->nlin, $1->ncol, "!");
    $$ = new Atributos();
    $$->codigo = $2->codigo + "noti A\n";
    $$->tipo = LOGICO;
}
| pari Tipo pard Factor {
    $$ = new Atributos();
    $$->codigo = $4->codigo;
    if ($2->tipo == REAL && $4->tipo == ENTERO) $$->codigo += "itor\n";
    else if ($2->tipo == ENTERO && $4->tipo == REAL) $$->codigo += "rtoi\n";
    else if ($2->tipo == LOGICO && $4->tipo == ENTERO) $$->codigo += "noti\nnoti A\n"; 
    $$->tipo = $2->tipo;
}

Ref : id {
    Simbolo *s = ts->get($1->lexema);
    if (!s) msgError(ERR_NODECL, $1->nlin, $1->ncol, $1->lexema.c_str());
    if (s->tipo == SCVAR) msgError(ERR_SCVAR, $1->nlin, $1->ncol, $1->lexema.c_str());

    $$ = new Atributos();
    $$->ref = to_string(s->dir);
    $$->tipo = s->tipo;
    $$->codigo = "";
    $$->nlin = $1->nlin;
    $$->ncol = $1->ncol;
}
| Ref cori Esimple cord {
    if (tt.tipos[$1->tipo].clase != TIPOARRAY) msgError(ERR_SOBRAN, $2->nlin, $2->ncol, "");
    if ($3->tipo != ENTERO) msgError(ERR_INDICE_ENTERO, $2->nlin, $2->ncol, "");
    
    $$ = new Atributos();
    unsigned tbase = tt.tipos[$1->tipo].tipoBase;
    unsigned tam_base = 1;
    unsigned t = tbase;
    while (tt.tipos[t].clase == TIPOARRAY) {
        tam_base *= tt.tipos[t].tamano;
        t = tt.tipos[t].tipoBase;
    }
    
    $$->codigo = $1->codigo;
    if ($1->ref == "@A") {
        unsigned tmp = getTemp();
        $$->codigo += "mov A " + to_string(tmp) + "\n";
        $$->codigo += $3->codigo;
        if (tam_base > 1) $$->codigo += "muli #" + to_string(tam_base) + "\n";
        $$->codigo += "addi " + to_string(tmp) + "\n";
        releaseTemp();
    } else {
        $$->codigo += $3->codigo;
        if (tam_base > 1) $$->codigo += "muli #" + to_string(tam_base) + "\n";
        $$->codigo += "addi #" + $1->ref + "\n";
    }
    $$->ref = "@A";
    $$->tipo = tbase;
    $$->nlin = $4->nlin;
    $$->ncol = $4->ncol;
}

IfGuard : if_token pari Expr pard {
    if ($3->tipo != LOGICO) msgError(ERR_TIPOSIFW, $1->nlin, $1->ncol, "");
    $$ = $3;
}

WhileGuard : while_token pari Expr pard {
    if ($3->tipo != LOGICO) msgError(ERR_TIPOSIFW, $1->nlin, $1->ncol, "");
    $$ = $3;
}

%%

int main(int argc, char *argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "No se pudo abrir el fichero %s\n", argv[1]);
            exit(1);
        }
    }
    yyparse();
    return 0;
}

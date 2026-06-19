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
#include "ASTNodes.h"

using namespace std;

extern int yylex();
extern int nlin, ncol;
extern char *yytext;
extern int findefichero;
extern FILE *yyin;

Node* rootAST = nullptr;

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
bool is_constant = false;

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

unsigned getSafeTmp(int above) {
    if (above >= 0 && (int)next_tmp <= above) {
        next_tmp = (unsigned)(above + 1);
    }
    return getTemp();
}

%}

%code requires {
  #include "ASTNodes.h"
  #include "comun.h"
}

%union {
    char *lexema;
    Atributos *attr;
    Node *node;
    StmtNode *stmt;
    ExprNode *expr;
    BlockNode *block;
}

%token <attr> id nentero nreal relop addop mulop ctebool asig cori cord and_token or_token not_token if_token while_token system_token return_token final_token class_token public_token static_token void_token main_token
%token boolean int_type double_type out_token in_token print_token println_token string_token import_token new_token scanner_token nextint nextdouble else_token coma pyc punto pari pard llavei llaved

%type <attr> Import SecImp Tipo BDecl DVar DimSN Dimensiones LIdent Variable Ref 
%type <node> S Class
%type <stmt> Main Method Member Instr
%type <block> Bloque SeqInstr Members
%type <expr> Expr EConj ERel Esimple Term Factor IfGuard WhileGuard

%%

S : Import Class {
    rootAST = $2;
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

Class : public_token class_token id llavei Members llaved {
    $$ = new ProgramNode($5);
}

Members : Members Member {
    if ($2) $1->add($2);
    $$ = $1;
}
| {
    $$ = new BlockNode(nlin, ncol);
}

Member : Main { $$ = $1; }
| Method { $$ = $1; }
| DVar { $$ = nullptr; }

Main : public_token static_token void_token main_token pari string_token cori cord id pard Bloque {
    $$ = new MethodNode("main", -1, $11, $1->nlin, $1->ncol);
}

Method : public_token static_token Tipo id pari pard Bloque {
    Simbolo s;
    s.nombre = $4->lexema;
    s.tipo = $3->tipo;
    s.isFunction = true;
    s.returnType = $3->tipo;
    ts->set(s);
    $$ = new MethodNode($4->lexema, $3->tipo, $7, $4->nlin, $4->ncol);
}
| public_token static_token void_token id pari pard Bloque {
    Simbolo s;
    s.nombre = $4->lexema;
    s.tipo = -1;
    s.isFunction = true;
    s.returnType = -1;
    ts->set(s);
    $$ = new MethodNode($4->lexema, -1, $7, $4->nlin, $4->ncol);
}

Tipo : int_type { $$ = new Atributos(); $$->tipo = ENTERO; $$->tam = 1; }
| double_type { $$ = new Atributos(); $$->tipo = REAL; $$->tam = 1; }
| boolean { $$ = new Atributos(); $$->tipo = LOGICO; $$->tam = 1; }

Bloque : llavei {
    ts = new TablaSimbolos(ts);
} BDecl SeqInstr llaved {
    $$ = $4;
    $$->symbols = ts;
    ts = ts->getParent();
}

BDecl : BDecl DVar {
    $$ = $1;
}
| {
    $$ = new Atributos();
}

DVar : Tipo { current_type = $1->tipo; is_constant = false; } LIdent pyc {
    $$ = $3;
}
| final_token Tipo { current_type = $2->tipo; is_constant = true; } LIdent pyc {
    $$ = $4;
}
| Tipo DimSN id asig new_token Tipo Dimensiones pyc {
    Simbolo s;
    s.nombre = $3->lexema;
    s.tipo = $1->tipo;
    s.isConstant = false;
    s.dir = next_dir;
    ts->set(s);
    next_dir++;
    $$ = new Atributos();
}
| scanner_token id asig new_token scanner_token pari system_token punto in_token pard pyc {
    Simbolo s;
    s.nombre = $2->lexema;
    s.tipo = SCVAR;
    s.isConstant = false;
    ts->set(s);
    $$ = new Atributos();
}

DimSN : DimSN cori cord { $$ = $1; }
| cori cord { $$ = new Atributos(); }

Dimensiones : cori nentero cord Dimensiones { $$ = $4; }
| cori nentero cord { $$ = new Atributos(); }

LIdent : LIdent coma Variable { $$ = $1; }
| Variable { $$ = $1; }

Variable : id {
    Simbolo s;
    s.nombre = $1->lexema;
    s.tipo = current_type;
    s.isConstant = is_constant;
    s.dir = next_dir;
    ts->set(s);
    next_dir++;
    $$ = new Atributos();
}

SeqInstr : SeqInstr Instr {
    if ($2) $1->add($2);
    $$ = $1;
}
| {
    $$ = new BlockNode(nlin, ncol);
}

Instr : pyc { $$ = nullptr; }
| Bloque { $$ = $1; }
| Ref asig Expr pyc {
    // Necesitamos convertir Ref (Atributos) a un Nodo adecuado. 
    // Como Ref es complicado, por ahora mantengamos la estructura, pero esto debe evolucionar.
    $$ = new AssignNode(new IdentifierNode($1->lexema, $1->nlin, $1->ncol), $3, $2->nlin, $2->ncol);
}
| system_token punto out_token punto println_token pari Expr pard pyc {
    $$ = new PrintNode($7, true, $1->nlin, $1->ncol); 
}
| system_token punto out_token punto print_token pari Expr pard pyc {
    $$ = new PrintNode($7, false, $1->nlin, $1->ncol);
}
| IfGuard Instr {
    $$ = new IfNode($1, $2, nullptr, $1->line, $1->column);
}
| IfGuard Instr else_token Instr {
    $$ = new IfNode($1, $2, $4, $1->line, $1->column);
}
| WhileGuard Instr {
    $$ = new WhileNode($1, $2, $1->line, $1->column);
}
| return_token Expr pyc {
    $$ = new ReturnNode($2, $1->nlin, $1->ncol);
}
| return_token pyc {
    $$ = new ReturnNode(nullptr, $1->nlin, $1->ncol);
}

Expr : Expr or_token EConj {
    $$ = new BinaryExprNode("||", $1, $3, $2->nlin, $2->ncol);
}
| EConj { $$ = $1; }

EConj : EConj and_token ERel {
    $$ = new BinaryExprNode("&&", $1, $3, $2->nlin, $2->ncol);
}
| ERel { $$ = $1; }

ERel : Esimple relop Esimple {
    $$ = new BinaryExprNode($2->lexema, $1, $3, $2->nlin, $2->ncol);
}
| Esimple { $$ = $1; }

Esimple : Esimple addop Term {
    $$ = new BinaryExprNode($2->lexema, $1, $3, $2->nlin, $2->ncol);
}
| Term { $$ = $1; }

Term : Term mulop Factor {
    $$ = new BinaryExprNode($2->lexema, $1, $3, $2->nlin, $2->ncol);
}
| Factor { $$ = $1; }

Factor : pari Expr pard {
    $$ = $2;
}
| id {
    $$ = new IdentifierNode($1->lexema, $1->nlin, $1->ncol);
}
| nentero {
    $$ = new IntLiteralNode(atoi($1->lexema.c_str()), $1->nlin, $1->ncol);
}
| nreal {
    $$ = new FloatLiteralNode(atof($1->lexema.c_str()), $1->nlin, $1->ncol);
}
| ctebool {
    $$ = new BoolLiteralNode(($1->lexema == "true"), $1->nlin, $1->ncol);
}
| Ref {
    $$ = new IdentifierNode($1->lexema, $1->nlin, $1->ncol);
}
| not_token Factor {
    $$ = new UnaryExprNode($1->lexema, $2, $1->nlin, $1->ncol); 
}
| addop Factor {
    $$ = new UnaryExprNode($1->lexema, $2, $1->nlin, $1->ncol);
}
| id punto nextint pari pard {
    $$ = new IntLiteralNode(0, $1->nlin, $1->ncol);
}
| id punto nextdouble pari pard {
    $$ = new FloatLiteralNode(0.0, $1->nlin, $1->ncol);
}

Ref : id {
    $$ = $1;
}
| Ref cori Esimple cord {
    $$ = $1;
}

IfGuard : if_token pari Expr pard {
    $$ = $3;
}

WhileGuard : while_token pari Expr pard {
    $$ = $3;
}

%%

#include "ASTVisualizer.h"
#include "DOTVisualizer.h"
#include "CodeGenerator.h"
#include "SemanticVisitor.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "No se pudo abrir el fichero %s\n", argv[1]);
            exit(1);
        }
    }
    if (yyparse() == 0 && rootAST) {
        SemanticVisitor semantic(ts, &tt);
        rootAST->accept(&semantic);
        
        if (semantic.success()) {
            CodeGenerator gen;
            gen.generate(rootAST, 4096);
        } else {
            std::cerr << "Compilation failed due to semantic errors." << std::endl;
        }
        delete rootAST;
    }
    return 0;
}

%{
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comun.h"
#include "TablaSimbolos.h"

using namespace std;

extern int nlin, ncol, findefichero;
extern int yylex();
extern char *yytext;
extern FILE *yyin;

void msgError(int nerror, int nlin, int ncol, const char *s);
void errorSemantico(int nerror, char *lexema, int fila, int columna);

string prefix = "";
vector<string> prefixStack;
TablaSimbolos *ts = new TablaSimbolos(NULL);

const int ERRYADECL=1, ERRNODECL=2, ERRTIPOS=3, ERRNOSIMPLE=4, ERRNOENTERO=5;

string itor(tAtributos a) {
    if (a.tipo == ENTERO) return "itor(" + a.cod + ")";
    return a.cod;
}

int yyerror(char *s);

%}

%token CLASS FUN INT FLOAT PRINT IF ELSE FI
%token ID NUMENTERO NUMREAL
%token AS MD REL ASIGN DOSPTOS LLAVEI LLAVED PARI PARD PYC COMA

%left REL
%left AS
%left MD

%%

S : Componentes {
        cout << $1.cod;
        int tk = yylex();
        if (tk != 0) yyerror("");
    }
  ;

Componentes : Componentes Componente { $$.cod = $1.cod + $2.cod; }
            | { $$.cod = ""; }
            ;

Componente : Clase { $$.cod = $1.cod; }
           | Funcion { $$.cod = $1.cod; }
           | Declaracion { $$.cod = $1.cod; }
           | Sentencia { $$.cod = $1.cod; }
           | PYC { $$.cod = ""; }
           ;

Clase : CLASS ID {
          prefixStack.push_back(prefix);
          prefix += $2.lexema + "_";
          ts = new TablaSimbolos(ts);
        }
        LLAVEI Componentes LLAVED {
          string className = $2.lexema;
          string pre = prefixStack.back();
          prefix = prefixStack.back();
          prefixStack.pop_back();
          ts = ts->padre;
          $$.cod = "// class " + pre + className + "\n" + $5.cod + "\n";
        }
      ;

Funcion : FUN ID {
            prefixStack.push_back(prefix);
            prefix += $2.lexema + "_";
            ts = new TablaSimbolos(ts);
          }
          Argumentos {
            // No podemos poner el cout aqui
          }
          LLAVEI Componentes LLAVED {
            string funcName = $2.lexema;
            string fullFuncName = prefixStack.back() + funcName;
            string args = $4.cod;
            string body = $7.cod;
            prefix = prefixStack.back();
            prefixStack.pop_back();
            ts = ts->padre;
            $$.cod = "void " + fullFuncName + "(" + args + ") {\n" + body + "} // " + fullFuncName + "\n\n";
          }
        ;

Argumentos : ArgumentosList { $$.cod = $1.cod; }
           | { $$.cod = ""; }
           ;

ArgumentosList : ArgumentosList PYC Argumento { $$.cod = $1.cod + "," + $3.cod; }
               | Argumento { $$.cod = $1.cod; }
               ;

Argumento : Tipo ID {
              string trad = "arg_" + prefix + $2.lexema;
              if (!ts->set({$2.lexema, $1.tipo, trad}))
                  errorSemantico(ERRYADECL, (char*)$2.lexema.c_str(), $2.nlin, $2.ncol);
              $$.cod = ($1.tipo == ENTERO ? "int " : "float ") + trad;
            }
          ;

Tipo : INT { $$.tipo = ENTERO; }
     | FLOAT { $$.tipo = REAL; }
     ;

Declaracion : Tipo ID {
                string trad = prefix + $2.lexema;
                if (!ts->set({$2.lexema, $1.tipo, trad}))
                    errorSemantico(ERRYADECL, (char*)$2.lexema.c_str(), $2.nlin, $2.ncol);
                $$.cod = "\n" + string($1.tipo == ENTERO ? "int " : "float ") + trad + ";\n\n";
              }
            ;

Sentencia : Asignacion { $$.cod = $1.cod; }
          | Print { $$.cod = $1.cod; }
          | IfStmt { $$.cod = $1.cod; }
          | Bloque { $$.cod = $1.cod; }
          ;

Asignacion : ID ASIGN Exp {
               Simbolo *s = ts->get($1.lexema);
               if (!s) errorSemantico(ERRNODECL, (char*)$1.lexema.c_str(), $1.nlin, $1.ncol);
               if (s->tipo == ENTERO && $3.tipo == REAL)
                   errorSemantico(ERRTIPOS, (char*)"=", $2.nlin, $2.ncol);
               
               string res = $3.cod;
               if (s->tipo == REAL && $3.tipo == ENTERO) res = "itor(" + res + ")";
               $$.cod = "  " + s->nomtrad + " = " + res + ";\n";
             }
           | ID ASIGN error { yyerrok; $$.cod = ""; }
           ;

Print : PRINT Exp {
          if ($2.tipo == ENTERO)
              $$.cod = "  printf(\"%d\"," + $2.cod + ");\n";
          else
              $$.cod = "  printf(\"%f\"," + $2.cod + ");\n";
        }
      ;

IfStmt : IF Exp DOSPTOS Componente ElsePart FI {
           $$.cod = "if (" + $2.cod + ")\n" + $4.cod + $5.cod;
         }
       ;

ElsePart : ELSE Componente { $$.cod = "else\n" + $2.cod; }
         | { $$.cod = ""; }
         ;

Bloque : LLAVEI {
           prefixStack.push_back(prefix);
           prefix += "_";
           ts = new TablaSimbolos(ts);
         }
         Componentes LLAVED {
           string body = $3.cod;
           prefix = prefixStack.back();
           prefixStack.pop_back();
           ts = ts->padre;
           $$.cod = "{\n" + body + "}\n\n";
         }
       ;

Exp : Exp AS Exp {
        if ($1.tipo == REAL || $3.tipo == REAL) {
            $$.tipo = REAL;
            $$.cod = itor($1) + " " + $2.lexema + "r " + itor($3);
        } else {
            $$.tipo = ENTERO;
            $$.cod = $1.cod + " " + $2.lexema + "i " + $3.cod;
        }
      }
    | Exp MD Exp {
        if ($1.tipo == REAL || $3.tipo == REAL) {
            $$.tipo = REAL;
            $$.cod = itor($1) + " " + $2.lexema + "r " + itor($3);
        } else {
            $$.tipo = ENTERO;
            $$.cod = $1.cod + " " + $2.lexema + "i " + $3.cod;
        }
      }
    | Exp REL Exp {
        $$.tipo = ENTERO;
        string op = $2.lexema;
        if ($1.tipo == REAL || $3.tipo == REAL) {
            $$.cod = itor($1) + " " + op + "r " + itor($3);
        } else {
            $$.cod = $1.cod + " " + op + "i " + $3.cod;
        }
      }
    | PARI Exp PARD {
        $$.tipo = $2.tipo;
        $$.cod = "(" + $2.cod + ")";
      }
    | ID {
        Simbolo *s = ts->get($1.lexema);
        if (!s) errorSemantico(ERRNODECL, (char*)$1.lexema.c_str(), $1.nlin, $1.ncol);
        $$.tipo = s->tipo;
        $$.cod = s->nomtrad;
      }
    | NUMENTERO {
        $$.tipo = ENTERO;
        $$.cod = $1.lexema;
      }
    | NUMREAL {
        $$.tipo = REAL;
        $$.cod = $1.lexema;
      }
    ;

%%

void errorSemantico(int nerror, char *lexema, int fila, int columna)
{
    fprintf(stderr,"Error semantico (%d,%d): en '%s', ",fila,columna,lexema);
    switch (nerror) {
      case ERRYADECL: fprintf(stderr,"ya existe en este ambito\n");
         break;
      case ERRNODECL: fprintf(stderr,"no ha sido declarado\n");
         break;
      case ERRTIPOS: fprintf(stderr,"tipos incompatibles entero/real\n");
         break;
      case ERRNOSIMPLE: fprintf(stderr,"debe ser de tipo entero o real\n");
         break;
      case ERRNOENTERO: fprintf(stderr,"la expresion debe ser de tipo entero\n");
         break;
    }
    exit(-1);
}

void msgError(int nerror, int nlin, int ncol, const char *s)
{
     switch (nerror) {
         case ERRLEXICO: fprintf(stderr,"Error lexico (%d,%d): caracter '%s' incorrecto\n",nlin,ncol,s);
            break;
         case ERRSINT: fprintf(stderr,"Error sintactico (%d,%d): en '%s'\n",nlin,ncol,s);
            break;
         case ERREOF: fprintf(stderr,"Error sintactico: fin de fichero inesperado\n");
            break;
         case ERRLEXEOF: fprintf(stderr,"Error lexico: fin de fichero inesperado\n");
            break;
     }
     exit(1);
}

int yyerror(char *s)
{
    if (findefichero) 
    {
       msgError(ERREOF,-1,-1,"");
    }
    else
    {  
       msgError(ERRSINT,nlin,ncol-strlen(yytext),yytext);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    FILE *fent;

    if (argc==2)
    {
        fent = fopen(argv[1],"rt");
        if (fent)
        {
            yyin = fent;
            yyparse();
            fclose(fent);
        }
        else
            fprintf(stderr,"No puedo abrir el fichero\n");
    }
    else
        yyparse();
    return 0;
}

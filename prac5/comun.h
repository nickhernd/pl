#ifndef _COMUN_H
#define _COMUN_H

#include <string>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int ERRLEXICO=1,
          ERRSINT=2,
          ERREOF=3,
          ERRLEXEOF=4,
          
          ERR_YADECL=10,
          ERR_NODECL=11,
          ERR_DIM=12,
          ERR_NOCABE=13,

          ERR_FALTAN=20,
          ERR_SOBRAN=21,
          ERR_INDICE_ENTERO=22,

          ERR_NOSC=30,
          ERR_TIPOSDECLARRAY=31,
          ERR_DIMSDECLARRAY=32,
          ERR_TIPOSASIG=33,
          ERR_SCVAR=34,
          ERR_TIPOSIFW=35,
          ERR_OPNOBOOL=36,
          ERR_NUM=37,
          ERR_TIPOS=38,

          ERR_MAXTMP=100;

extern int nlin, ncol;
extern char *yytext;

struct Atributos {
    string codigo;
    int tipo;
    unsigned dir;
    unsigned tam;
    unsigned tbase;
    int ndims;
    vector<unsigned> dims;
    string ref; 

    Atributos() : codigo(""), tipo(-1), dir(0), tam(0), tbase(0), ndims(0), ref("") {}
};

void msgError(int nerror, int nlin, int ncol, const char *s);

#endif

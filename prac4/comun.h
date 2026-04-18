#ifndef COMUN_H
#define COMUN_H

#include <string>

using namespace std;

typedef struct {
    string lexema;
    int nlin;
    int ncol;
    int tipo;
    string cod;
    string trad; // Para el nombre traducido de variables
} tAtributos;

#define YYSTYPE tAtributos

#define ERRLEXICO    1
#define ERRSINT      2
#define ERREOF       3
#define ERRLEXEOF    4

void msgError(int nerror, int nlin, int ncol, const char *s);

#endif

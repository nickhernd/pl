#ifndef _TablaSimbolos_
#define _TablaSimbolos_

#include <string>
#include <vector>

using namespace std;

const int ENTERO=0;
const int REAL=1;
const int LOGICO=2;
const int SCVAR=3;   // Scanner


struct Simbolo {

  string nombre;
  unsigned tipo;
  unsigned dir;
  unsigned tam;
  bool isConstant = false;
  bool isAssigned = false;
  bool isFunction = false;
  int returnType = -1;
};


class TablaSimbolos {

   public:
   
      TablaSimbolos *padre;
      vector<Simbolo> simbolos;
   
   
   TablaSimbolos(TablaSimbolos *padre);
   TablaSimbolos *getParent() { return padre; }
   
   bool set(Simbolo s);
   Simbolo* get(string nombre);
   bool isDeclared(string name); // ver si está declarada en algún ámbito (no sólo en el actual)
};

#endif

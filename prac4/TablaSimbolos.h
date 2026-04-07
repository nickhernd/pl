
#include <string>
#include <vector>

using namespace std;

const int ENTERO=1;
const int REAL=2;
const int CLASSFUN=3;

struct Simbolo {

  string nombre;
  int tipo;
  string nomtrad;
};


class TablaSimbolos {

   private:
   
     bool buscarAmbito(Simbolo s); // ver si está en el ámbito actual

   public:
   
      TablaSimbolos *padre;
      vector<Simbolo> simbolos;
   
   
   TablaSimbolos(TablaSimbolos *padre);
   TablaSimbolos *getParent() { return padre; }
   
   bool set(Simbolo s);
   Simbolo* get(string nombre);
};



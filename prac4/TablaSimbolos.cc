
using namespace std;

#include "TablaSimbolos.h"

TablaSimbolos::TablaSimbolos(TablaSimbolos *padre)
{
      this->padre = padre;
}

bool TablaSimbolos::buscarAmbito(Simbolo s)
{
     for (unsigned i=0;i<simbolos.size();i++)
       if (simbolos[i].nombre == s.nombre)
          return true;
     return false;
}

bool TablaSimbolos::set(Simbolo s)
{
     if (buscarAmbito(s))  // repetido en el ámbito
       return false;
     simbolos.push_back(s);
     return true;
}

Simbolo* TablaSimbolos::get(string nombre)
{
     for (unsigned i=0;i<simbolos.size();i++)
       if (simbolos[i].nombre == nombre) return &(simbolos[i]);
       
     if (padre != NULL)
       return padre->get(nombre);
     else
       return NULL;
}

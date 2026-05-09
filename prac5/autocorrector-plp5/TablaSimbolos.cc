
using namespace std;

#include "TablaSimbolos.h"

TablaSimbolos::TablaSimbolos(TablaSimbolos *padre)
{
      this->padre = padre;
}

bool TablaSimbolos::isDeclared(string nombre)
{
     for (unsigned i=0;i<simbolos.size();i++)
       if (simbolos[i].nombre == nombre)
          return true;
     if (padre != NULL)
       return padre->isDeclared(nombre);
     else
       return false;
}

bool TablaSimbolos::set(Simbolo s)
{
     if (isDeclared(s.nombre))  // repetido en cualquier ámbito (Java)
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

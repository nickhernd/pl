#ifndef _TablaTipos_
#define _TablaTipos_

#include <vector>
#include "TablaSimbolos.h"

using namespace std;

const unsigned TIPOBASICO=0,TIPOARRAY=1;



struct unTipo {
  unsigned clase;             // TIPOBASICO o ARRAY
  unsigned tamano;
  unsigned tipoBase;
};

class TablaTipos {

  public:
  
     vector<unTipo> tipos;
     
     TablaTipos();
     unsigned nuevoTipoArray(unsigned tam,unsigned tbase);

};

#endif

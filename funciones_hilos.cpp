#include <iostream>
#include "funciones_hilos.h"

using namespace std;


void* fn_Regulador(void *regulador)
{
    Regulador *reg=static_cast<Regulador*>(regulador);  // Cast para pasar el regulador (Wrap)
    reg->HiloRegulador();
    return nullptr;
}

void* fn_Planta(void *planta)
{
    Planta *pla=static_cast<Planta*>(planta);           // Cast para pasar la planta (Wrap)
    pla->HiloPlanta();
    return nullptr;
}

void *fn_Conversor(void *conversor)
{
    Conversor *con=static_cast<Conversor*>(conversor);  // Cast para pasar el coversor (Wrap)
    con->HiloConversor();
    return nullptr;
}






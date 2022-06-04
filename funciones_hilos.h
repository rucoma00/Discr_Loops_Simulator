#ifndef HILOS_H
#define HILOS_H

#include "regulador.h"
#include "planta.h"
#include "conversor.h"

// Archivos para las funciones de los hilos
// Funciones tienen que servir indistintamente para los dos reguladores y las dos plantas

void* fn_Regulador(void *regulador);
void* fn_Planta(void *planta);
void* fn_Conversor(void *conversor);

#endif // HILOS_H

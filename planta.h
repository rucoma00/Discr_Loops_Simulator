#ifndef PLANTA_H
#define PLANTA_H

#include "fdt.h"
#include <time.h>
#include "config.h"
#include "variablescompartidas.h"
#include <iostream>

class Planta
{
    double T=0;
    FDT *fdt;
    VariablesCompartidas *varcomp;

    // Función para sumar estructuras de tiempo. Devuelve el resultado en t1
    void Suma_timespec(struct timespec *t1, struct timespec *t2);

public:
    Planta(double periodo, FDT *funcion, VariablesCompartidas *var);
    double Calc_yk(double uk);
    double Get_T(void);
    void HiloPlanta();
};

#endif // PLANTA_H

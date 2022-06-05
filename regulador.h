#ifndef REGULADOR_H
#define REGULADOR_H

#include "fdt.h"
#include <time.h>
#include "config.h"
#include "conversor.h"

class Regulador
{
    double T = 0;
    double Kp= 0;
    FDT *fdt;
    Conversor *conversor;
    VariablesCompartidas *varcomp;

    pthread_mutex_t mutKp;

    // Función para sumar estructuras de tiempo. Devuelve el resultado en t1
    void Suma_timespec(struct timespec *t1, struct timespec *t2);

public:
    Regulador(double periodo, double ganancia, FDT *funcion, Conversor *conv, VariablesCompartidas *var);
    double Calc_uk(double ek);
    double Get_Kp(void);
    void Set_Kp(double);
    double Get_T(void);
    void HiloRegulador();
};

#endif // REGULADOR_H

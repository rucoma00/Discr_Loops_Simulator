#ifndef VARIABLESCOMPARTIDAS_H
#define VARIABLESCOMPARTIDAS_H
#include <pthread.h>


class VariablesCompartidas
{
    // Variables compartidas por hilo. Varios hilos usan las mismas varibles (no los mismos valores)
    double r=0;             // Referencia
    double uk=0;
    double yk[5];
    pthread_mutex_t mutV;   // Mutex para proteger las variables compartidas


public:
    VariablesCompartidas(double referencia);
    double Get_r(void);
    double Get_uk(void);
    double Get_yk(int index);

    void Set_r(double referncia);
    void Set_uk(double accion);
    void Set_yk(double salida);
};

#endif // VARIABLESCOMPARTIDAS_H

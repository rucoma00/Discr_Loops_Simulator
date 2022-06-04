#include "planta.h"

using namespace std;

Planta::Planta(double periodo, FDT *funcion, VariablesCompartidas *var)
{
    // Guardar datos
    T=periodo;
    fdt=funcion;
    varcomp=var;
}

double Planta::Calc_yk(double uk)
{
    return fdt->Calc(uk);
}

double Planta::Get_T()
{
    return T;
}

void Planta::Suma_timespec(struct timespec *t1, struct timespec *t2)
{
    t1->tv_nsec += t2->tv_nsec;
    t1->tv_sec += t2->tv_sec;
    while(t1->tv_nsec >= 1e9)   // Si desbordan los nanosegundos
    {
        t1->tv_nsec -= 1e9;     // Reseteo nanosegundos
        t1->tv_sec++;           // Incrementar segundos
    }
}

void Planta::HiloPlanta()
{
    struct timespec t, tperiodo;        // Estructuras para guardar tiempo
    tperiodo.tv_nsec=T*1e9;             // Guardar el tiempo de periodo que siempre es fijo
    tperiodo.tv_sec=0;
    while(tperiodo.tv_nsec >= 1e9)      // Si desbordan los nanosegundos
    {
        tperiodo.tv_nsec -= 1e9;        // Reseteo nanosegundos
        tperiodo.tv_sec++;              // Incrementar segundos
    }

    while(1)    // Bucle de ejecución continua
    {                                                   // Tarea periodica pura:
        clock_gettime(CLOCK_REALTIME,&t);               // 1)   Captura de tiempo actual
        Suma_timespec(&t,&tperiodo);                    // 2)   Suma al tiempo actual un periodo fijo
        varcomp->Set_yk(Calc_yk(varcomp->Get_uk()));    // 3)   Hacer cálculos. Calcualar yk a partit de uk y guardarla
        if(T == PERIODO_PLANTA_MOTOR)                   //      Comprobación de en que sistema está
            cout<<varcomp->Get_yk(0)<<endl;             //      Salida por pantalla a la izquierda si es el motor
        else
            cout<<"\t\t"<<varcomp->Get_yk(0)<<endl;     //      Salida por pantalla a la derecha si es el crucero
        clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME,&t,NULL); // 4)   Hacer retardo. De esta forma queda retardo absoluto
    }
}

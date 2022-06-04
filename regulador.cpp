#include "regulador.h"

Regulador::Regulador(double periodo, double ganancia, FDT *funcion, Conversor *conv, VariablesCompartidas *var)
{
    // Guardar datos
    T=periodo;
    Kp=ganancia;
    fdt=funcion;
    conversor=conv;
    varcomp=var;
}

double Regulador::Calc_uk(double ek)
{
    return Kp*fdt->Calc(ek);   // Kp se modifica por pantalla, proteger
}

double Regulador::Get_Kp()
{
    return Kp;
}

void Regulador::Set_Kp(double ganancia)
{
    Kp=ganancia;
}

double Regulador::Get_T()
{
    return T;
}

void Regulador::Suma_timespec(struct timespec *t1, struct timespec *t2)
{
    t1->tv_nsec += t2->tv_nsec;
    t1->tv_sec += t2->tv_sec;
    while(t1->tv_nsec >= 1e9)   // Si desbordan los nanosegundos
    {
        t1->tv_nsec -= 1e9;     // Reseteo nanosegundos
        t1->tv_sec++;           // Incrementar segundos
    }
}

void Regulador::HiloRegulador()
{
    struct timespec t, tperiodo;    // Estructuras para guardar tiempo
    int DR;                         // Registro de datos que se obtiene del conversor
    double yk;                      // Valor de la salida real
    tperiodo.tv_nsec=T*1e9;         // Guardar el tiempo de periodo que siempre es fijo
    tperiodo.tv_sec=0;
    while(tperiodo.tv_nsec >= 1e9)  // Si desbordan los nanosegundos
    {
        tperiodo.tv_nsec -= 1e9;    // Reseteo nanosegundos
        tperiodo.tv_sec++;          // Incrementar segundos
    }

    while(1)    // Bucle de ejecución continua.
    {                                           // Tarea periodica pura:
        clock_gettime(CLOCK_REALTIME,&t);       // 1)   Captura de tiempo actual
        Suma_timespec(&t,&tperiodo);            // 2)   Suma al tiempo actual un periodo fijo
        if(T==PERIODO_REGULADOR_MOTOR)          //      Comprobar si se trata del Reg. motor o Reg. crucero
        {
            conversor->Read(CH_MOTOR, &DR);     // 3)   Leer del conversor canal motor
                                                // Cambiar la decodificación para complemento a 2
            yk = (DR*(conversor->Get_Vmax()-conversor->Get_Vmin())/pow(2,conversor->Get_Resolucion()))
                    /(conversor->s_ch0->Get_Ganancia()*conversor->s_ch0->Get_Ratio());
            double ek = varcomp->Get_r() - yk;  // Obtener referencia y calcular ek
            varcomp->Set_uk(Calc_uk(ek));       // Calcular uk a partir de ek y guardar
        }
        else
        {
            conversor->Read(CH_CRUCERO, &DR);   //      Leer del conversor canal crucero
            yk = (DR*(conversor->Get_Vmax()-conversor->Get_Vmin())/pow(2,conversor->Get_Resolucion()))
                    /(conversor->s_ch1->Get_Ganancia()*conversor->s_ch1->Get_Ratio());
            double ek = varcomp->Get_r() - yk;  // Obtener referencia y calcular ek
            varcomp->Set_uk(Calc_uk(ek));       // Calcular uk a partir de ek y guardar
        }
        // 4)   Hacer retardo. De esta forma queda retardo absoluto
        clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME,&t,NULL);
    }
}

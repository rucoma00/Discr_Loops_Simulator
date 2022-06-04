#include "conversor.h"

Conversor::Conversor(double minVolt, double maxVolt, int resolucion, Sensor *s0, Sensor *s1,  VariablesCompartidas *varM, VariablesCompartidas *varC)
{
    Vmin=minVolt;
    Vmax=maxVolt;
    res=resolucion;
    s_ch0=s0;
    s_ch1=s1;
    csr={0,0,0,0,0};
    varMot=varM;
    varCru=varC;
    pthread_mutex_init(&mutConv, NULL);
    pthread_mutex_init(&mutRead, NULL);
    pthread_cond_init(&convDone, NULL);
    pthread_cond_init(&convStart, NULL);
}

void Conversor::Read(int Ncanal, int *datareg)
{
    pthread_mutex_lock(&mutRead);   // Cerrar mutex de lectura por si entrara el otro regulador
    csr.ERROR=0;                    // Poner el error a 0
    csr.IE=1;                       // Habilitar interrupción
    csr.DONE=0;                     // Done a 0
    csr.CANAL=Ncanal;               // Seleccion de canal
    csr.START=1;                    // Inicio de conversión

    pthread_cond_signal(&convStart);            // Señalar variable de condición start para que de paso al hilo conversor
    pthread_mutex_lock(&mutConv);
    while(csr.DONE==0)                          // Mientras no a acabado, espra a que se señale la variable
        pthread_cond_wait(&convDone,&mutConv);  // de condición done y libera el mutex de conversor
    *datareg=DR;                                // Guardar el valor del registro de datos cuando ha acabdo
    pthread_mutex_unlock(&mutConv);
    pthread_mutex_unlock(&mutRead);             // Liberar el mutex de lectura
}

double Conversor::Get_Vmax()
{
    return Vmax;
}

double Conversor::Get_Vmin()
{
    return Vmin;
}

int Conversor::Get_Resolucion()
{
    return res;
}

void Conversor::HiloConversor()
{
    while(1)
    {
        pthread_mutex_lock(&mutConv);       // Cierra el mutex del hilo conversor
        while(csr.START==0)                 // Espera a que se le indique que hay que convertir
            pthread_cond_wait(&convStart, &mutConv);
        // Guardar valor de la salida en el Data Register
        if(csr.CANAL==CH_MOTOR)             // Cambiar codificación para complemento a 2
            DR=(s_ch0->Calc_Tension(varMot->Get_yk(0)))*(pow(2,res)/(Vmax-Vmin));
        else
            DR=(s_ch1->Calc_Tension(varCru->Get_yk(0)))*(pow(2,res)/(Vmax-Vmin));
        csr.START=0;    // Resetar start
        csr.DONE=1;     // Indicar en CSR que ha acabado
        pthread_cond_signal(&convDone);     // Señal de que hay nuevo valor. Ha acabdo la conversión
        pthread_mutex_unlock(&mutConv);     // Liberar el mutex de conversión
    }
}

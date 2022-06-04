#include "variablescompartidas.h"

VariablesCompartidas::VariablesCompartidas(double referencia)
{
    r=referencia;
    uk=0;
    pthread_mutex_init(&mutV,NULL);
    for(int i=0;i<5;i++)
        yk[i]=0;        // Inicializar salidas a 0
}

double VariablesCompartidas::Get_r(void)
{
    double referencia;
    pthread_mutex_lock(&mutV);
    referencia=r;
    pthread_mutex_unlock(&mutV);
    return referencia;
}
double VariablesCompartidas::Get_uk(void)
{
    double accion;
    pthread_mutex_lock(&mutV);
    accion=uk;
    pthread_mutex_unlock(&mutV);
    return accion;
}
double VariablesCompartidas::Get_yk(int index)
{
    double salida;
    pthread_mutex_lock(&mutV);
    salida=yk[index];
    pthread_mutex_unlock(&mutV);
    return salida;
}


void VariablesCompartidas::Set_r(double referncia)
{
    pthread_mutex_lock(&mutV);
    r=referncia;
    pthread_mutex_unlock(&mutV);
}
void VariablesCompartidas::Set_uk(double accion)
{
    pthread_mutex_lock(&mutV);
    uk=accion;
    pthread_mutex_unlock(&mutV);
}
void VariablesCompartidas::Set_yk(double salida)
{
    pthread_mutex_lock(&mutV);
    for(int i=4;i>0;i--)
        yk[i]=yk[i-1];  // Desplazar valores
    yk[0]=salida;
    pthread_mutex_unlock(&mutV);
}


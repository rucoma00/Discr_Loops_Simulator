#ifndef CONVERSOR_H
#define CONVERSOR_H

#include <stdint.h>
#include <pthread.h>
#include <math.h>

#include "sensor.h"
#include "variablescompartidas.h"
#include "config.h"


// Estructura para registro CSR. Campo de bits
typedef struct
{
    uint8_t ERROR:  2,
            IE:     1,
            DONE:   1,
            CANAL:  2,
            :       1,  // Sin usar
            START:  1;
}CSR;

class Conversor
{
    double Vmax, Vmin;  // Rango de tensiones de entrada
    int res;            // Resolución
    int DR;             // Data Register (12 bits)
    int ch;             // Canal a convertir
    CSR csr;
    // Mutex de Lectura: Protege a la función read de la llamada desde los reguladores
    // Mutex de Conversor: Protege los registros del conversor
    pthread_mutex_t mutRead, mutConv;   // Mutex de lectura y mutex de conversion
    pthread_cond_t convStart, convDone; // Condicición de start y condición de done
    VariablesCompartidas *varMot;
    VariablesCompartidas *varCru;

public:
    Sensor *s_ch0;      // Sensor del canal 0 (Motor)
    Sensor *s_ch1;      // Sensor del canal 1 (Crucero)
    Conversor(double minVolt, double maxVolt, int resolucion, Sensor *s0, Sensor *s1, VariablesCompartidas *varM, VariablesCompartidas *varC);
    void Read(int Ncanal, int *datareg);
    double Get_Vmax();
    double Get_Vmin();
    int Get_Resolucion();
    void HiloConversor();
};

#endif // CONVERSOR_H

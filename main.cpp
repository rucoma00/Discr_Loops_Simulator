#include "mainwindow.h"

#include <QApplication>

#include <iostream>
#include <pthread.h>

#include "planta.h"
#include "regulador.h"
#include "config.h"
#include "funciones_hilos.h"
#include "variablescompartidas.h"

using namespace std;

#if defined (SISTEMA_COMPLETO) && defined (LAZO_MOTOR)
    #error Configuracion incompatible
#endif

#if defined (SISTEMA_COMPLETO) && defined (LAZO_CRUCERO)
    #error Configuracion incompatible
#endif

#if defined (LAZO_CRUCERO) && defined (LAZO_MOTOR)
    #error Configuracion incompatible
#endif


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Sensores
    Sensor sMot(GANANCIA_SENSOR, RATIO_SENSOR);
    Sensor sCru(GANANCIA_SENSOR, RATIO_SENSOR);

    // Variables compartidas de cada sistema
    VariablesCompartidas varMot(REFERENCIA_INIT);
    VariablesCompartidas varCru(REFERENCIA_INIT);

    // Conversor
    Conversor conv(VMIN_CONVERSOR, VMAX_CONVERSOR,RESOLUCION_CONVERSOR, &sMot, &sCru, &varMot, &varCru);

    // Funciones de transferencia
    double N_regMot[]={414.1, -647.8, 250.1, 0};    // Numerador regulador motor
    double D_regMot[]={1, 0.82,-1, -0.82};          // Denominador regulador motor
    FDT FDT_regMot(N_regMot, D_regMot, 4, 4);       // Función de transferencia del regulador motor

    Regulador regMot(PERIODO_REGULADOR_MOTOR, KP_INIT_REGULADOR_MOTOR, &FDT_regMot, &conv, &varMot);

    double N_plaMot[]={0, 0.0005663, 0.0005125};    // Numerador planta motor
    double D_plaMot[]={1, -1.73, 0.7408};           // Denominador planta motor
    FDT FDT_plaMot(N_plaMot, D_plaMot, 3, 3);       // Función de transferencia de la planta motor

    Planta plaMot(PERIODO_PLANTA_MOTOR, &FDT_plaMot, &varMot);

    double N_regCru[]={489.08, -488.5918, 0};       // Numerador regulador crucero
    double D_regCru[]={1, -0.9998};                 // Denominador regulador crucero
    FDT FDT_regCru(N_regCru, D_regCru, 3, 2);       // Función de transferencia del regulador crucero

    Regulador regCru(PERIODO_REGULADOR_CRUCERO, KP_INIT_REGULADOR_CRUCERO, &FDT_regCru, &conv, &varCru);

    double N_plaCru[]={0, 9.998e-6};                // Numerador planta crucero
    double D_plaCru[]={1, -0.9995};                 // Denominador planta crucero
    FDT FDT_plaCru(N_plaCru,D_plaCru ,2 ,2);        // Función de transferencia de la planta crucero

    Planta plaCru(PERIODO_PLANTA_CRUCERO, &FDT_plaCru, &varCru);

    // Creación de hilos
    pthread_t h_plaMot, h_regMot, h_plaCru, h_regCru, h_conver;                           // Identificadores de hilo

    #ifdef SISTEMA_COMPLETO     // Se ejecutan los dos lazos de control
    pthread_create(&h_regMot, NULL, fn_Regulador, static_cast<void*>(&regMot)); // Hilo regulador motor
    pthread_create(&h_plaMot, NULL, fn_Planta, static_cast<void*>(&plaMot));    // Hilo planta motor
    pthread_create(&h_regCru, NULL, fn_Regulador, static_cast<void*>(&regCru)); // Hilo regulador crucero
    pthread_create(&h_plaCru, NULL, fn_Planta, static_cast<void*>(&plaCru));    // Hilo planta crucero
    pthread_create(&h_conver, NULL, fn_Conversor, static_cast<void*>(&conv));   // Hilo conversor

    // Finalización
//    pthread_join(h_regMot,NULL);
//    pthread_join(h_plaMot,NULL);
//    pthread_join(h_regCru,NULL);
//    pthread_join(h_plaCru,NULL);
//    pthread_join(h_conver,NULL);
    #endif

    #ifdef LAZO_MOTOR   // Solo se ejecuta el lazo motor
    pthread_create(&h_regMot, NULL, fn_Regulador, static_cast<void*>(&regMot)); // Hilo regulador motor
    pthread_create(&h_plaMot, NULL, fn_Planta, static_cast<void*>(&plaMot));    // Hilo planta motor
    pthread_create(&h_conver, NULL, fn_Conversor, static_cast<void*>(&conv));  // Hilo converso

    // Finalización
    pthread_join(h_regMot,NULL);
    pthread_join(h_plaMot,NULL);
    pthread_join(h_conver,NULL);
    #endif

    #ifdef LAZO_CRUCERO // Solo se ejecuta el lazo crucero
    pthread_create(&h_regCru, NULL, fn_Regulador, static_cast<void*>(&regCru)); // Hilo regulador crucero
    pthread_create(&h_plaCru, NULL, fn_Planta, static_cast<void*>(&plaCru));    // Hilo planta crucero
    pthread_create(&h_conver, NULL, fn_Conversor, static_cast<void*>(&conv));  // Hilo converso

    // Finalización
    pthread_join(h_regCru,NULL);
    pthread_join(h_plaCru,NULL);
    pthread_join(h_conver,NULL);
    #endif

    MainWindow w(nullptr, &regMot, &regCru, &varMot, &varCru);
    w.show();
    return a.exec();
}

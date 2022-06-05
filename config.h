#ifndef CONFIG_H
#define CONFIG_H

// Macros para los datos de las funciones de transferencia
// Sistema motor
#define PERIODO_REGULADOR_MOTOR 0.05    // s
#define KP_INIT_REGULADOR_MOTOR 0.1
#define PERIODO_PLANTA_MOTOR 0.025      // s
#define CH_MOTOR 0

// Sistema crucero
#define PERIODO_REGULADOR_CRUCERO 0.02  // s
#define KP_INIT_REGULADOR_CRUCERO 1
#define PERIODO_PLANTA_CRUCERO 0.01     // s
#define CH_CRUCERO 1

#define REFERENCIA_INIT 1
#define REFERENCIA_MAX 10
#define REFERENCIA_MIN 0
#define KP_MAX 10
#define KP_MIN 0

// Sensores
#define GANANCIA_SENSOR 500
#define RATIO_SENSOR 0.001

// Conversor
#define VMAX_CONVERSOR 10
#define VMIN_CONVERSOR -10
#define RESOLUCION_CONVERSOR 12


// Configuraciones para pruebas. Descomentar solo una
#define SISTEMA_COMPLETO
//#define LAZO_MOTOR
//#define LAZO_CRUCERO

// Para ver la salidas en el terminal
//#define COUT_TERMINAL

#endif // CONFIG_H

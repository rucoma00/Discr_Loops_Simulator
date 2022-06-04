#ifndef FDT_H
#define FDT_H

class FDT
{   //Campos privados
    int gradoNum = 0;           // Grado polinomio numerador
    int gradoDen = 0;           // Grado polinomio denominador
    double *coefNum=nullptr;    // Array coeficientes polinomio numerador
    double *coefDen=nullptr;    // Array coeficientes polinomio denominador
    double *xk=nullptr;         // Entrada de la FDT
    double *yk=nullptr;         // Salida de la FDT

    // Métodos privados
    double ProductoEscalar(double*,double*,int);    // Producto esclalar de dos arrays
    void  Desplazar();                              // Desplaza los arrays de entrada y salida una posición de forma que valor[i] = valor[i-1]

public: // Métodos públicos
    FDT(double* numerador,double* denominador,int nNum,int nDen);   // Constructor
    ~FDT();                                                         // Destructor
    double Calc(double in); // Función para obtener la salida de la FDT en función de la entrada
};

#endif // FDT_H

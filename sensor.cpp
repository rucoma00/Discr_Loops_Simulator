#include "sensor.h"

Sensor::Sensor(double ganancia, double r)
{
    G=ganancia;
    ratio=r;
}

double Sensor::Calc_Tension(double valor)
{
    double V;
    V=valor*ratio;
    return V*G;
}

double Sensor::Get_Ganancia()
{
    return G;
}

double Sensor::Get_Ratio()
{
    return ratio;
}

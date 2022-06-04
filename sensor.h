#ifndef SENSOR_H
#define SENSOR_H


class Sensor
{
    double G;       // Ganancia del sensor
    double ratio;   // Relación entre tensión y velocidad: mV/(rad/s)
public:
    Sensor(double ganancia, double r);
    double Calc_Tension(double valor);
    double Get_Ganancia();
    double Get_Ratio();
};

#endif // SENSOR_H

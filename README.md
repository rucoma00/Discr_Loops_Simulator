# Discreete Control Loops Simulator
This project implements the control of two systems: ***Motor Speed Control*** and ***Cruise Control***, and allows the user to tune some parameters and visualize different outputs thanks to a custom GUI. It is archieved thanks to three concurrent actions, two discrete control loops and a supervision task.

## Control loops general description.
Two discrete control loops are implemented. In each of them, two threads corresponding to the ***Regulator (R)*** and ***Plant (G)*** are executed in a cyclic manner. Each control loop has a different period: 50 ms for the ***Motor Speed Control*** and 20 ms for the ***Cruise Control***. 

The ***Motor Speed Control (T = 50 ms)*** is implemented by the following equations:

```math
R_{Motor}=Kp\times \frac{414.1z^2-647.8z+250.1}{z^3+0.82z^2-z-0.82}
```
```math
G_{Motor}=\frac{0.0005663z+0.0005125}{z^2-1.73z+0.7408}
```

The ***Cruise Control (T = 20 ms)*** is implemented by the following equations:

```math
R_{Cruise}=Kp\times \frac{414.1z^2-647.8z+250.1}{z^3+0.82z^2-z-0.82}
```
```math
G_{Cruise}=\frac{0.0005663z+0.0005125}{z^2-1.73z+0.7408}
```

The inputs to this systems are always considered to be *steps*. Their amplitude can be modifyed in the GUI. 

## Control loops threads.
There is no alternating between the execution of the threads in each control loop. Eaxh of them activates according to its period and will work with the available data at the time. The following sequence of threads happens inside each control loop:

### Regulator thread.
It is held inside the class ***Regulator***.
1. The thread executes method ```Read( int channel, int *datareg)``` from the class [**Conversor**](#conversor). This is a function that simulates the capture of an analog signal and its conversion to a discrete value, giving ***Yk***, the last value of the control loop output.
2. The error is calculated and stored as a field of the class ***Variables Compartidas*** ( Shared Variables). These are the variables shared betwween plant and regulator:
```math
E_k=Y_k-ref 
```
3. The regulator thread stops executing until its next activation period.

### Plant thread
It is held inside the class ***Plant***.
1. The corresponding plant takes the shared variable ***Uk*** (output of the regulator, control action) and generates a new ***Yk*** (also a shared variable). This task is two times faster than its regulator.
2. The plant thread stops executing until its next activation period.

## Sensor simulation
The ***Sensor*** class provides a voltage value to an angular velocity. ***Yk*** is only known by the system after passing through the **sensor** and the [**conversor**](#conversor). The following table describes sensor specifications:
| Gain | Ratio [mV/(rad/s)] |
| ---- | ------------------ |
| 500 | 1 |

## Conversor
It is a simulated **ADC** thread (includin the sensor in the thread) with two hardware registers: ***CSR*** (Control State Register, 8 bit) and ***DR*** (Data Register). It works between -10 and +10 V with 12 bit resolution. ***CSR*** is detailed in the following table:
| Function | Bit(s) |
| -------- | ------ |
| ERROR | [0, 1] |
| IE | 2 |
| DONE | 3 |
| CH | [4, 5] |
| - | 6 |
| START | 7 |

The function ```Read( int channel, int *datareg)``` uses the channel (0 for Motor, 1 for Cruise) and the memory location where the 12 bit int that has just been read will be stored. There is only one ***Conversor***, therefore only one ***Regulator*** can use this method at a time. Before executing the operation, ***CSR*** must be in initial conditions: 

```
csr.ERROR=0;                    // Poner el error a 0
csr.IE=1;                       // Habilitar interrupción
csr.DONE=0;                     // Done a 0
csr.CANAL=Ncanal;               // Seleccion de canal
csr.START=1;                    // Inicio de conversión
```
## GUI
The graphic interface shows for each control loop:
- Last 5 output values (***Yk***) with a button to refresh them.
- Reference adjustemnt slider.
- Box to modify regulator's gain (***Kp***) value.
- Exit button.
- A graph showing the system's output against the reference.

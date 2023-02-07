# trabajo-tiempo-real-interfaz
This project implements the control of two systems: ***Motor Speed Control*** and ***Cruise Control***, and allows the user to tune some parameters and visualize different outputs thanks to a custom GUI. It is archieved thanks to three concurrent actions, two discrete control loops and a supervision task.

## Control loops description
Two discrete control loops are implemented. In each of them, two threads corresponding to the ***Regulator (R)*** and ***Plant (G)*** are executed in a cyclic manner. Each control loop has a different period: 50 ms for the ***Motor Speed Control*** and 20 ms for the ***Cruise Control***. 

```math
R_{Motor}=\frac{414.1z^2-647.8z+250.1}{z^3+0.82z^2-z-0.82}
```
```math
G_{Motor}=\frac{0.0005663z+0.0005125}{z^2-1.73z+0.7408}
```

```math
R_{Cruise}=\frac{414.1z^2-647.8z+250.1}{z^3+0.82z^2-z-0.82}
```
```math
G_{Cruise}=\frac{0.0005663z+0.0005125}{z^2-1.73z+0.7408}
```

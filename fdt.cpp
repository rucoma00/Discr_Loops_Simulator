#include "fdt.h"

double FDT::ProductoEscalar(double* arr1, double* arr2, int N)
{
    double res=0;
    for(int i=0;i<N;i++)
        res+=arr1[i]*arr2[i];
    return res;
}

void FDT::Desplazar()
{
    for(int i=gradoNum;i>0;i--)
        xk[i]=xk[i-1];
    for(int i=gradoDen;i>0;i--)
        yk[i]=yk[i-1];
}

FDT::FDT(double* numerador,double* denominador,int nNum,int nDen)
{
    gradoNum=nNum-1;
    gradoDen=nDen-1;
    coefNum=new double[nNum];
    yk=new double[nNum];
    coefDen=new double[nDen];
    xk=new double[nDen];

    for(int i=0;i<nNum;i++){
        coefNum[i]=numerador[i];
        yk[i]=0;
    }
    for(int i=0;i<nDen;i++){
        coefDen[i]=denominador[i];
        xk[i]=0;
    }
}

FDT::~FDT(){
    delete [] coefNum;
    delete [] coefDen;
    delete [] xk;
    delete [] yk;
}

double FDT::Calc(double in){
    Desplazar();
    xk[0]=in;
    yk[0]=(ProductoEscalar(coefNum,xk,gradoNum+1)-ProductoEscalar(coefDen+1,yk+1,gradoDen))/coefDen[0];
    return yk[0];
}

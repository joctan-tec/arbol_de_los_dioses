#ifndef _DIOS_
#define _DIOS_ 1
#include <iostream>
#include <string>
using namespace std;

class Dios
{
private:
    
    int fieles;
    string nombre;

public:

    Dios (int fieles, string nombre){
    }

    int getFieles(){
        
        return fieles;

    }

    string getNombre(){
        return nombre;
    }

    void setFieles(int numFieles){
        fieles=numFieles;
    }

    void setNombre(string nombreDios){
        nombre = nombreDios;
    }

    Dios cartaMilagro(Dios perdedor){
        int fielesPerdedor = perdedor.getFieles();
        int veintePorciento = 20*100 / fielesPerdedor;

        fieles+=veintePorciento;
        perdedor.setFieles(perdedor.getFieles()-veintePorciento);
        return perdedor;
    }


    
};

#endif
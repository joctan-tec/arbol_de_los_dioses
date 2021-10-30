#ifndef _DIOS_
#define _DIOS_ 1
#include <iostream>
#include <string>
using namespace std;

class Dios {

private:
    

public:

    int fieles;
    string nombre;

    Dios (int numFieles, string nombreDios){
        fieles = numFieles;
        nombre = nombreDios;

    }

    int getFieles(){
        
        return fieles;

    }

    string getNombre(){
        return nombre;
    }

    void sumarFieles(int numFieles){
        fieles+=numFieles;
    }

    void setFieles(int numFieles){
        fieles = numFieles;
    }

    void setNombre(string nombreDios){
        nombre = nombreDios;
    }

    Dios cartaMilagro(Dios perdedor){
        int fielesPerdedor = perdedor.getFieles();
        
        int veintePorciento = fielesPerdedor*0.2;
        

        fieles+=veintePorciento;
        perdedor.sumarFieles(veintePorciento*-1);
        
        return perdedor;
    }


    Dios cartaTraicion(Dios ganador){
        int treintaPorciento = fieles*0.3;
        

        fieles-=treintaPorciento;
        ganador.sumarFieles(treintaPorciento);
        
        return ganador;
    }


    Dios cartaNuevoDios(Dios pDiosB){
        return Dios(pDiosB.getFieles()+fieles,"Hijo de "+pDiosB.getNombre()+" y "+nombre);
    }


    void cartaMuerte(){
        fieles-=fieles*0.1;
    }




    


    
};

#endif
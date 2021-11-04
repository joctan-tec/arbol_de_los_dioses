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
};

#endif
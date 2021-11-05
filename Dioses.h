#ifndef _DIOS_
#define _DIOS_ 1
#include <iostream>
#include <string>
using namespace std;

class Dios {
    private:
    
    public:
        //se manejan publicos por motivos de la impresion en el postOrden del arbol
        int fieles;
        string nombre;

        Dios (int pNumFieles, string pNombreDios){
            fieles = pNumFieles;
            nombre = pNombreDios;
        }

        int getFieles(){
            return fieles;
        }

        string getNombre(){
            return nombre;
        }

        void sumarFieles(int pNumFieles){
            fieles+=pNumFieles;
        }

        void setFieles(int pNumFieles){
            fieles = pNumFieles;
        }

        void setNombre(string pNombreDios){
            nombre = pNombreDios;
        }
};

#endif
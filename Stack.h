#include "stack"
#include "Dioses.h"
#include "Cartas.h"
#include "random"
using namespace std;

class Stack
{
private:
    stack <Cartas> cartas;
    int cartasMilagro=0;
    int cartasTraicion=0;
    int cartasNuevoDios=0;
    int cartasMuerte=0;
public:

    Stack (bool estado){
        while (cartasMilagro < 5 | cartasTraicion < 4 | cartasNuevoDios < 4
               | cartasMuerte < 10)
        {
            int numeroRandom = rand()%4+1;
            if (numeroRandom==1){
                Cartas carta1(1);
                cartas.push(carta1);
                ++cartasMilagro;
            }else if (numeroRandom==2){
                Cartas carta2(2);
                cartas.push(carta2);
                ++cartasTraicion;
            }else if(numeroRandom==3){
                Cartas carta3(5);
                cartas.push(carta3);
                ++cartasNuevoDios;
            }else if (numeroRandom==4){
                Cartas carta4(7);
                cartas.push(carta4);
                ++cartasMuerte;
            }
                
            
            // switch (numeroRandom)
            // {
            // case 1:
            //     Cartas carta1(1);
            //     cartas.push(carta1);
            //     ++cartasMilagro;
            //     break;
            // case 2:
            //     Cartas carta2(2);
            //     cartas.push(carta2);
            //     ++cartasTraicion;
            //     break;
            // case 3:
            //     Cartas carta3(5);
            //     cartas.push(carta3);
            //     ++cartasNuevoDios;
            //     break;
            // case 4:              
            //     Cartas carta4(7);
            //     cartas.push(carta4);
            //     ++cartasMuerte;
            //     break;
            // }
        
        }
    }
    Stack (int num){

    }


    Cartas obtenerCarta(){
        Cartas primerCarta = cartas.top();
        cartas.pop();
        return primerCarta;
    }

    void agregarCarta(Cartas carta){
        cartas.push(carta);
    }



};


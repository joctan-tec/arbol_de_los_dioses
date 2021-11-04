#ifndef _STACK_CARTAS_ 
#define _STACK_CARTAS_ 1

#include "Cartas.h"


#include "stack" 
#include "random"
#include "vector"
#include "algorithm"


using namespace std;

class Stack {

private:
    stack <Cartas> cartas;
    int cartasMilagro=0;
    int cartasTraicion=0;
    int cartasNuevoDios=0;
    int cartasMuerte=0;
    int cartasRetorno =0;
    int cartasUnion=0;
    int cartasAnarquia=0;

public:

    Stack (bool estado){
        while (true)
        {
            int numeroRandom = rand()%7+1;
            if (cartasMilagro < 5 & numeroRandom==1){
                Cartas carta1(1);
                cartas.push(carta1);
                cartasMilagro++;
            }else if (cartasTraicion < 4 & numeroRandom==2){
                Cartas carta2(2);
                cartas.push(carta2);
                cartasTraicion++;
            }else if(cartasNuevoDios < 4 &&numeroRandom==3){
                Cartas carta3(5);
                cartas.push(carta3);
                cartasNuevoDios++;
            }else if (cartasMuerte < 10 &numeroRandom==4){
                Cartas carta4(7);
                cartas.push(carta4);
                cartasMuerte++;
            }else if(cartasRetorno < 6 &numeroRandom==5){
                Cartas carta5(6);
                cartas.push(carta5);
                cartasRetorno++;
            }else if(cartasAnarquia < 7 & numeroRandom==6){
                Cartas carta6(3);
                cartas.push(carta6);
                cartasAnarquia++;
            }else if(cartasUnion < 4 & numeroRandom==7){
                Cartas carta7(4);
                cartas.push(carta7);
                cartasUnion++;
            }


            if((cartasAnarquia+cartasMilagro+cartasMuerte+cartasRetorno+cartasNuevoDios+cartasTraicion+
                cartasUnion)==40){
                break;
            }

            
        
        }
    }
    Stack (int num){

    }

    Stack mezclarCartas(Stack* pilaParaMezclar){
        vector<Cartas> cartasAleatorias;

        for (;!pilaParaMezclar->esVacia();){
            cartasAleatorias.push_back(pilaParaMezclar->obtenerCarta());
        }

        random_device random;
        default_random_engine rng(random());
        shuffle(cartasAleatorias.begin(),cartasAleatorias.end(),rng);


        Stack pilaCambio(1);
        for (int indiceVector=0;indiceVector<40;indiceVector++)
        {
            pilaCambio.agregarCarta(cartasAleatorias[indiceVector]);
        }
        return pilaCambio;
    }


    void rellenarPila(Stack* pilaReserva){
        Stack pilaIntermedia(1);
        pilaIntermedia = pilaReserva->mezclarCartas(pilaReserva);
        for (;!pilaIntermedia.esVacia();)
        {
            cartas.push(pilaIntermedia.obtenerCarta());
        }

    }


    Cartas obtenerCarta(){
        Cartas primerCarta = cartas.top();
        cartas.pop();
        return primerCarta;
    }

    void agregarCarta(Cartas carta){
        cartas.push(carta);
    }

    bool esVacia(){
        return cartas.empty();
    }

    void desplegarCartas(){
        for (int i=1;!cartas.empty();i++){
            Cartas actual = cartas.top();
            cout<<i<<". "+actual.getTipoString()<<endl;
            cartas.pop();
        }
    }

    string regresaCartas(Stack* pilaReserva){
        string cartasRegresadas= "Regresamos una carta de: ";
        for(int contadorCartas=0;!pilaReserva->esVacia()&contadorCartas<3;contadorCartas++){
            cartas.push(pilaReserva->obtenerCarta());
            cartasRegresadas+=cartas.top().getTipoString()+" - "; 
        }
        return cartasRegresadas;
    }



};

#endif
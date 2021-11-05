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

        Stack (bool pEstado){
            //crea el stack con las cartas
            while (true)
            {
                int numeroRandom = rand() % 7+1;
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


                if((cartasAnarquia + cartasMilagro + cartasMuerte + cartasRetorno + cartasNuevoDios + cartasTraicion + cartasUnion)==40){
                    break;
                }
            }
        }
        Stack (int num){
            //crea un stack vacio
        }

        Stack mezclarCartas(Stack* pPilaParaMezclar){
            vector<Cartas> cartasAleatorias;

            for (;!pPilaParaMezclar->esVacia();){
                cartasAleatorias.push_back(pPilaParaMezclar->obtenerCarta());
            }

            random_device random;
            default_random_engine rng(random());
            shuffle(cartasAleatorias.begin(),cartasAleatorias.end(),rng);


            Stack pilaCambio(1);
            for (int indiceVector = 0; indiceVector < 40; indiceVector++)
            {
                pilaCambio.agregarCarta(cartasAleatorias[indiceVector]);
            }
            return pilaCambio;
        }


        void rellenarPila(Stack* pPilaReserva){
            Stack pilaIntermedia(1);
            pilaIntermedia = pPilaReserva->mezclarCartas(pPilaReserva);
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

        void agregarCarta(Cartas pCarta){
            cartas.push(pCarta);
        }

        bool esVacia(){
            return cartas.empty();
        }

        void desplegarCartas(){
            for (int carta = 1; !cartas.empty() ; carta++){
                Cartas actual = cartas.top();
                cout<< carta << ". " + actual.getTipoString() << endl;
                cartas.pop();
            }
        }

        string regresaCartas(Stack* pPilaReserva){
            string cartasRegresadas = "Regresamos una carta de: ";
            for(int contadorCartas = 0; !pPilaReserva->esVacia() & contadorCartas<3 ;contadorCartas++){
                cartas.push( pPilaReserva->obtenerCarta() );
                cartasRegresadas += cartas.top().getTipoString() + " - ";
            }
            return cartasRegresadas;
        }



};

#endif
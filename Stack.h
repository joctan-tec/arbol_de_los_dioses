#include "Dioses.h"
#include "stack"
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
    int cartasRetorno =0;
    int cartasTotales = 0;
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
                cartasTotales++;
                cout<<carta1.getTipoString() <<":::"<<cartasMilagro<<endl;
                
            }else if (cartasTraicion < 4 & numeroRandom==2){
                Cartas carta2(2);
                cartas.push(carta2);
                cartasTraicion++;
                cartasTotales++;
                cout<<carta2.getTipoString() <<":::"<<cartasTraicion<<endl;
            }else if(numeroRandom==3){
                Cartas carta3(5);
                cartas.push(carta3);
                cartasNuevoDios++;
                cartasTotales++;
                cout<<carta3.getTipoString() <<":::"<<cartasNuevoDios<<endl;
            }else if (cartasMuerte < 10 &numeroRandom==4){
                Cartas carta4(7);
                cartas.push(carta4);
                cartasTotales++;
                cartasMuerte++;
                cout<<carta4.getTipoString() <<":::"<<cartasMuerte<<endl;
            }else if(cartasRetorno < 6 &numeroRandom==5){
                Cartas carta5(6);
                cartas.push(carta5);
                cartasTotales++;
                cartasRetorno++;
                cout<<carta5.getTipoString() <<":::"<<cartasRetorno<<endl;
            }else if(cartasAnarquia < 7 & numeroRandom==6){
                Cartas carta6(3);
                cartas.push(carta6);
                cartasTotales++;
                cartasAnarquia++;
                cout<<carta6.getTipoString() <<":::"<<cartasAnarquia<<endl;
            }else if(cartasUnion < 4 & numeroRandom==7){
                Cartas carta7(4);
                cartas.push(carta7);
                cartasTotales++;
                cartasUnion++;
                cout<<carta7.getTipoString() <<":::"<<cartasUnion<<endl;
            }


            if((cartasAnarquia+cartasMilagro+cartasMuerte+cartasRetorno+cartasNuevoDios+cartasTraicion+
                cartasUnion)==40){
                break;
            }

            
        
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

    void regresaCartas(Stack* pilaReserva){
        stack <Cartas> pilaIntermedia;
        for(int contadorCartas;!pilaReserva->esVacia()&&contadorCartas<3;contadorCartas++){
            Cartas cartaTop = pilaReserva->obtenerCarta();
            pilaIntermedia.push(cartaTop);
        }


        for(;pilaIntermedia.size();){
            cartas.push(pilaIntermedia.top());
            cout<<"Regresamos una carta de: "<<pilaIntermedia.top().getTipoString();
            pilaIntermedia.pop();
        }
    }



};


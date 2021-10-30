#include "Dioses.h"

using namespace std;

class Cartas
{
private:
    int tipo;
    
public:
    Cartas(int pTipo){
        tipo= pTipo;
    };

    int getTipo(){
        return tipo;
    }
    
    string getTipoString(){
        switch (tipo)
        {
        case 1:
            return "milagro";
        case 2:
            return "traicion";
        case 3:
            return "anarquia";
        case 4:
            return "union";
        case 5:
            return "nuevo dios";
        case 6:
            return "retorno";
        case 7:
            return "muerte";
        }
        return "";
    }
    

    void cartaMilagro(Dios* ganador,Dios* perdedor){
        int fielesPerdedor = perdedor->getFieles();
        int veintePorciento = fielesPerdedor*0.2;
        
        ganador->sumarFieles(veintePorciento);
        perdedor->sumarFieles(veintePorciento*-1);
        
    }

    void cartaTraicion(Dios* ganador, Dios* perdedor){
        int treintaPorciento = perdedor->getFieles() *0.3;
        
        perdedor->sumarFieles(treintaPorciento*-1);
        ganador->sumarFieles(treintaPorciento);
    }


    Dios cartaNuevoDios(Dios* pDiosB, Dios* pDiosA){
        return Dios(pDiosB->getFieles()+pDiosA->getFieles(),"Hijo de "+pDiosB->getNombre()+" y "+pDiosA->getNombre());
    }

    void cartaMuerte(Dios* pDiosA){
        pDiosA->sumarFieles((pDiosA->getFieles()*0.1)*-1);
    }

    // void cartaRetorno(Stack* pilaPrincipal, Stack* pilaReserva){
    //     pilaPrincipal->regresaCartas(pilaReserva);
    // }

    void cartaAnarquia(){

    }
    void cartaUnion(){
        
    }
    


};


#ifndef _CARTAS_
#define _CARTAS_ 1
#include "Dioses.h"

using namespace std;

class Cartas {
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
        

        void cartaMilagro(Dios* pGanador,Dios* pPerdedor){
            int fielesPerdedor = pPerdedor->getFieles();
            int veintePorciento = fielesPerdedor*0.2;
            
            pGanador->sumarFieles(veintePorciento);
            pPerdedor->sumarFieles(veintePorciento*-1);
            
        }

        void cartaTraicion(Dios* pGanador, Dios* pPerdedor){
            int treintaPorciento = pPerdedor->getFieles() *0.3;
            
            pPerdedor->sumarFieles(treintaPorciento*-1);
            pGanador->sumarFieles(treintaPorciento);
        }


        Dios cartaNuevoDios(string pNombreNuevo, Dios* pDiosB, Dios* pDiosA){
            Dios diosNuevo(pDiosB->getFieles() + pDiosA->getFieles(),pNombreNuevo);
            return diosNuevo;
        }


        void cartaMuerte(Dios* pDiosA){
            pDiosA->sumarFieles((pDiosA->getFieles()*0.1)*-1);
        }
        
};

#endif
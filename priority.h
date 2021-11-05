#ifndef _PRIORIDAD_
#define _PRIORIDAD_ 1

#include <iostream>
#include <string>
#include <queue>

#include "Dioses.h"
 
#include <bits/stdc++.h>

using namespace std;

//Tomado de:
//https://stackoverflow.com/questions/19535644/how-to-use-the-priority-queue-stl-for-objects/19535699

//Se aplico la modificacion para el tipo de objeto a trabajar
bool operator<(const Dios& pDiosA, const Dios& pDiosB) {

    Dios diosTempA = pDiosA, diosTempB = pDiosB;
    if(pDiosA.fieles != pDiosB.fieles)
        return pDiosA.fieles < pDiosB.fieles;
    else{
        return diosTempA.nombre.append(diosTempB.nombre) > diosTempB.nombre.append(diosTempA.nombre);
    }
} 


class ColaPrioridad{
    private:
        priority_queue<Dios> colaDioses;

    public:
        void add(Dios* pDios){
            Dios diosNuevo(pDios->getFieles(),pDios->getNombre());
            colaDioses.push(diosNuevo);
        }

        void elimina(){
            colaDioses.pop();
        }

        Dios primero(){
            return colaDioses.top();
        }

        int tamano(){
            return colaDioses.size();
        }

        bool isEmpty(){
            return colaDioses.empty();
        }

        //REVISAR NO FUNCA
        void imprimirCola(){
            for (int dios = 0; dios < tamano(); ++dios) {
                cout<< colaDioses.top().nombre <<" "<< colaDioses.top().fieles <<"\n";
                colaDioses.pop();
            }
        }
};
#endif
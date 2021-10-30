#ifndef _PRIORIDAD_
#define _PRIORIDAD_ 1

#include <iostream>
#include <string>
#include <queue>

#include "Dioses.h"

#include <bits/stdc++.h>

using namespace std;

bool operator<(const Dios& a, const Dios& b) {

    Dios temp1= a,temp2= b;
    if(a.fieles != b.fieles)
        return a.fieles < b.fieles;
    else{
        return temp1.nombre.append(temp2.nombre) > temp2.nombre.append(temp1.nombre);
    }
} 

class ColaPrioridad{
    private:
        priority_queue<Dios> colaDioses;

    public:
        void add(Dios* pDios){
            Dios diosG(pDios->getFieles(),pDios->getNombre());
            colaDioses.push(diosG);
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
            for (int i = 0; i < tamano(); ++i) {
                cout<<colaDioses.top().nombre<<" "<<colaDioses.top().fieles<<"\n";
                colaDioses.pop();
            }
        }
};
#endif
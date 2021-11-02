#include <iostream>
#include <string>

#include "Dioses.h"         //esta en el Joctan_Branch
#include "priority.h"
#include "leeJson.h"
#include "ArbolAVL.h"

#include <bits/stdc++.h>

using namespace std;

void Mostrar(Nodo* d, int FE)
{
   cout << d->dato->getNombre() << "  " <<d->dato->getFieles() << "\t";
}

// void llenaArbol(AVL* arbol, ColaPrioridad cola){
//     for (;!cola.isEmpty();) {
//         Dios diosGenerico = cola.primero();
//         arbol->Insertar(&diosGenerico);
//         //cout<<cola.primero().getNombre()<<" "<<cola.primero().getFieles()<<"\n";
//         cola.elimina();
//     } 
// }


int main(){
    AVL arbolito;
    

    ColaPrioridad copiaArbol;
    ColaPrioridad colaDioses = leerArchivo();
    copiaArbol = colaDioses;

    for (;!colaDioses.isEmpty();) {
        //Dios diosGenerico = new Dios(colaDioses.primero().getFieles(),colaDioses.primero().getFieles());
        arbolito.Insertar(new Dios(colaDioses.primero().getFieles(),colaDioses.primero().getNombre()));
        //cout<<cola.primero().getNombre()<<" "<<cola.primero().getFieles()<<"\n";
        colaDioses.elimina();
    }

    arbolito.PostOrden(Mostrar,nullptr,true);
/*     
    Faltaria hacer la carta de anarquia y la carta de union 
    Y hacer vectores de AVL para almacenar los arboles nuevos
    que se creen a partir de la carta Anarquia. Y ademas para
    checkear cuando los dioses estan en arboles separados y 
    hacer los correspondientes asignaciones.
 */

}
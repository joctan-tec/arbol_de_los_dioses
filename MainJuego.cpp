#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

#include "ArbolAVL.h"
#include "priority.h"
#include "leeJson.h"
#include "Stack.h"

#include <bits/stdc++.h>

//METODO QUE PERMITE IMPRIMIR LOS DIOSES EN POST ORDEN
void Mostrar(Nodo* d)
{
   cout << "Nombre del Dios:  " <<d->dato->getNombre() << "    Fieles: " <<d->dato->getFieles() << endl;
}

using namespace std;

static bool activador = false;
AVL arbolito;
vector<AVL> listaArboles; 

void init(){
    int contadorRondas = 1;

    // AVL arbolito;
    // vector<AVL> listaArboles; 
    Stack cartas(true);

    cartas = cartas.mezclarCartas(&cartas);

    Stack cartasRetorno(1);

    LeeJson archivo;
    ColaPrioridad copiaArbol;

    ColaPrioridad colaDioses = archivo.leerArchivo("infoDioses.json");
    stack<string> nombresSecundarios = archivo.leerArchivoConStack("nombresDioses.json");

    copiaArbol = colaDioses;

    for (;!colaDioses.isEmpty();) {               
        arbolito.Insertar(new Dios(colaDioses.primero().getFieles(),colaDioses.primero().getNombre()));
        colaDioses.elimina();
    }
    listaArboles.push_back(arbolito);

    cout << "                            ********************" << endl;
    cout << "*************************     INICIO DEL JUEGO      *************************" << endl;
    cout << "                            ********************" << endl;

    while (!activador) {
        cout << "***************************   R O N D A";
        cout << "       " << contadorRondas << "     *************************" << endl;
        contadorRondas++;
        
        if(cartas.esVacia()){
            cartas.rellenarPila(&cartasRetorno);
        }
        Cartas cartaSacada = cartas.obtenerCarta();
        cout << "           Carta Sacada:    \t    " << cartaSacada.getTipoString() << endl;
        cout << "*****************************************************************************"<< endl;
        Dios diosA = copiaArbol.primero();
        copiaArbol.elimina();
        Dios diosB = copiaArbol.primero();
        copiaArbol.elimina();
        Dios diosCopia1(diosA.getFieles(),diosA.getNombre());
        Dios diosCopia2(diosB.getFieles(),diosB.getNombre());

        if (cartaSacada.getTipo()==1) {
            //  MILAGRO

                    cout << "       Dioses en Batalla:          " <<endl;
            cout << diosA.getNombre() << " con " << diosA.getFieles() << " fieles" << endl;
            cout << diosB.getNombre() << " con " << diosB.getFieles() << " fieles" << endl << endl;

            int contadorDiosA;
            int contadorDiosB;

            cartaSacada.cartaMilagro(&diosA,&diosB);

            //Se eliminan del arbol
            for (int i = 0; i < listaArboles.size(); i++)
            {
                if (listaArboles[i].getRaiz() != nullptr & listaArboles[i].Buscar(&diosCopia1))
                {
                    listaArboles[i].Borrar(&diosCopia1);
                    contadorDiosA = i;
                }else if (listaArboles[i].getRaiz() != nullptr & listaArboles[i].Buscar(&diosCopia2))
                {                               
                    listaArboles[i].Borrar(&diosCopia2);
                    contadorDiosB = i;
                } 
            }

            //se insertan nuevamente los dioses en sus arboles correspondientes
            listaArboles[contadorDiosA].Insertar(new Dios(diosA.getFieles(),diosA.getNombre()));
            listaArboles[contadorDiosB].Insertar(new Dios(diosB.getFieles(),diosB.getNombre()));

                    cout << "       Despues de la Batalla:       " <<endl;
            cout << diosA.getNombre() << " con " << diosA.getFieles() << " fieles" << endl;
            cout << diosB.getNombre() << " con " << diosB.getFieles() << " fieles" << endl;
            cout << "*****************************************************************************" << endl;

        }else if (cartaSacada.getTipo()==2)
        {
            //  TRAICION

                    cout << "       Dioses en Batalla:          " <<endl;
            cout << diosA.getNombre() << " con " << diosA.getFieles() << " fieles" << endl;
            cout << diosB.getNombre() << " con " << diosB.getFieles() << " fieles" << endl << endl;

            int contadorDiosA;
            int contadorDiosB;

            cartaSacada.cartaTraicion(&diosA,&diosB);
            //Se eliminan del arbol
            for (int i = 0; i < listaArboles.size(); i++)
            {
                if (listaArboles[i].getRaiz() != nullptr& listaArboles[i].Buscar(&diosCopia1))
                {
                    listaArboles[i].Borrar(&diosCopia1);
                    contadorDiosA = i;
                }else if (listaArboles[i].getRaiz() != nullptr & listaArboles[i].Buscar(&diosCopia2))
                {                               
                    listaArboles[i].Borrar(&diosCopia2);
                    contadorDiosB = i;
                } 
            }

            //se insertan nuevamente los dioses en sus arboles correspondientes
            listaArboles[contadorDiosA].Insertar(new Dios(diosA.getFieles(),diosA.getNombre()));
            listaArboles[contadorDiosB].Insertar(new Dios(diosB.getFieles(),diosB.getNombre()));

                    cout << "       Despues de la Batalla:       " <<endl;
            cout << diosA.getNombre() << " con " << diosA.getFieles() << " fieles" << endl;
            cout << diosB.getNombre() << " con " << diosB.getFieles() << " fieles" << endl;
            cout << "*****************************************************************************" << endl;

        }else if (cartaSacada.getTipo()==3)
        {
            // ANARQUIA
            cout << "*****************************************************************************" << endl;

            
        }else if (cartaSacada.getTipo()==4)
        {
            // UNION
            /*
                    Cuando hay unión, se inserta el árbol con 
                    menos nodos en el árbol de mayor 
                    cantidad de nodos
            */
           cout << "*****************************************************************************" << endl;
            
        }else if (cartaSacada.getTipo()==5)
        {
            // NUEVO DIOS

                    cout << "       Dioses en Batalla:          " <<endl;
            cout << diosA.getNombre() << " con " << diosA.getFieles() << " fieles" << endl;
            cout << diosB.getNombre() << " con " << diosB.getFieles() << " fieles" << endl << endl;

            Dios nuevo = cartaSacada.cartaNuevoDios(nombresSecundarios.top(),&diosA,&diosB);
            nombresSecundarios.pop();   //sacamos el nombre que utilizamos
            for (int i = 0; i < listaArboles.size(); i++)
            {
                if (listaArboles[i].getRaiz() != nullptr & listaArboles[i].Buscar(&diosCopia1)) {
                    listaArboles[i].Insertar(&nuevo);
                }
            }
            copiaArbol.add(new Dios(nuevo.getFieles(),nuevo.getNombre()));

                    cout << "       Despues de la Batalla:       " <<endl;
            cout << diosA.getNombre() << " con " << diosA.getFieles() << " fieles" << endl;
            cout << diosB.getNombre() << " con " << diosB.getFieles() << " fieles" << endl;
            cout << "*****************************************************************************" << endl;
            
        }else if (cartaSacada.getTipo()==6)
        {
            //RETORNO
            cout << cartas.regresaCartas(&cartasRetorno) << endl;   

        }else if (cartaSacada.getTipo()==7)
        {
            //  MUERTE

                    cout << "       Dioses en Batalla:          " <<endl;
            cout << diosA.getNombre() << " con " << diosA.getFieles() << " fieles" << endl;
            cout << diosB.getNombre() << " con " << diosB.getFieles() << " fieles" << endl << endl;

            int contadorDiosA;
            int contadorDiosB;

            cartaSacada.cartaMuerte(&diosA);
            //Se elimina el dios del arbol
            for (int i = 0; i < listaArboles.size(); i++)
            {
                if (listaArboles[i].getRaiz() != nullptr & listaArboles[i].Buscar(&diosCopia1)) {
                    listaArboles[i].Borrar(&diosCopia1);
                    contadorDiosA = i;
                    for (int j = 0; j < listaArboles.size(); j++)
                    {
                        if (listaArboles[j].getRaiz() != nullptr & listaArboles[j].Buscar(&diosCopia2)) {
                            listaArboles[j].Borrar(&diosCopia2);
                            contadorDiosB = j;
                        }
                    } 
                }
            }

            listaArboles[contadorDiosA].Insertar(new Dios(diosA.getFieles(),diosA.getNombre()));
            listaArboles[contadorDiosB].Insertar(new Dios(diosB.getFieles(),diosB.getNombre()));

                    cout << "       Despues de la Batalla:       " <<endl;
            cout << diosA.getNombre() << " con " << diosA.getFieles() << " fieles" << endl;
            cout << diosB.getNombre() << " con " << diosB.getFieles() << " fieles" << endl;
            cout << "*****************************************************************************" << endl;

        }
        cartasRetorno.agregarCarta(cartaSacada);

        copiaArbol.add(new Dios(diosA.getFieles(),diosA.getNombre()));
        copiaArbol.add(new Dios(diosB.getFieles(),diosB.getNombre()));
        
        listaArboles[0] = listaArboles[0].ReconstruyeArbol(copiaArbol);
        
        ///////////////////////// TIEMPO /////////////////////////////
        this_thread::sleep_for(chrono::milliseconds(3000));
    }
}

int main(){
    thread hiloJuego(init);
    cin.get();
    activador = true;

    hiloJuego.join();
    cout << "*************************   F I N   D E   P A R T I D A   *************************" << endl << endl << endl;


    cout << "*************************      R E S U L T A D O S        *************************" << endl;
    listaArboles[0].PostOrden(Mostrar,nullptr,true);


}
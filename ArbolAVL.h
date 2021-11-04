#ifndef _NODOAVL_
#define _NODOAVL_ 1

#include <iostream>
using namespace std;

#include "Dioses.h"
#include "priority.h"

// Clase Nodo de Arbol AVL:
class Nodo {
  public:
     // Constructor:
     Nodo(Dios* dat, Nodo* pad=nullptr, Nodo* izq=nullptr, Nodo* der=nullptr):
          dato(dat), padre(pad), izquierdo(izq), derecho(der), FE(0) {}
     // Miembros:
     Dios* dato;

     int FE;
     Nodo* izquierdo;
     Nodo* derecho;
     Nodo* padre;
     friend class AVL;
};

class AVL{
     private:
          enum {IZQUIERDO, DERECHO};
          // Punteros de la lista, para la raiz y nodo actual:
          Nodo* raiz;
          Nodo* actual;
          int contador;
          int altura;

     public:
          //Constructor
          AVL(): raiz(nullptr), actual(nullptr) {}

          //Verifica vacio
          bool Vacio(Nodo* nodo) { 
               return nodo == nullptr; 
          }

          //Comprueba la raiz
          Nodo* getRaiz(){
               return raiz;
          }

          // Comprobar si es un nodo hoja
          bool EsHoja(Nodo* nodo) { 
               return !nodo->derecho && !nodo->izquierdo; 
          }

          // Contar el numero de nodos
          int NumeroNodos() {
               contador = 0;
               auxContador(raiz); // Funcion auxiliar
               return contador;
          }

          // Funcion auxiliar para contar nodos. Funcion recursiva de recorrido en
          //   preorden, el proceso es aumentar el contador
          void auxContador(Nodo* nodo) {
               contador++;  // Otro nodo
               // Continuar recorrido
               if(nodo->izquierdo) auxContador(nodo->izquierdo);
               if(nodo->derecho)   auxContador(nodo->derecho);
          }

          // Poda: borrar todos los nodos a partir de uno, incluido
          void Podar(Nodo* &nodo) {
          // Algoritmo recursivo, recorrido en postorden
               if(nodo) {
                    Podar(nodo->izquierdo); // Podar izquierdo
                    Podar(nodo->derecho);   // Podar derecho
                    delete nodo;            // Eliminar nodo
                    nodo = nullptr;
               }
          }


          //Inserta un objeto de tipo Dios en el arbol
          void Insertar(Dios* dat){
               Nodo *padre = nullptr;

               //cout << "Insertar: " << dat->getFieles() << endl;
               actual = raiz;
               // Buscar el dato en el arbol, manteniendo un puntero al nodo padre
               while( !Vacio(actual) && dat->getFieles() != actual->dato->getFieles() ) {  //modificar nodo
                    padre = actual;
                    if( dat->getFieles() > actual->dato->getFieles() ) actual = actual->derecho;
                    else if( dat->getFieles() <= actual->dato->getFieles() ) actual = actual->izquierdo;
               }

               // Si el elemento es igual a la raiz
               // se inserta a la izquierda
               if (actual != nullptr){
                    if ( dat->getFieles() == actual->dato->getFieles() ){
                         padre = actual;
                         if ( dat->getFieles() == actual->dato->getFieles() ) actual = actual->izquierdo;
                    }
               }
               // Si se ha encontrado el elemento, regresar sin insertar
               if(!Vacio(actual)){   
                    return;
               }
               // Si padre es nulo, entonces el arbol estaba vacio, el nuevo nodo sera
               // el nodo raiz
               if(Vacio(padre)) raiz = new Nodo(dat);
               // Si el dato es menor que el que contiene el nodo padre, lo insertamos
               // en la rama izquierda
               else if(dat->getFieles() <= padre->dato->getFieles()) {
                    padre->izquierdo = new Nodo(dat, padre);
                    EquilibrarArbol(padre, IZQUIERDO, true);
               }
               // Si el dato es mayor que el que contiene el nodo padre, lo insertamos
               // en la rama derecha
               else if(dat->getFieles() > padre->dato->getFieles()) {
                    padre->derecho = new Nodo(dat, padre);
                    EquilibrarArbol(padre, DERECHO, true);
               }
          }

          // Equilibrar arbol AVL partiendo del nodo nuevo
          void EquilibrarArbol(Nodo* nodo, int rama, bool nuevo){
               bool salir = false;

               // Recorrer camino inverso actualizando valores de FE:
               while(nodo && !salir) {
                    if(nuevo)
                    if(rama == IZQUIERDO) nodo->FE--; // Depende de si anadimos ...
                    else                  nodo->FE++;
                    else
                    if(rama == IZQUIERDO) nodo->FE++; // ... o borramos
                    else                  nodo->FE--;
                    if(nodo->FE == 0) salir = true; // La altura de las rama que
                                                  // empieza en nodo no ha variado,
                                                  // salir de equilibrar
                    else if(nodo->FE == -2) { // Rotar a derechas y salir:
                         try{
                              if( nodo->izquierdo != nullptr )
                                   if (nodo->izquierdo->FE == 1)
                                        RDD(nodo); // Rotacion doble
                                   else RSD(nodo);                         // Rotacion simple
                                        salir = true;
                         } catch (exception e){
                              RDD(nodo);
                         }
                    }
                    else if(nodo->FE == 2) {  // Rotar a izquierdas y salir:
                         if(nodo->derecho->FE == -1) RDI(nodo); // Rotacion doble
                         else RSI(nodo);                        // Rotacion simple
                         salir = true;
                    }
                    if(nodo->padre) 
                    if(nodo->padre->derecho == nodo) rama = DERECHO; else rama = IZQUIERDO;
                    nodo = nodo->padre; // Calcular FE, siguiente nodo del camino.
               }   
          }

          // Rotacion doble a derechas
          void RDD(Nodo* nodo) {
               Nodo *Padre = nodo->padre;
               Nodo *P = nodo;
               Nodo *Q = P->izquierdo;
               Nodo *R = Q->derecho;
               Nodo *B = R->izquierdo;
               Nodo *C = R->derecho;

               if(Padre) 
                    if(Padre->derecho == nodo) Padre->derecho = R;
                    else Padre->izquierdo = R;
               else raiz = R;

               // Reconstruir arbol:
               Q->derecho = B;
               P->izquierdo = C;
               R->izquierdo = Q;
               R->derecho = P;
               
               // Reasignar padres:
               R->padre = Padre;
               P->padre = Q->padre = R;
               if(B) B->padre = Q;
               if(C) C->padre = P;

               // Ajustar valores de FE:
               switch(R->FE) {
                    case -1: Q->FE = 0; P->FE = 1; break;
                    case 0:  Q->FE = 0; P->FE = 0; break;
                    case 1:  Q->FE = -1; P->FE = 0; break;
               }
               R->FE = 0;
          }

          // Rotacion simple a derechas
          void RSD(Nodo* nodo) {
               Nodo *Padre = nodo->padre;
               Nodo *P = nodo;
               Nodo *Q = P->izquierdo;
               Nodo *B = Q->derecho;

               if(Padre) 
                    if(Padre->derecho == P) Padre->derecho = Q;
                    else Padre->izquierdo = Q;
               else raiz = Q;

               // Reconstruir arbol:
               P->izquierdo = B;
               Q->derecho = P;
               
               // Reasignar padres:
               P->padre = Q;
               if(B) B->padre = P;
               Q->padre = Padre;

               // Ajustar valores de FE:
               P->FE = 0;
               Q->FE = 0;
          }

          // Rotacion doble a izquierdas
          void RDI(Nodo* nodo) {
               Nodo *Padre = nodo->padre;
               Nodo *P = nodo;
               Nodo *Q = P->derecho;
               Nodo *R = Q->izquierdo;
               Nodo *B = R->izquierdo;
               Nodo *C = R->derecho;

               if(Padre)
                    if(Padre->derecho == nodo) Padre->derecho = R;
                    else Padre->izquierdo = R;
               else raiz = R;

               // Reconstruir arbol:
               P->derecho = B;
               Q->izquierdo = C;
               R->izquierdo = P;
               R->derecho = Q;
               
               // Reasignar padres:
               R->padre = Padre;
               P->padre = Q->padre = R;
               if(B) B->padre = P;
               if(C) C->padre = Q;

               // Ajustar valores de FE:
               switch(R->FE) {
                    case -1: P->FE = 0; Q->FE = 1; break;
                    case 0:  P->FE = 0; Q->FE = 0; break;
                    case 1:  P->FE = -1; Q->FE = 0; break;
               }
               R->FE = 0;
          }

          // Rotacion simple a izquierdas
          void RSI(Nodo* nodo) {
               Nodo *Padre = nodo->padre;
               Nodo *P = nodo;
               Nodo *Q = P->derecho;
               Nodo *B = Q->izquierdo;

               if(Padre) 
                    if(Padre->derecho == P) Padre->derecho = Q;
                    else Padre->izquierdo = Q;
               else raiz = Q;

               // Reconstruir arbol:
               P->derecho = B;
               Q->izquierdo = P;
               
               // Reasignar padres:
               P->padre = Q;
               if(B) B->padre = P;
               Q->padre = Padre;
               
               // Ajustar valores de FE:
               P->FE = 0;
               Q->FE = 0;
          }

          // Buscar un valor en el arbol
          bool Buscar(Dios* dat) {
               actual = raiz;

               // Todavia puede aparecer, ya que quedan nodos por mirar
               while(!Vacio(actual)) {
                    if(dat->getFieles() == actual->dato->getFieles() & dat->getNombre() == actual->dato->getNombre()) {return true;} // dato encontrado
                    else if(dat->getFieles() > actual->dato->getFieles()) {actual = actual->derecho;} // Seguir
                    else if(dat->getFieles() <= actual->dato->getFieles()) {actual = actual->izquierdo;}
               }
               return false; // No esta en arbol
          }


          // Eliminar un elemento de un arbol AVL
          void Borrar(Dios* dat) {
               Nodo *padre = nullptr;
               Nodo *nodo;
               Dios* aux;

               actual = raiz;
               // Mientras sea posible que el valor esta en el arbol
               while (!Vacio(actual)) {
                    if (dat->getFieles() == actual->dato->getFieles() && dat->getNombre() == actual->dato->getNombre()) { // Si el valor esta en el nodo actual
                         if (EsHoja(actual)) { // Y si ademas es un nodo hoja: lo borramos
                              if(padre) // Si tiene padre (no es el nodo raiz)
                                   // Anulamos el puntero que le hace referencia
                                   if (padre->derecho == actual) padre->derecho = nullptr;
                                   else if(padre->izquierdo == actual) padre->izquierdo = nullptr;
                              //guardaBorrado(actual);
                              //delete actual; // Borrar el nodo
                              actual = nullptr;
                              // El nodo padre del actual puede ser ahora un nodo hoja, por lo tanto su
                              // FE es cero, pero debemos seguir el camino a partir de su padre, si existe.
                              if (NumeroNodos() == 1){
                                   Podar(raiz);
                                   return;
                              }

                              if((padre->derecho == actual && padre->FE == 1) ||
                                   (padre->izquierdo == actual && padre->FE == -1)) {
                                   padre->FE = 0;
                                   actual = padre;
                                   padre = actual->padre;
                              }
                              if(padre)
                                   if(padre->derecho == actual) EquilibrarArbol(padre, DERECHO, false);
                                   else                         EquilibrarArbol(padre, IZQUIERDO, false);
                         }
                         else { // Si el valor esta en el nodo actual, pero no es hoja
                              // Buscar nodo
                              padre = actual;
                              // Buscar nodo mas izquierdo de rama derecha
                              if(actual->derecho) {
                                   nodo = actual->derecho;
                                   while(nodo->izquierdo) {
                                        padre = nodo;
                                        nodo = nodo->izquierdo;
                                   }
                              }
                              // O buscar nodo mas derecho de rama izquierda
                              else {
                                   nodo = actual->izquierdo;
                                   while(nodo->derecho) {
                                        padre = nodo;
                                        nodo = nodo->derecho;
                                   }
                              }
                              // Intercambiar valores de nodo a borrar u nodo encontrado
                              // y continuar, cerrando el bucle. El nodo encontrado no tiene
                              // por que ser un nodo hoja, cerrando el bucle nos aseguramos
                              // de que solo se eliminan nodos hoja.
                              aux = actual->dato;
                              actual->dato = nodo->dato;
                              nodo->dato = aux;
                              actual = nodo;
                         }
                    }
                    else { // Todavia no hemos encontrado el valor, seguir buscandolo
                         padre = actual;
                         if(dat->getFieles() > actual->dato->getFieles()) {actual = actual->derecho;}
                         else if(dat->getFieles() <= actual->dato->getFieles()) {actual = actual->izquierdo;}
                    }
               }
          }

          // Recorrido de arbol en postorden, aplicamos la funcion func, que tiene
          // el prototipo:
          // void func(Nodo&);
          void PostOrden(void (*func)(Nodo*), Nodo* nodo, bool r) {
               if(r){
                    nodo = raiz;
               }
               if(nodo->izquierdo) {
                    PostOrden(func, nodo->izquierdo, false);
               }
               if(nodo->derecho) {
                    PostOrden(func, nodo->derecho, false);
               }
               func( nodo );
          }

          //ANARQUIA
          AVL cartaAnarquia(Dios* dat) {

               Nodo* padre = nullptr;

               AVL nuevoArbolAnarquico;

               Nodo* nodo;
               Nodo* sEliminar;

               actual = raiz;
               // Mientras sea posible que el valor esta en el arbol
               while (!Vacio(actual)) {
                    if (dat->getFieles() == actual->dato->getFieles() && dat->getNombre() == actual->dato->getNombre()) { // Si el valor esta en el nodo actual
                         if (EsHoja(actual)) { // Y si ademas es un nodo hoja: lo borramos
                              nuevoArbolAnarquico.Insertar(new Dios(actual->dato->getFieles(),actual->dato->getNombre()));
                              sEliminar = actual;
                              Borrar(sEliminar->dato);
                              return nuevoArbolAnarquico;
                         }
                         else { // Si el valor esta en el nodo actual, pero no es hoja
               
                              //ACA SE TENDRIA QUE HACER LA DIVISION, SE TOMA LA RAIZ (EL ACTUAL) Y LUEGO SE 
                              // CORTA EL ENLACE CON EL DERECHO PARA INSERTARLOS EN EL ARBOL NUEVAMENTE
                              //Y LA PARTE IZQUIERDA SE HARIA INSERTAR EN EL ARBOL NUEVO
                              padre = actual;

                              nuevoArbolAnarquico.Insertar(new Dios(actual->dato->getFieles(),actual->dato->getNombre()));

                              if (actual->izquierdo) {
                                   nodo = actual->izquierdo;
                                   nuevoArbolAnarquico.Insertar(new Dios(nodo->dato->getFieles(),nodo->dato->getNombre()));
                                   sEliminar = actual->izquierdo;
                                   Borrar(sEliminar->dato);

                                   while (!Vacio(nodo)) {
                                        nuevoArbolAnarquico.Insertar(new Dios(nodo->dato->getFieles(),nodo->dato->getNombre()));
                                        sEliminar = nodo;
                                        Borrar(sEliminar->dato);

                                        if (nodo->izquierdo) {
                                             nuevoArbolAnarquico.Insertar(new Dios(nodo->dato->getFieles(),nodo->dato->getNombre()));
                                             sEliminar = nodo->izquierdo;
                                             Borrar(sEliminar->dato);
                                        }
                                        if (nodo->derecho) {
                                             nuevoArbolAnarquico.Insertar(new Dios(nodo->dato->getFieles(),nodo->dato->getNombre()));
                                             sEliminar = nodo->derecho;
                                             Borrar(sEliminar->dato);
                                        }
                                        nodo = nodo->izquierdo;
                                   }

                              }
                              actual = sEliminar->padre;
                              Borrar(actual->dato);
                         }
                         
                         return nuevoArbolAnarquico;
                    }
                    else { // Todavia no hemos encontrado el valor, seguir buscandolo
                         padre = actual;
                         if(dat->getFieles() > actual->dato->getFieles()) {actual = actual->derecho;}
                         else if(dat->getFieles() <= actual->dato->getFieles()) {actual = actual->izquierdo;}
                    }
               }
               return nuevoArbolAnarquico;
          }

          AVL ReconstruyeArbol(ColaPrioridad cola){
               AVL arbolNuevo;
               for (;!cola.isEmpty();) {               
                    arbolNuevo.Insertar(new Dios(cola.primero().getFieles(),cola.primero().getNombre()));
                    cola.elimina();
               }
               return arbolNuevo;
          }


          // EN LA LOGICA PRINCIPAL HABRIA QUE SACAR LOS DIOSES DE LA COLA, METERLOS EN UNA VARIABLE TEMPORAL, LUEGO MODIFICAR SEGUN LA CARTA, 
          //LUEGO RECORRER EL VECTOR DE ARBOLES Y BORRAR LOS DIOSES DE SUS ARBOLES CORRESPONDIENTES Y METER LOS DIOSES CON SUS FIELES
          // MODIFICADOS EN SUS ARBOLES CORRESPONDIENTES. ESTO EN CASO DE LAS CARTAS QUE NO SEAN ANARQUIA NI UNION.

          // Despues de esto se tendria que eliminar en el arbol donde este el Dios B, ese nodo
          void auxUnion(Nodo* nodo, AVL* arbolCompleto){
               if(arbolCompleto->raiz==nullptr){
                    return;
               }
               Nodo* aEliminar;
               aEliminar = nodo;
               Insertar(nodo->dato);
               arbolCompleto->Borrar(aEliminar->dato);

               if(nodo->izquierdo) auxUnion(nodo->izquierdo, arbolCompleto);
               if(nodo->derecho) auxUnion(nodo->derecho, arbolCompleto);
          }

          void cartaUnion(AVL* arbol){
               auxUnion(arbol->raiz, arbol);
          }
};

#endif
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
     Nodo(Dios* pDataNueva, Nodo* pad=nullptr, Nodo* izq=nullptr, Nodo* der=nullptr):
          dato(pDataNueva), padre(pad), izquierdo(izq), derecho(der), FE(0) {}
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
          bool EsHoja(Nodo* pNodo) { 
               return !pNodo->derecho && !pNodo->izquierdo; 
          }

          // Contar el numero de nodos
          int NumeroNodos() {
               contador = 0;
               auxContador(raiz); // Funcion auxiliar
               return contador;
          }

          // Funcion auxiliar para contar nodos. Funcion recursiva de recorrido en
          //   preorden, el proceso es aumentar el contador
          void auxContador(Nodo* pNodo) {
               contador++;  // Otro nodo
               // Continuar recorrido
               if(pNodo->izquierdo) auxContador(pNodo->izquierdo);
               if(pNodo->derecho)   auxContador(pNodo->derecho);
          }

          // Poda: borrar todos los nodos a partir de uno
          void Podar(Nodo* &pNodo) {
          // Algoritmo recursivo, recorrido en postorden
               if(pNodo) {
                    Podar(pNodo->izquierdo); // Podar izquierdo
                    Podar(pNodo->derecho);   // Podar derecho
                    delete pNodo;            // Eliminar nodo
                    pNodo = nullptr;
               }
          }


          //Inserta un objeto de tipo Dios en el arbol
          void Insertar(Dios* pDataNueva){
               Nodo *padre = nullptr;
               actual = raiz;
               // Buscar el dato en el arbol, manteniendo un puntero al nodo padre
               while( !Vacio(actual) && pDataNueva->getFieles() != actual->dato->getFieles() ) {  //modificar nodo
                    padre = actual;
                    if( pDataNueva->getFieles() > actual->dato->getFieles() ) actual = actual->derecho;
                    else if( pDataNueva->getFieles() <= actual->dato->getFieles() ) actual = actual->izquierdo;
               }

               // Si el elemento es igual a la raiz
               // se inserta a la izquierda
               if (actual != nullptr){
                    if ( pDataNueva->getFieles() == actual->dato->getFieles() ){
                         padre = actual;
                         if ( pDataNueva->getFieles() == actual->dato->getFieles() ) actual = actual->izquierdo;
                    }
               }
               // Si se ha encontrado el elemento, regresar sin insertar
               if(!Vacio(actual)){   
                    return;
               }
               // Si padre es nulo, entonces el arbol estaba vacio, el nuevo nodo sera
               // el nodo raiz
               if(Vacio(padre)) raiz = new Nodo(pDataNueva);
               // Si el dato es menor que el que contiene el nodo padre, lo insertamos
               // en la rama izquierda
               else if(pDataNueva->getFieles() <= padre->dato->getFieles()) {
                    padre->izquierdo = new Nodo(pDataNueva, padre);
                    EquilibrarArbol(padre, IZQUIERDO, true);
               }
               // Si el dato es mayor que el que contiene el nodo padre, lo insertamos
               // en la rama derecha
               else if(pDataNueva->getFieles() > padre->dato->getFieles()) {
                    padre->derecho = new Nodo(pDataNueva, padre);
                    EquilibrarArbol(padre, DERECHO, true);
               }
          }

          // Equilibrar arbol AVL partiendo del nodo nuevo
          void EquilibrarArbol(Nodo* pNodo, int pRama, bool pNuevo){
               bool salir = false;

               // Recorrer camino inverso actualizando valores de FE:
               while(pNodo && !salir) {
                    if(pNuevo)
                    if(pRama == IZQUIERDO) pNodo->FE--; // Depende de si anadimos ...
                    else                  pNodo->FE++;
                    else
                    if(pRama == IZQUIERDO) pNodo->FE++; // ... o borramos
                    else                  pNodo->FE--;
                    if(pNodo->FE == 0) salir = true; // La altura de las rama que
                                                  // empieza en nodo no ha variado,
                                                  // salir de equilibrar
                    else if(pNodo->FE == -2) { // Rotar a derechas y salir:
                         try{
                              if( pNodo->izquierdo != nullptr )
                                   if (pNodo->izquierdo->FE == 1)
                                        RDD(pNodo); // Rotacion doble
                                   else RSD(pNodo);                         // Rotacion simple
                                        salir = true;
                         } catch (exception e){
                              RDD(pNodo);
                         }
                    }
                    else if(pNodo->FE == 2) {  // Rotar a izquierdas y salir:
                         if(pNodo->derecho->FE == -1) RDI(pNodo); // Rotacion doble
                         else RSI(pNodo);                        // Rotacion simple
                         salir = true;
                    }
                    if(pNodo->padre) 
                    if(pNodo->padre->derecho == pNodo) pRama = DERECHO; else pRama = IZQUIERDO;
                    pNodo = pNodo->padre; // Calcular FE, siguiente nodo del camino.
               }   
          }

          // Rotacion doble a derechas
          void RDD(Nodo* pNodo) {
               Nodo *Padre = pNodo->padre;
               Nodo *P = pNodo;
               Nodo *Q = P->izquierdo;
               Nodo *R = Q->derecho;
               Nodo *B = R->izquierdo;
               Nodo *C = R->derecho;

               if(Padre) 
                    if(Padre->derecho == pNodo) Padre->derecho = R;
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
          void RSD(Nodo* pNodo) {
               Nodo *Padre = pNodo->padre;
               Nodo *P = pNodo;
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
          void RDI(Nodo* pNodo) {
               Nodo *Padre = pNodo->padre;
               Nodo *P = pNodo;
               Nodo *Q = P->derecho;
               Nodo *R = Q->izquierdo;
               Nodo *B = R->izquierdo;
               Nodo *C = R->derecho;

               if(Padre)
                    if(Padre->derecho == pNodo) Padre->derecho = R;
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
          void RSI(Nodo* pNodo) {
               Nodo *Padre = pNodo->padre;
               Nodo *P = pNodo;
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
          bool Buscar(Dios* pDataNueva) {
               actual = raiz;

               // Todavia puede aparecer, ya que quedan nodos por mirar
               while(!Vacio(actual)) {
                    if(pDataNueva->getFieles() == actual->dato->getFieles() & pDataNueva->getNombre() == actual->dato->getNombre()) {return true;} // dato encontrado
                    else if(pDataNueva->getFieles() > actual->dato->getFieles()) {actual = actual->derecho;} // Seguir
                    else if(pDataNueva->getFieles() <= actual->dato->getFieles()) {actual = actual->izquierdo;}
               }
               return false; // No esta en arbol
          }


          // Eliminar un elemento de un arbol AVL
          void Borrar(Dios* pDataNueva) {
               Nodo *padre = nullptr;
               Nodo *nodo;
               Dios* auxDios;

               actual = raiz;
               // Mientras sea posible que el valor esta en el arbol
               while (!Vacio(actual)) {
                    if (pDataNueva->getFieles() == actual->dato->getFieles() && pDataNueva->getNombre() == actual->dato->getNombre()) { // Si el valor esta en el nodo actual
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
                              auxDios = actual->dato;
                              actual->dato = nodo->dato;
                              nodo->dato = auxDios;
                              actual = nodo;
                         }
                    }
                    else { // Todavia no hemos encontrado el valor, seguir buscandolo
                         padre = actual;
                         if(pDataNueva->getFieles() > actual->dato->getFieles()) {actual = actual->derecho;}
                         else if(pDataNueva->getFieles() <= actual->dato->getFieles()) {actual = actual->izquierdo;}
                    }
               }
          }

          // Recorrido de arbol en postorden, aplicamos la funcion func, que tiene
          // el prototipo:
          // void func(Nodo&);
          void PostOrden(void (*func)(Nodo*), Nodo* pNodo, bool pRecorrer) {
               if(pRecorrer){
                    pNodo = raiz;
               }
               if(pNodo->izquierdo) {
                    PostOrden(func, pNodo->izquierdo, false);
               }
               if(pNodo->derecho) {
                    PostOrden(func, pNodo->derecho, false);
               }
               func( pNodo );
          }

          //ANARQUIA
          AVL cartaAnarquia(Dios* pDataNueva) {

               Nodo* padre = nullptr;

               AVL nuevoArbolAnarquico;

               Nodo* nodo;
               Nodo* sEliminar;

               actual = raiz;
               // Mientras sea posible que el valor esta en el arbol
               while (!Vacio(actual)) {
                    if (pDataNueva->getFieles() == actual->dato->getFieles() && pDataNueva->getNombre() == actual->dato->getNombre()) { // Si el valor esta en el nodo actual
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
                         if(pDataNueva->getFieles() > actual->dato->getFieles()) {actual = actual->derecho;}
                         else if(pDataNueva->getFieles() <= actual->dato->getFieles()) {actual = actual->izquierdo;}
                    }
               }
               return nuevoArbolAnarquico;
          }

          AVL ReconstruyeArbol(ColaPrioridad pCola){
               AVL arbolNuevo;
               for (;!pCola.isEmpty();) {               
                    arbolNuevo.Insertar(new Dios(pCola.primero().getFieles(),pCola.primero().getNombre()));
                    pCola.elimina();
               }
               return arbolNuevo;
          }


          // EN LA LOGICA PRINCIPAL HABRIA QUE SACAR LOS DIOSES DE LA COLA, METERLOS EN UNA VARIABLE TEMPORAL, LUEGO MODIFICAR SEGUN LA CARTA, 
          //LUEGO RECORRER EL VECTOR DE ARBOLES Y BORRAR LOS DIOSES DE SUS ARBOLES CORRESPONDIENTES Y METER LOS DIOSES CON SUS FIELES
          // MODIFICADOS EN SUS ARBOLES CORRESPONDIENTES. ESTO EN CASO DE LAS CARTAS QUE NO SEAN ANARQUIA NI UNION.

          // Despues de esto se tendria que eliminar en el arbol donde este el Dios B, ese nodo
          void auxUnion(Nodo* pNodo, AVL* pArbolCompleto){
               if(pArbolCompleto->raiz==nullptr){
                    return;
               }
               Nodo* aEliminar;
               aEliminar = pNodo;
               Insertar(pNodo->dato);
               pArbolCompleto->Borrar(aEliminar->dato);

               if(pNodo->izquierdo) auxUnion(pNodo->izquierdo, pArbolCompleto);
               if(pNodo->derecho) auxUnion(pNodo->derecho, pArbolCompleto);
          }

          void cartaUnion(AVL* pArbol){
               auxUnion(pArbol->raiz, pArbol);
          }
};

#endif
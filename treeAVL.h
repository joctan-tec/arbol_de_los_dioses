#ifndef _TREEAVL_
#define _TREEAVL_ 0
#include <iostream>
#include "treenodoAVL.h"

using namespace std;

template <class T>
class TreeAVL2 {
    private:
        int size = 0;

    public:
        void rotarLL(treenodoAVL<T>* &arbol){ //precond: el árbol necesita una rotacion LL
            treenodoAVL<T>* aux = arbol->left->right;
            arbol->left->right = arbol;
            arbol->left->diferencia = 0; 
            treenodoAVL<T>* aux2 = arbol->left;
            arbol->left = aux;
            arbol->diferencia = 0;
            arbol = aux2;
        }

        void rotarRR(treenodoAVL<T>* &arbol){ //precond: el árbol necesita una rotacion RR
            treenodoAVL<T>* aux = arbol->right->left;
            arbol->right->left = arbol;
            arbol->right->diferencia = 0; 
            treenodoAVL<T>* aux2 = arbol->right;
            arbol->right = aux;
            arbol->diferencia = 0;
            arbol = aux2;
        }

        void rotarLRalter(treenodoAVL<T>* &arbol){ //precond: el árbol necesita una rotacion LR
            rotarRR(arbol->left);
            rotarLL(arbol);
        }

        void rotarRLalter(treenodoAVL<T>* &arbol){ //precond: el árbol necesita una rotacion RL
            rotarLL(arbol->right);
            rotarRR(arbol);
        }

        void Insert(int n, bool aumento, treenodoAVL<T>* &arbol){
            if (arbol == nullptr){
                arbol = (treenodoAVL<T>*) malloc(sizeof(treenodoAVL<T>));
                arbol->setData(n);
                arbol->diferencia = 0;
                arbol->left = nullptr;
                arbol->right = nullptr;
                aumento = true;
                arbol->borrado = false;
            }else{
                if (n < arbol->getData()){			
                    Insert(n, aumento, arbol->left);			
                    if (aumento){
                        switch (arbol->diferencia){
                            case -1:{
                                arbol->diferencia = 0;
                                aumento = false;
                                break;
                            }
                            case 0:{
                                arbol->diferencia = 1;
                                aumento = true;
                                break;
                            }
                            case 1:{
                                if (arbol->left->diferencia == 1){ // Si es 1 necesita una rotacion LL si es -1 necesita una rotacion LR
                                    rotarLL(arbol);
                                }else{
                                    rotarLRalter(arbol);
                                }
                                aumento = false;
                                break;
                            }
                        }
                    }
                }else{
                    Insert(n, aumento, arbol->right);			
                    if (aumento){
                        switch (arbol->diferencia){
                            case -1:{
                                if (arbol->right->diferencia == 1){ // Si es 1 necesita una rotacion RL si es -1 necesita una rotacion RR
                                    rotarRLalter(arbol);
                                }else{
                                    rotarRR(arbol);
                                }
                                aumento = false;						
                                break;
                            }
                            case 0:{
                                arbol->diferencia = -1;
                                aumento = true;
                                break;
                            }
                            case 1:{
                                arbol->diferencia = 0;
                                aumento = false;
                                break;
                            }
                        }
                    }
                }
            }
        }

        //Función para mostrar el arbol
        void mostrarArbol(treenodoAVL<T>* arbol,int cont) {
            if (arbol == nullptr) {
                return;
            } else {
                mostrarArbol(arbol->right, cont + 1);
                for (int i = 0; i < cont; i++) {
                    cout <<"    ";
                }
                cout << arbol->getData() << endl;
                mostrarArbol(arbol->left, cont + 1);
            }
        }

        void postorder(treenodoAVL<T>* arbol) {
            if (arbol != nullptr) {
                postorder(arbol->left);
                postorder(arbol->right);
                cout << arbol->getData() << " ";
            }
        }
};

#endif
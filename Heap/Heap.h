#include <iostream>
#include <cassert>
#include <math.h>
#include "../DcNet/Paquete.h"
using namespace std;


class ColaPriorHeap{

    public:
        ColaPriorHeap();
        void Encolar(const Pakete& a);
        bool EsVacia();
        Pakete Desencolar();
        int Cantidad();
        //ColaPriorHeap<T>& operator=(const ColaPriorHeap<T>& otro);


    private:

// Estructura del nodo, tiene un valor de tipo T, su altura, un puntero para cada uno de sus dos hijos y uno para su padre

        struct Nodo{
            Pakete dato;
            Nodo* izq;
            Nodo* der;
            Nodo* padre;
            int alt;
        };

// Funcion para ver si un elemento tiene mas prioridad que otro

        bool mayorPrioridad(Pakete& dato1, Pakete& dato2){
            return (dato1.prioridad() < dato2.prioridad());
        }

// Funcion para cambiar los valores dados dos nodos

        void swapear(Nodo* papa, Nodo* n){

        Pakete aux = papa->dato;
        papa->dato = n->dato;
        n->dato = aux;
   		}


// Funcion que luego de agregar un elemento, reajusta la altura del arbol y luego va subiendo el valor agregado hasta que encuentre su lugar
//________________________________________________________________

        void acomodar(Nodo* n){

        //Modifico la altura

        if (n->padre!=NULL){
        Nodo* aux = n;
        	while (aux->padre != NULL && aux->alt == aux->padre->alt){
        		aux->padre->alt = aux->padre->alt + 1;
        		aux = aux->padre;
        	}
        }

        //Hago los swaps

        Nodo* padre = n->padre;

        while (padre != NULL && mayorPrioridad(n->dato,padre->dato)){
            swapear(padre,n);
        	acomodar(padre);
        }

        }

// Funcion para reajustar la altura una vez que se desencolo el nodo izq de un padreult
//________________________________________________________________

		void ajustaraltura(Nodo* n){
			n->alt = n->alt - 1;
			while (n->padre != NULL && n->padre->izq == n){
				n->padre->alt = n->padre->alt-1;
				n = n->padre;
			}


		}

// Funcion para encontrar el nuevo padreult luego de haber desencolado el elemento izq de un padreult
//________________________________________________________________

		Nodo* buscarpadreult(Nodo* n){

            int altDer = n->der == NULL? 0 : n->der->alt;
            int altIzq = n->izq == NULL? 0 : n->izq->alt;

            if(n == padreult){
                return NULL;
            }else if(n->alt == 2){
                return n;
            }else if (altIzq == altDer){
                return buscarpadreult(n->der);
            }else{
                return buscarpadreult(n->izq);
            }
        }

// Funcion para bajar el valor de un nodo hasta encontrar su lugar
//________________________________________________________________

        void bajar(Nodo* n){

        if(n->der != NULL && n->izq != NULL && n!=NULL ){
            if (mayorPrioridad(n->izq->dato,n->dato) || mayorPrioridad(n->der->dato,n->dato)){
                if(mayorPrioridad(n->izq->dato,n->der->dato)){
                    swapear(n,n->izq);
                    bajar(n->izq);
                }else{
                    swapear(n,n->der);
                    bajar(n->der);
                }
            }
        }else{
            if(n->izq != NULL){
                if(mayorPrioridad(n->izq->dato,n->dato)){
                    swapear(n,n->izq);
                }
            }
        }
        }

        Nodo* raiz;
        Nodo* padreult;
        int cant;
};

// Constructor por defecto
//________________________________________________________________


ColaPriorHeap::ColaPriorHeap(){
    raiz = NULL;
    padreult = NULL;
    cant = 0;
}

// Funcion para encolar un elemnto
//________________________________________________________________


void ColaPriorHeap::Encolar(const Pakete& a){

// Creo el nodo con los datos 

    Nodo* n = new Nodo;
    n->izq = NULL;
    n->der = NULL;
    n->padre = NULL;
    n->dato = a;
    n->alt = 1;
    cant++;

// Me fijo si esta vacio    

    if (raiz == NULL){
        raiz = n;
    }else{

// Si no esta vacio me fijo si tiene solo un elemento (la raiz)

        if (padreult == NULL){
            padreult = raiz;
            n->padre = raiz;
            raiz->izq = n;
        }else{

// Me fijo si padreult der tiene algo , sino lo tiene lo pongo ahi, (siempre que se llega aca el padreult se llena)

            if (padreult->der == NULL){
                n->padre = padreult;
                padreult->der = n;
            }else{

// Me fijo si esta completo el arbol, si lo esta, significa que el nueov padreult es el nodo mas a la izq

                if ((log2(cant)) == int(log2(cant))){
                    Nodo* actual = raiz;
                    while (actual->izq != NULL){
                        actual = actual->izq;
                    }
                    padreult = actual;
                    n->padre = actual;
                    actual->izq = n;
                }else{

// Como el padreult se lleno busco el nuevo padreult , haciendo una busqueda transversal y pongo el valor en padreult izq   

                    Nodo* abuelo = padreult->padre;
                    Nodo* actual = padreult;
                    while (abuelo!=NULL && abuelo->der == actual){
                        actual = abuelo;
                        abuelo = abuelo->padre;
                    }
                    actual = abuelo->der;
                    while(actual->izq != NULL){
                        actual = actual->izq;
                    }
                    padreult = actual;
                    padreult->izq = n;
                    n->padre = padreult;
                }
            }
        }
    }

// Subo el valor del nuevo nodo hasta que encuentre su lugar

    acomodar(n);
}

// Cantidad
//________________________________________________________________


int ColaPriorHeap::Cantidad(){
return cant;
}

// Funcion para Desencolar
//________________________________________________________________


Pakete ColaPriorHeap::Desencolar(){
    assert(cant != 0);
    cant--;
	Pakete a = raiz->dato;
	Nodo* ultimo;

// Me fijo si padreult es nulo o no, basicamente si el heap tiene 3 elementos (no hay padreult) o si tiene mas

	if(padreult != NULL){

// Agarro el valor del nodo der de padreult, lo pongo como raiz y lo bajo, ademas deleteo el nodo der de padreult pues ya no deberia existir


        if (padreult->der != NULL){
            ultimo = padreult->der;
            swapear(ultimo,raiz);
            delete padreult->der;
            padreult->der = NULL;
            bajar(raiz);

        }else{

// Modifico la altura, agarro el valor del nodo izq de padreult, lo pongo como raiz y lo bajo, ademas deleteo el nodo izq de padreult pues ya no deberia existir, y busco el nuevo padreult 

            ultimo = padreult->izq;
            swapear(ultimo,raiz);
            delete padreult->izq;
            padreult->izq = NULL;
            ajustaraltura(padreult);
            padreult = buscarpadreult(raiz);
            if(padreult == raiz){
                padreult = NULL;
            }
            bajar(raiz);
        }
    	}else{

// En este caso no hay padreult pues solo hay como mucho 3 elementos

        	if(raiz->der != NULL){
           		swapear(raiz,raiz->der);
           		delete raiz->der;
            	raiz->der = NULL;
           		bajar(raiz);
       		}else{
            	if(raiz->izq != NULL){
                	swapear(raiz,raiz->izq);
                	delete raiz->izq;
                	raiz->izq = NULL;
                	bajar(raiz);
            	}else{
                	delete raiz;
                    raiz = NULL;
            }
		}
    }
return a;
}
/*
template<typename T>
ColaPriorHeap<T>& operator=(const ColaPriorHeap<T>& otro){
    raiz = otro.raiz;
    padreult = otro.padreult;
    cant = otro.cant;
    return *this;
}
*/
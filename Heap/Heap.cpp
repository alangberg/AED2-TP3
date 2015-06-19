#include <iostream>
#include <cassert>
#include <math.h>

using namespace std;

template<typename T>
class ColaPriorHeap{

    public:
        ColaPriorHeap();
        void Encolar(const T& a);
        bool EsVacia();
        T& Desencolar();
        int Cantidad();


    private:

        struct Nodo{
            T dato;
            Nodo* izq;
            Nodo* der;
            Nodo* padre;
            int alt;
        };

        bool mayorPrioridad(T& dato1, T& dato2){
            return (dato1 > dato2);
        }

        void swapear(Nodo* papa, Nodo* n){

        T aux = papa->dato;
        papa->dato = n->dato;
        n->dato = aux;
   		}


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

		void ajustaraltura(Nodo* n){
			n->alt = n->alt - 1;
			while (n->padre != NULL && n->padre->izq == n){
				n->padre->alt = n->padre->alt-1;
				n = n->padre;
			}


		}


        Nodo* buscarpadreult(Nodo* n){

        if(n == padreult){
            padreult = NULL;
        }else{
        	if(n->alt == 2){
                return n;
        	}else{
        		if (n->izq->alt == n->der->alt){
                    buscarpadreult(n->der);
                }else{
        			if(n->izq->alt > n->der->alt){
        				buscarpadreult(n->izq);

        			}
        		}
    	    }
	    }


        }

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

template<class T>
ostream& operator<<(ostream& out, const ColaPriorHeap<T>& a){
return a.mostrar(out);
}

template<typename T>
ColaPriorHeap<T>::ColaPriorHeap(){
    raiz = NULL;
    padreult = NULL;
    cant = 0;
}

template<typename T>
void ColaPriorHeap<T>::Encolar(const T& a){

    Nodo* n = new Nodo;
    n->izq = NULL;
    n->der = NULL;
    n->padre = NULL;
    n->dato = T(a);
    n->alt = 1;
    cant++;

    if (raiz == NULL){
        raiz = n;
    }else{
        if (padreult == NULL){
            padreult = raiz;
            n->padre = raiz;
            raiz->izq = n;
        }else{
            if (padreult->der == NULL){
                n->padre = padreult;
                padreult->der = n;
            }else{
                if ((log2(cant)) == int(log2(cant))){
                    Nodo* actual = raiz;
                    while (actual->izq != NULL){
                        actual = actual->izq;
                    }
                    padreult = actual;
                    n->padre = actual;
                    actual->izq = n;
                }else{
                    Nodo* abuelo = padreult->padre;
                    Nodo* actual = padreult;
                    while (abuelo!=NULL && abuelo->der == NULL){
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

    acomodar(n);

}

template<typename T>
int ColaPriorHeap<T>::Cantidad(){
return cant;
}


template<typename T>
T& ColaPriorHeap<T>::Desencolar(){

    cant--;
	T a = raiz->dato;
	Nodo* ultimo;



	if(padreult != NULL){

        if (padreult->der != NULL){

            ultimo = padreult->der;
            swapear(ultimo,raiz);
            delete padreult->der;
            padreult->der = NULL;
            bajar(raiz);
        }else{

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
                raiz = NULL;
                delete raiz;
            }
	}
    }


 return a;

}















/*





template<typename T>
void ColaPriorHeap<T>::
template<typename T>
void ColaPriorHeap<T>::



*/














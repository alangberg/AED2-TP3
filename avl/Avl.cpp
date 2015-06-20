#include <iostream> 
#include "Avl.h"
#include "math.h"
using namespace std;


template <class T>
Avl<T>::Nodo::Nodo(const T& v){
	valor = v;
	izq = NULL;
	der = NULL;
	padre = NULL;
	altura = 1;
}
 
template <class T>
Avl<T>::Avl(){
	raiz = NULL;
	cant = 0;
} 



template <class T>
unsigned int Avl<T>::cardinal() const {
    return cant;
}


template <class T>
void Avl<T>::mostrar(std::ostream& o) const { // sin repetidos
    o << "[";
    Nodo* aux = raiz;
    while (aux->der != NULL){
    	aux = aux->der;
    }
    raiz->imprimirNodo(o,aux->valor);    
    o << "]" << endl;
}

template <class T>
void Avl<T>::Nodo::imprimirNodo(std::ostream& o, const T& n) const {  
    if (this->izq != NULL){
        this->izq->imprimirNodo(o, n);       
    }
    o << this->valor;
    if (this->valor != n){
    	o << ",";	
    }    
    if (this->der != NULL){
        this->der->imprimirNodo(o, n);       
    }
}



template <class T>
typename Avl<T>::Nodo* 
Avl<T>::buscarPapa(const T& clave) const {
    Nodo* x = this->raiz;
    Nodo* y = NULL;
    while (x != NULL) {
        y = x;
        if (clave < x->valor)
            x = x->izq ;
        else
            x = x->der ;
        }
    return y;
}


template <class T>
void Avl<T>::rotacionDerecha(Nodo* n){
	Nodo* aux = n->der->izq;
	if (n == raiz){
		n->der->izq = n;
		n->der->padre = NULL;
		raiz = n->der;
		n->padre = n->der;
		n->der = aux;
	} else {
		if (n->padre->izq == n){
			n->padre->izq = n->der;
		} else {
			n->padre->der = n->der;
		}
		n->der->izq = n;
		n->der->padre = n->padre;
		n->padre = n->der;
		n->der = aux;		
	}
	restablecerAlt(n);
}


template <class T>
void Avl<T>::rotacionIzquierda(Nodo* n){
	Nodo* aux = n->izq->der;
	if (n == raiz){
		n->izq->der = n;
		n->izq->padre = NULL;
		raiz = n->izq;
		n->padre = n->izq;
		n->izq = aux;
	} else {
		if (n->padre->izq == n){
			n->padre->izq = n->izq;
		} else {
			n->padre->der = n->izq;
		}
		n->izq->der = n;
		n->izq->padre = n->padre;
		n->padre = n->izq;
		n->izq = aux;
	}	
	restablecerAlt(n);
}


template <class T>
void Avl<T>::rotacionDerIzq(Nodo* n){
	rotacionIzquierda(n->der);
	rotacionDerecha(n);		
}

template <class T>
void Avl<T>::rotacionIzqDer(Nodo* n){
	rotacionDerecha(n->izq);
	rotacionIzquierda(n);
}



template <class T>
void Avl<T>::restablecerAlt(Nodo* n){
	int altDer = n->der == NULL? 0 : n->der->altura;
	int altIzq = n->izq == NULL? 0 : n->izq->altura;
	n->altura = max(altIzq,altDer)+1;
}


template <class T>
void Avl<T>::rebalanceo(Nodo* n){
	int altDer = n->der == NULL? 0 : n->der->altura;
	int altIzq = n->izq == NULL? 0 : n->izq->altura;
	int altIzqIzq = 0;
	int altIzqDer = 0;
	int altDerDer = 0;
	int altDerIzq = 0;
	if (n->izq != NULL){
		altIzqIzq = n->izq->izq == NULL? 0 : n->izq->izq->altura;
		altIzqDer = n->izq->der == NULL? 0 : n->izq->der->altura;
	}
	if (n->der != NULL){
		altDerDer = n->der->der == NULL? 0 : n->der->der->altura;
		altDerIzq = n->der->izq == NULL? 0 : n->der->izq->altura;
	}
	if (altDer - altIzq == 2){
		if (altDerDer > altDerIzq){ //  >= ?
			rotacionDerecha(n);
		} else {
			rotacionDerIzq(n);
		}
	} else if (altDer - altIzq == -2){
		if (altIzqIzq > altIzqDer){ //  >= ?
			rotacionIzquierda(n);
		} else{
			rotacionIzqDer(n);
		}		
	}
	restablecerAlt(n);
	if (n->padre != NULL){
		rebalanceo(n->padre);
	}
}


template <class T>
void Avl<T>::insertar(const T& clave){
	Nodo* nuevo = new Nodo(clave);
	Nodo* papa = raiz;
    if (raiz == NULL){
    	raiz = nuevo;
    	cant++;
    	return;
    }
	papa = buscarPapa(clave);    	
    if (papa->valor < clave ) {	            
        papa->der = nuevo;
        nuevo->padre = papa;
        cant++;	             
    } else if (papa->valor > clave){
        papa->izq = nuevo;
        nuevo->padre = papa;
        cant++;
    }	    
    rebalanceo(papa);
    
}






template <class T>
bool Avl<T>::pertenece(const T& clave) const{ 
	Nodo* n = raiz;
    while (n != NULL){
    	if (n->valor == clave){
    		return true;    		
    	} else if (n->valor > clave){
    		n = n->izq;
    	} else {
    		n = n->der;
    	}
    }
    return false;  
}



template <class T>
typename Avl<T>::Nodo* 
Avl<T>::buscar(const T& clave) const {
    Nodo* x = this->raiz;
    while (x->valor != clave) {
        if (clave < x->valor)
            x = x->izq ;
        else
            x = x->der ;
        }
    return x;
}


template <class T>
void Avl<T>::borrar(const T& clave){ // problemas con 1 y 2 nodos
	Nodo* n = buscar(clave);
	Nodo* aux;
	Nodo* padreAux;
	if (n->izq != NULL){
		aux = n->izq;
		while (aux != NULL && aux->der != NULL){
			aux = aux->der;
		}
		padreAux = aux->padre;
		if (padreAux->der == aux){
			padreAux->der = NULL;
		} else{
			padreAux->izq = NULL;		
		}		
		n->valor = aux->valor;
		delete aux;	
	} else if (n->der != NULL){
		n->der->padre = n->padre;
		if (n == raiz){
			raiz = n->der;
			delete n;
		} else {
			if (n->padre->der == n){
				n->padre->der = n->der;
			} else{
				n->padre->izq = n->der;				
			}
			delete n;
		}
	} else {
		if (n == raiz){
			raiz = NULL;
			delete n;
		} else {
			padreAux = n->padre;
			if (padreAux->der == n){
				padreAux->der = NULL;
			} else{
				padreAux->izq = NULL;		
			}
			delete n;
		}
	}

	rebalanceo(padreAux);
}

/*
template <class T>
Avl<T> Avl<T>::operator=(const Avl<T>& otro){
	raiz = otro.raiz;
	cant = otro.cant;
    return *this;	
}
*/
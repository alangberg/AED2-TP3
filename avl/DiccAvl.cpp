#include <iostream> 
#include "DiccAvl.h"
#include "math.h"
using namespace std;


template<class K,class S>
DiccAvl<K,S>::Nodo::Nodo(const K& k, const S& s){
	clave = k;
	sign = s;
	izq = NULL;
	der = NULL;
	padre = NULL;
	altura = 1;
}
 
template<class K,class S>
DiccAvl<K,S>::DiccAvl(){
	raiz = NULL;
	cant = 0;
} 



template<class K,class S>
unsigned int DiccAvl<K,S>::cardinal() const {
    return cant;
}


template<class K,class S>
void DiccAvl<K,S>::mostrar(std::ostream& o) const { // sin repetidos
    o << "[";
    Nodo* aux = raiz;
    while (aux->der != NULL){
    	aux = aux->der;
    }
    raiz->imprimirNodo(o,aux->clave);    
    o << "]" << endl;
}

template<class K,class S>
void DiccAvl<K,S>::Nodo::imprimirNodo(std::ostream& o, const K& n) const {  
    if (this->izq != NULL){
        this->izq->imprimirNodo(o, n);       
    }
    o << this->clave;
    if (this->clave != n){
    	o << ",";	
    }    
    if (this->der != NULL){
        this->der->imprimirNodo(o, n);       
    }
}



template<class K,class S>
typename DiccAvl<K,S>::Nodo* 
DiccAvl<K,S>::buscarPapa(const K& clave) const {
    Nodo* x = this->raiz;
    Nodo* y = NULL;
    while (x != NULL) {
        y = x;
        if (clave < x->clave)
            x = x->izq ;
        else
            x = x->der ;
        }
    return y;
}


template<class K,class S>
void DiccAvl<K,S>::rotacionDerecha(Nodo* n){
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


template<class K,class S>
void DiccAvl<K,S>::rotacionIzquierda(Nodo* n){
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


template<class K,class S>
void DiccAvl<K,S>::rotacionDerIzq(Nodo* n){
	rotacionIzquierda(n->der);
	rotacionDerecha(n);		
}

template<class K,class S>
void DiccAvl<K,S>::rotacionIzqDer(Nodo* n){
	rotacionDerecha(n->izq);
	rotacionIzquierda(n);
}



template<class K,class S>
void DiccAvl<K,S>::restablecerAlt(Nodo* n){
	int altDer = n->der == NULL? 0 : n->der->altura;
	int altIzq = n->izq == NULL? 0 : n->izq->altura;
	n->altura = max(altIzq,altDer)+1;
}


template<class K,class S>
void DiccAvl<K,S>::rebalanceo(Nodo* n){
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


template<class K,class S>
void DiccAvl<K,S>::definir(const K& clave, const S& significado){
	Nodo* nuevo = new Nodo(clave,significado);
	Nodo* papa = raiz;
    if (raiz == NULL){
    	raiz = nuevo;
    	cant++;
    	return;
    }
	papa = buscarPapa(clave);    	
    if (papa->clave < clave ) {	            
        papa->der = nuevo;
        nuevo->padre = papa;
        cant++;	             
    } else if (papa->clave > clave){
        papa->izq = nuevo;
        nuevo->padre = papa;
        cant++;
    }	    
    rebalanceo(papa);    
}






template<class K,class S>
bool DiccAvl<K,S>::definido(const K& clave) const{ 
	Nodo* n = raiz;
    while (n != NULL){
    	if (n->clave == clave){
    		return true;    		
    	} else if (n->clave > clave){
    		n = n->izq;
    	} else {
    		n = n->der;
    	}
    }
    return false;  
}



template<class K,class S>
S& DiccAvl<K,S>::significado(const K& clave){
	  Nodo* aux = buscar(clave);
	  return aux->sign;
}


template<class K,class S>
typename DiccAvl<K,S>::Nodo* 
DiccAvl<K,S>::buscar(const K& clave) const {
    Nodo* x = this->raiz;
    while (x->clave != clave) {
        if (clave < x->clave)
            x = x->izq ;
        else
            x = x->der ;
        }
    return x;
}


template<class K,class S>
void DiccAvl<K,S>::borrar(const K& clave){
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
		n->clave = aux->clave;
		n->sign = aux->sign;
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
			return;
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

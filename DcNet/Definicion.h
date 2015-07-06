#ifndef DEFINICION_H
#define DEFINICION_H

#include "Pc.h"
#include "Paquete.h"
#include "../Conjunto/Conjunto.h"
#include "../Heap/Heap.h"
#include "../avl/Avl.cpp"
#include "../avl/DiccAvl.cpp"


using namespace std;
using namespace aed2;


class Definicion{ // perdida de memoria?
	public:
		Definicion();
		Definicion(Avl<Pakete>& avl, ColaPriorHeap& heap, DiccAvl< Pakete, Lista<Pc> >& dicc);
		int* pEnviados() const;
		Avl<Pakete>* xID() const;
		ColaPriorHeap* xPrior() const;
		DiccAvl< Pakete, Lista<Pc> >* caminos() const;
		void sumarUnoEnviados();

	private:
		Avl<Pakete>* xid;
		ColaPriorHeap* xprior;
		DiccAvl<  Pakete, Lista<Pc> >* p_caminos;
		int* enviados;
};

Definicion::Definicion(){
	xid = new Avl<Pakete>;
	xprior =  new ColaPriorHeap;
	p_caminos = new DiccAvl<  Pakete, Lista<Pc> >;
	enviados = new int(0);
}
/*
Definicion::Definicion(Avl<Pakete>& avl, ColaPriorHeap<Pakete>& heap, DiccAvl< Pakete, Lista<Pc> >& dicc) 
: xid(&avl), xprior(&heap), p_caminos(&dicc), enviados(0){	
}
*/



int* Definicion::pEnviados() const{
	return enviados;
}

Avl<Pakete>* Definicion::xID() const{
	return xid;
}

ColaPriorHeap*  Definicion::xPrior() const{
	return xprior;
}

DiccAvl< Pakete, Lista<Pc> >* Definicion::caminos() const{
	return p_caminos;
}

void Definicion::sumarUnoEnviados(){
	*enviados = *enviados+1;

}

#endif
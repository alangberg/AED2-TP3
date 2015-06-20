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


class Definicion{
	public:
		Definicion();
		Definicion(const Avl<Paquete>& avl, const ColaPriorHeap<Paquete>& heap, const DiccAvl< Paquete, Lista<Pc> >& dicc);
		int pEnviados() const;
		Avl<Paquete> xID() const;
		ColaPriorHeap<Paquete> xPrior() const;
		DiccAvl< Paquete, Lista<Pc> > caminos() const;

	private:
		Avl<Paquete> xid;
		ColaPriorHeap<Paquete> xprior;
		DiccAvl<  Paquete, Lista<Pc> > p_caminos;
		int enviados;
};

Definicion::Definicion(){}

Definicion::Definicion(const Avl<Paquete>& avl, const ColaPriorHeap<Paquete>& heap, const DiccAvl< Paquete, Lista<Pc> >& dicc) : xid(avl), xprior(heap), p_caminos(dicc), enviados(0){}

int Definicion::pEnviados() const{
	return enviados;
}

Avl<Paquete> Definicion::xID() const{
	return xid;
}

ColaPriorHeap<Paquete>  Definicion::xPrior() const{
	return xprior;
}

DiccAvl< Paquete, Lista<Pc> > Definicion::caminos() const{
	return p_caminos;
}



#endif
#include <iostream> 
#include "DcNet.h"

using namespace std;

DcNet::DcNet(const Red& r){ // falta terminar
    red = r;
    pc_masEnviados = r.mostrarComputadoras().DameUno();
    cant_MasEnviados = 0;
    //siguientes = 

}


void DcNet::anadirPaquete(const Paquete& p){ // deberia haber aliasing para que funcione
	Definicion actual = pc_paquetes.Significado(p.origen());
	actual.xID().insertar(p);
	actual.xPrior().Encolar(p);
	Lista<Pc> camRec;
	camRec.AgregarAtras(p.origen());
	actual.caminos().definir(p,camRec);
}

const Red DcNet::verRed() const{
	return red;
}

int DcNet::enviados(const Pc& p) const{
	return pc_paquetes.Significado(p).pEnviados();
}

Avl<Paquete> DcNet::paquetes(const Pc& p) const{
	return pc_paquetes.Significado(p).xID();
}

Pc DcNet::masEnviados() const{
	return pc_masEnviados;
}


bool DcNet::enTransito(const Paquete& p) const{
	Conjunto<Pc>::const_Iterador it = red.mostrarComputadoras().CrearIt();
	bool noEncontrado = true;
	while (noEncontrado && it.HaySiguiente()){
		Definicion sig = pc_paquetes.Significado(it.Siguiente());
		noEncontrado = !(sig.xID().pertenece(p));
		it.Avanzar();
	}
	return !noEncontrado;
}


Lista<Pc> DcNet::recorrido(const Paquete& p) const{
	Dicc<Pc,Definicion>::const_Iterador it = pc_paquetes.CrearIt();
	bool noEncontrado = true;
	Definicion actual;
	Lista<Pc> l;
	while (noEncontrado && it.HaySiguiente()){
		actual = it.SiguienteSignificado();
		if (actual.caminos().definido(p)){
			noEncontrado = false;
			l = actual.caminos().significado(p);
		}
		it.Avanzar();			
	}
	return l;
}


void DcNet::avanzarSegundo(){
	Conjunto<Pc>::const_Iterador it = red.mostrarComputadoras().CrearIt();
	Lista<Tupla> aEnviar; //Lista< tuple<Paquete, Lista<Pc>, Pc> > aEnviar;
	while (it.HaySiguiente()){
		Definicion actual = pc_paquetes.Significado(it.Siguiente());
		if (actual.xID().cardinal() != 0){
			Paquete p = actual.xPrior().Desencolar();
			Lista<Pc> l = actual.caminos().significado(p);
			actual.xID().borrar(p);
			actual.caminos().borrar(p);
			Dicc<Pc,Pc> aux = siguientes.Significado(it.Siguiente());
			Pc pct = aux.Significado(p.destino());
			if (pct != p.destino()){
				l.AgregarAtras(pct);
				Tupla tp(p,l,pct);
				aEnviar.AgregarAtras(tp);
			}			
		}
		it.Avanzar();
	}
	Lista<Tupla>::const_Iterador itP = aEnviar.CrearIt();
	while (itP.HaySiguiente()){
		Definicion actual2 = pc_paquetes.Significado(itP.Siguiente().Ter());
		actual2.xID().insertar(itP.Siguiente().Prim());
		actual2.xPrior().Encolar(itP.Siguiente().Prim());
		actual2.caminos().definir(itP.Siguiente().Prim(), itP.Siguiente().Seg());
		itP.Avanzar();
	}
}
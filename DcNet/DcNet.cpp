#include <iostream>
#include <cassert> 
#include "DcNet.h"

using namespace std;

DcNet::DcNet(){}

DcNet::DcNet(const Red& r){ 
    red = r;
    cant_MasEnviados = 0;
    pc_paquetes;
    siguientes;
    if (r.mostrarComputadoras().EsVacio()) {
    	pc_masEnviados = Pc();
    }else{
    	pc_masEnviados = r.mostrarComputadoras().DameUno();
    	Conjunto<Pc> aux = r.mostrarComputadoras();
    	Conjunto<Pc>::const_Iterador it1 = aux.CrearIt();
    	while (it1.HaySiguiente()) {
    		Pc pc1 = it1.Siguiente();
			Definicion d;
			pc_paquetes.definir(pc1.IP(), d);
    		Conjunto<Pc>::const_Iterador it2 = aux.CrearIt();
    		DiccString<Pc> sig;
    		while (it2.HaySiguiente()) {
    			Pc pc2 = it2.Siguiente();
    			if (pc1 != pc2 && !(r.caminosMinimos(pc1, pc2).EsVacio())) {
    				Pc pc3 = r.caminosMinimos(pc1, pc2).DameUno()[1];
    				sig.definir(pc2.IP(), pc3);
    			}
    			it2.Avanzar();
    		}
    		siguientes.definir(pc1.IP(), sig);
    		it1.Avanzar();
        }
    }
}


void DcNet::anadirPaquete(const Paquete& p){
	assert(red.mostrarComputadoras().Pertenece(p.origen()) && red.mostrarComputadoras().Pertenece(p.destino()) && red.existeCamino(p.origen(), p.destino()) && not enTransito(p));
	Definicion actual = *pc_paquetes.obtener(p.origen().IP());
	actual.xID()->insertar(p);
	actual.xPrior()->Encolar(p);
	Lista<Pc> camRec;
	camRec.AgregarAtras(p.origen());
	actual.caminos()->definir(p,camRec);
}

const Red DcNet::verRed() const{
	return red;
}

int DcNet::enviados(const Pc& p) {
	assert(red.mostrarComputadoras().Pertenece(p));
	return *pc_paquetes.obtener(p.IP())->pEnviados();
}

Avl<Paquete> DcNet::paquetes(const Pc& p){
	assert(red.mostrarComputadoras().Pertenece(p));
	return *pc_paquetes.obtener(p.IP())->xID();
}

Pc DcNet::masEnviados() const{
	return pc_masEnviados;
}


bool DcNet::enTransito(const Paquete& p){
	Conjunto<Pc> aux = red.mostrarComputadoras();
	Conjunto<Pc>::const_Iterador it = aux.CrearIt();
	bool noEncontrado = true;
	while (noEncontrado && it.HaySiguiente()){
		Definicion sig = *pc_paquetes.obtener(it.Siguiente().IP());
		noEncontrado = !(sig.xID()->pertenece(p));
		it.Avanzar();
	}
	return !noEncontrado;
}


Lista<Pc> DcNet::recorrido(const Paquete& p){
	assert(enTransito(p));	
	DiccString<Definicion>::Iterador it(&pc_paquetes);
	//Dicc<Pc,Definicion>::const_Iterador it = pc_paquetes.CrearIt();
	bool noEncontrado = true;
	Definicion actual;
	Lista<Pc> l;
	while (noEncontrado){
		actual = *it.valorActual();
		if (actual.caminos()->definido(p)){
			noEncontrado = false;
			l = actual.caminos()->significado(p);
		}
		it.avanzar();			
	}
	return l;
}


void DcNet::avanzarSegundo(){
	Conjunto<Pc> auxiliar = red.mostrarComputadoras();
	Conjunto<Pc>::const_Iterador it = auxiliar.CrearIt();
	Lista<Tupla> aEnviar; //Lista< tuple<Paquete, Lista<Pc>, Pc> > aEnviar;
	while (it.HaySiguiente()){
		Definicion actual = *pc_paquetes.obtener(it.Siguiente().IP());
		if (actual.xID()->cardinal() != 0){
			Paquete p = actual.xPrior()->Desencolar();
			Lista<Pc> l = actual.caminos()->significado(p);
			actual.xID()->borrar(p);
			actual.caminos()->borrar(p);
			DiccString<Pc> aux = *siguientes.obtener(it.Siguiente().IP());
			Pc pct = *aux.obtener(p.destino().IP());
			if (pct != p.destino()){
				l.AgregarAtras(pct);
				Tupla tp(p,l,pct);
				aEnviar.AgregarAtras(tp);
			}
			actual.sumarUnoEnviados();
			int cant = *actual.pEnviados();			
			if (cant_MasEnviados < cant){
				cant_MasEnviados = cant;
				pc_masEnviados = it.Siguiente();
			}
		}
		it.Avanzar();
	}
	Lista<Tupla>::const_Iterador itP = aEnviar.CrearIt();
	while (itP.HaySiguiente()){
		Definicion actual2 = *pc_paquetes.obtener(itP.Siguiente().Ter().IP());
		actual2.xID()->insertar(itP.Siguiente().Prim());
		actual2.xPrior()->Encolar(itP.Siguiente().Prim());
		actual2.caminos()->definir(itP.Siguiente().Prim(), itP.Siguiente().Seg());
		itP.Avanzar();
	}
}

DcNet& DcNet::operator=(DcNet& otro){
	pc_paquetes = otro.pc_paquetes;
	pc_masEnviados = otro.pc_masEnviados;
	cant_MasEnviados = otro.cant_MasEnviados;
	red = otro.red;
	siguientes = otro.siguientes;
}

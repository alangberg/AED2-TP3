#include <iostream> 
#include "DcNet.h"

using namespace std;

DcNet::DcNet(const Red& r){ // falta terminar
    red = r;
    masEnviados = r.mostrarComputadoras().DameUno();
    cantMasEnviados = 0;
    //siguientes = 

}


void DcNet::anadirPaquete(const Paquete& p){ // deberia haber aliasing para que funcione
	Definicion* actual = paquetes.Significado(p);
	actual.xID().insertar(p);
	actual.xPrior().Encolar(p);
	Lista<Pc> camRec;
	camRec.AgregarAtras(p.origen());
	actual.caminos().definir(p,camRec);
}

Red verRed() const{
	return red;
}

int enviados(const Pc& p) const{
	return paquetes.Significado(p).pEnviados();
}

Conjunto<Paquete> paquetes(const Pc& p) const{
	return paquetes.Significado(p).xID();
}

Pc masEnviados() const{
	return masEnviados;
}


bool enTransito(const Paquete& p) const{
	Conjunto<Pc>::Iterador it = crearIt(red.mostrarComputadoras()); // corregir
	bool noEncontrado = true;
	while (noEncontrado && HaySiguiente(it)){
		Definicion* sig = paquetes.Significado(it.Siguiente());
		noEncontrado = !(sig.xID().pertenece(p));
		it.Avanzar();
	}
	return !noEncontrado;
}



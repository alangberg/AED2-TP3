#include "Driver.h"
#include "ArbolSintactico.h"

namespace aed2 {

Driver::Driver(){
	DcNet d;
	id_paquetes = 0;  
}


Driver::~Driver() {
    // TODO
}

// TAD RED
Nat Driver::CantidadComputadoras() const {
    return d.verRed().mostrarComputadoras().Cardinal();
}

const Computadora& Driver::IesimaComputadora(const Nat i) const {
    Conjunto<Pc> aux = d.verRed().mostrarComputadoras();
    Conjunto<Pc>::const_Iterador it = aux.CrearIt();
    for (int j = 0; j < i ; j++ ){
    	it.Avanzar();
    } 
	return it.Siguiente().IP();
}
        
Nat Driver::CantidadInterfacesDe(const Computadora& c) const {
    // TODO
    return 0;

}

const Interfaz& Driver::IesimaInterfazDe(const Computadora& c, const Nat i) const{
    // TODO
    return 0;

} 

const Interfaz& Driver::IntefazUsada(const Computadora& c1, const Computadora& c2) const {
    // TODO
    return 0;

}

bool Driver::conectadas(const Computadora& c1, const Computadora& c2) const {
    // TODO
    return 0;
}

// TAD DCNET
void Driver::AgregarComputadora(const Computadora& ip, const Conjunto<Interfaz>& ci) {
    Pc izipc(ip, ci);
    Red r = d.verRed();
    r.agregarCompu(izipc);
    DcNet aux(r);
    d = aux;
}
        
void Driver::Conectar(const Computadora& c1, const Interfaz& i1, const Computadora& c2, const Interfaz& i2) {
    // TODO
}
	
	
Nat Driver::CantidadNodosRecorridosPor(const Pakete& p) const {
    // TODO
    return 0;
}

const Computadora& Driver::IesimoNodoRecorridoPor(const Pakete& p) const {
    // TODO
}

Nat Driver::CantidadEnviadosPor(const Computadora& c) const {
    // TODO
    return 0;
}
	
Nat Driver::CantidadEnEsperaEn(const Computadora& c) const {
    // TODO
    return 0;
}

const Pakete& Driver::IesimoEnEsperaEn(const Computadora& c) const {
    // TODO
    return 0;
}

void Driver::CrearPaquete(const Computadora& origen, const Computadora& destino, Nat prioridad) {
    // TODO
}
		
void Driver::AvanzarSegundo() {
    // TODO
}
		
const Computadora& Driver::laQueMasEnvio() const {
    // TODO	
    return 0;
}

const Computadora& Driver::origen(const Pakete& p) const {
    // TODO	
    return 0;
} 

const Computadora& Driver::destino(const Pakete& p) const { 
    // TODO	
    return 0;
}

Nat Driver::prioridad(const Pakete& p) const { 
    // TODO	
    return 0;
}
		


} // namespace aed2


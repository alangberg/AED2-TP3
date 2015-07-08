#include "Driver.h"
namespace aed2 {

Driver::Driver(){
	DcNet d;
	id_paquetes = 0;
    Conjunto<Pakete> c;  
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
    Pc a = it.Siguiente();
	return a.IP();
}
        
Nat Driver::CantidadInterfacesDe(const Computadora& c) const {
    Conjunto<Pc> aux = d.verRed().mostrarComputadoras();
    Conjunto<Pc>::const_Iterador it = aux.CrearIt();
    while( c != it.Siguiente().IP() ){
        it.Avanzar();
    }
    Pc pc1 = it.Siguiente();
    return pc1.Interfaces().Cardinal();

}

const Interfaz& Driver::IesimaInterfazDe(const Computadora& c, const Nat i) const{
    Conjunto<Pc> aux = d.verRed().mostrarComputadoras();
    Conjunto<Pc>::const_Iterador it = aux.CrearIt();
    while( c != it.Siguiente().IP() ){
        it.Avanzar();
    }
    Pc a = it.Siguiente();
    Conjunto<Interfaz> aux2 = a.Interfaces();
    Conjunto<Interfaz>::const_Iterador it2 = aux2.CrearIt(); 
    for (int j = 0; j < i ; j++ ){
        it2.Avanzar();
    }
    Interfaz *inter = new Interfaz(it2.Siguiente());
    return *inter;
} 

const Interfaz& Driver::IntefazUsada(const Computadora& c1, const Computadora& c2) const {
    Conjunto<Pc> aux = d.verRed().mostrarComputadoras();
    Conjunto<Pc>::const_Iterador it = aux.CrearIt();
    while( c1 != it.Siguiente().IP() ){
        it.Avanzar();
    }
    Pc pc1 = it.Siguiente();
    Conjunto<Pc>::const_Iterador it2 = aux.CrearIt();
    while (c2 != it2.Siguiente().IP() ){
        it2.Avanzar();
    }
    Pc pc2 = it2.Siguiente();
    Interfaz* res = new Interfaz(d.verRed().interfazQueUsan(pc1, pc2));
    return *res;
}

bool Driver::conectadas(const Computadora& c1, const Computadora& c2) const {
    Conjunto<Pc> aux = d.verRed().mostrarComputadoras();
    Conjunto<Pc>::const_Iterador it = aux.CrearIt();
    while( c1 != it.Siguiente().IP() ){
    	it.Avanzar();
    }
    Pc pc1 = it.Siguiente();
    Conjunto<Pc>::const_Iterador it2 = aux.CrearIt();
    while (c2 != it2.Siguiente().IP() ){
    	it2.Avanzar();
    }
    Pc pc2 = it2.Siguiente();
    return d.verRed().estanConectadas(pc1, pc2);
}

// TAD DCNET
void Driver::AgregarComputadora(const Computadora& ip, const Conj<Interfaz>& ci) {
    Conj<Interfaz>::const_Iterador it = ci.CrearIt();
    Conjunto<Interfaz> con;
    while (it.HaySiguiente()){
        con.AgregarRapido(it.Siguiente());
        it.Avanzar();
    }
    Pc izipc(ip, con);
    Red r = d.verRed();
    r.agregarCompu(izipc);
    DcNet aux(r);
    d = aux;
}
        
void Driver::Conectar(const Computadora& c1, const Interfaz& i1, const Computadora& c2, const Interfaz& i2) {
    Conjunto<Pc> aux = d.verRed().mostrarComputadoras();
    Conjunto<Pc>::const_Iterador it = aux.CrearIt();
    while( c1 != it.Siguiente().IP() ){
    	it.Avanzar();
    }
    Pc pc1 = it.Siguiente();
    Conjunto<Pc>::const_Iterador it2 = aux.CrearIt();
    while (c2 != it2.Siguiente().IP() ){
    	it2.Avanzar();
    }
    Pc pc2 = it2.Siguiente();
    Red r = d.verRed();
    r.conectar(pc1, i1, pc2, i2);
    DcNet nuevo(r);
    d = nuevo;
}
	
	
Nat Driver::CantidadNodosRecorridosPor(const Paquete& p)  {
    Conjunto<Pakete>::const_Iterador it = c.CrearIt();
    while( p != it.Siguiente().ID() ){
        it.Avanzar();
    }
    Pakete aux = it.Siguiente();
    return d.recorrido(aux).Longitud();
}

const Computadora& Driver::IesimoNodoRecorridoPor(const Paquete& p, const Nat i) {
    Conjunto<Pakete>::const_Iterador it = c.CrearIt();
    while( p != it.Siguiente().ID() ){
        it.Avanzar();
    }
    Pakete aux = it.Siguiente();
    Pc a = d.recorrido(aux)[i];
    return a.IP();
}

Nat Driver::CantidadEnviadosPor(const Computadora& c)  {
    Conjunto<Pc> aux = d.verRed().mostrarComputadoras();
    Conjunto<Pc>::const_Iterador it = aux.CrearIt();
    while( c != it.Siguiente().IP() ){
        it.Avanzar();
    }
    Pc pc1 = it.Siguiente();
    return d.enviados(pc1);
}
	
Nat Driver::CantidadEnEsperaEn(const Computadora& c)  {
    Conjunto<Pc> aux = d.verRed().mostrarComputadoras();
    Conjunto<Pc>::const_Iterador it = aux.CrearIt();
    while( c != it.Siguiente().IP() ){
        it.Avanzar();
    }
    Pc pc1 = it.Siguiente();
    return d.paquetes(pc1).cardinal();
}

const Paquete& Driver::IesimoEnEsperaEn(const Computadora& c1, const Nat i)  {
    Conjunto<Pc> aux = d.verRed().mostrarComputadoras();
    Conjunto<Pc>::const_Iterador it = aux.CrearIt();
    while( c1 != it.Siguiente().IP() ){
        it.Avanzar();
    }
    Pc pc1 = it.Siguiente();
    Avl<Pakete> PaketesEn = d.paquetes(pc1);
    ColaPriorHeap cola;
    Conjunto<Pakete>::const_Iterador it2 = c.CrearIt();
    while (it2.HaySiguiente()){
        if ( PaketesEn.pertenece(it2.Siguiente()) ){
            cola.Encolar(it2.Siguiente());    
        } 
        it2.Avanzar(); 
    }
    for (int j = 0; j < i ; j++){
        cola.Desencolar();
    }
    Pakete p = cola.Desencolar();
    return p.ID();
}

void Driver::CrearPaquete(const Computadora& origen, const Computadora& destino, Nat prioridad) {
    Conjunto<Pc> aux = d.verRed().mostrarComputadoras();
    Conjunto<Pc>::const_Iterador it = aux.CrearIt();
    while( origen != it.Siguiente().IP() ){
        it.Avanzar();
    }
    Pc pc1 = it.Siguiente();
    Conjunto<Pc>::const_Iterador it2 = aux.CrearIt();
    while ( destino!= it2.Siguiente().IP() ){
        it2.Avanzar();
    }
    Pc pc2 = it2.Siguiente();
    Pakete p(id_paquetes, prioridad, pc1, pc2);
    d.anadirPaquete(p);
    id_paquetes++;
    c.AgregarRapido(p);
}
		
void Driver::AvanzarSegundo() {
    d.avanzarSegundo();
}
		
const Computadora& Driver::laQueMasEnvio() {
    Computadora* res = new Computadora(d.masEnviados().IP());
    return *res;
}

const Computadora& Driver::origen(const Paquete& p) const {
    Conjunto<Pakete>::const_Iterador it = c.CrearIt();
    while( p != it.Siguiente().ID() ){
        it.Avanzar();
    }
    Pakete aux = it.Siguiente();
    return aux.origen().IP();
} 

const Computadora& Driver::destino(const Paquete& p) const { 
    Conjunto<Pakete>::const_Iterador it = c.CrearIt();
    while( p != it.Siguiente().ID() ){
        it.Avanzar();
    }
    Pakete aux = it.Siguiente();
    return aux.destino().IP();	
}

Nat Driver::prioridad(const Paquete& p) const { 
    Conjunto<Pakete>::const_Iterador it = c.CrearIt();
    while( p != it.Siguiente().ID() ){
        it.Avanzar();
    }
    Pakete aux = it.Siguiente();
    return aux.prioridad();
}
		


} // namespace aed2


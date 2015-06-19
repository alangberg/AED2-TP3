/**
 * Modulo Paquete
 * Algoritmos y Estructuras de Datos 2
 */
#ifndef PAQUETE_H
#define PAQUETE_H
#include "Pc.h"
#include "../Conjunto/Conjunto.h"
#include "TiposSecundarios.h"
using namespace std;
using namespace aed2;



namespace aed2
{

class Paquete // pasar pc por referencia ???? revisar el operador =
{
	public:
		Paquete();
		Paquete(Id&, Prioridad&, Pc&, Pc&);
		const Id& ID() const;
		const Prioridad& prioridad() const;
		const Pc& origen() const;
		const Pc& destino() const;
		bool operator<(const Paquete& otro) const;
		Paquete& operator=(const Paquete& otro);
		void mostrar(ostream& o) const;
    private:
        Id id_paq;
        Prioridad prior_paq;
        Pc pc_origen;
        Pc pc_destino;
};

Paquete::Paquete(){}

Paquete::Paquete(Id& i, Prioridad& p, Pc& o, Pc& d):
	id_paq(i), prior_paq(p), pc_origen(o), pc_destino(d){}



const Id& Paquete::ID() const{
	return id_paq;
} 

const Prioridad& Paquete::prioridad() const{
	return prior_paq;
} 

const Pc& Paquete::origen() const{
	return pc_origen;
} 

const Pc& Paquete::destino() const{
	return pc_destino;
} 


void Paquete::mostrar(ostream& o) const{
    o << "[" << id_paq << ";" << prior_paq << ";";
   	pc_origen.mostrar(o);
    o << ";";
    pc_destino.mostrar(o);
    o << "]" <<endl;
}


Paquete& Paquete::operator=(const Paquete& otro) {
	id_paq = otro.id_paq;
    prior_paq = otro.prior_paq;
    pc_origen = otro.pc_origen;
    pc_destino = otro.pc_destino;
    return *this;
}


};




#endif // PAQUETE_H

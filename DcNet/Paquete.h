/**
 * Modulo Pakete
 * Algoritmos y Estructuras de Datos 2
 */
#ifndef Pakete_H
#define Pakete_H
#include "Pc.h"
#include "../Conjunto/Conjunto.h"
#include "TiposSecundarios.h"
using namespace std;
using namespace aed2;



namespace aed2
{

class Pakete // pasar pc por referencia ???? revisar el operador =
{
	public:
		Pakete();
		Pakete(Id&, Prioridad&, Pc&, Pc&);
		const Id& ID() const;
		const Prioridad& prioridad() const;
		const Pc& origen() const;
		const Pc& destino() const;
		bool operator<(const Pakete& otro) const; // corregir
		bool operator>(const Pakete& otro) const; // corregir
		bool operator==(const Pakete& otro) const; // corregir
		bool operator!=(const Pakete& otro) const; // corregir		
		Pakete& operator=(const Pakete& otro);
    private:
        Id id_paq;
        Prioridad prior_paq;
        Pc pc_origen;
        Pc pc_destino;
};

Pakete::Pakete(){}

Pakete::Pakete(Id& i, Prioridad& p, Pc& o, Pc& d):
	id_paq(i), prior_paq(p), pc_origen(o), pc_destino(d){}



const Id& Pakete::ID() const{
	return id_paq;
} 

const Prioridad& Pakete::prioridad() const{
	return prior_paq;
} 

const Pc& Pakete::origen() const{
	return pc_origen;
} 

const Pc& Pakete::destino() const{
	return pc_destino;
} 


Pakete& Pakete::operator=(const Pakete& otro) {
	id_paq = otro.id_paq;
    prior_paq = otro.prior_paq;
    pc_origen = otro.pc_origen;
    pc_destino = otro.pc_destino;
    return *this;
}

bool Pakete::operator<(const Pakete& otro) const{
	return id_paq < otro.id_paq;
}

bool Pakete::operator>(const Pakete& otro) const{
	return id_paq > otro.id_paq;
}

bool Pakete::operator==(const Pakete& otro) const{
	return id_paq == otro.id_paq;
}

bool Pakete::operator!=(const Pakete& otro) const{
	return id_paq != otro.id_paq;
}


ostream& operator << (ostream& os, const Pakete& p){
	os << "{" << p.ID() << ";" << p.prioridad() << ";" << p.origen() << ";" << p.destino() << "}" <<endl;
	return os;
}

};



#endif // Pakete_H

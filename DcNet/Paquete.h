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

class Paquete // pasar pc por referencia ????
{
	public:
		Paquete(Id, Prioridad, Pc, Pc);
		Id ID() const;
		Prioridad prioridad() const;
		Pc origen() const;
		Pc destino() const;
		bool operator<(const Paquete& otro) const;
    private:
        Id id_paq;
        Prioridad prior_paq;
        Pc pc_origen;
        Pc pc_destino;
};


Paquete::Paquete(Id i, Prioridad p, Pc o, Pc d){
	id_paq = i;
	prior_paq = p;
	pc_origen = o;
	pc_destino = d;
}


Id Paquete::ID() const{
	return id_paq;
} 

Prioridad Paquete::prioridad() const{
	return prior_paq;
} 

Pc Paquete::origen() const{
	return pc_origen;
} 

Pc Paquete::destino() const{
	return pc_destino;
} 

bool Paquete::operator<(const Paquete& otro) const{
	return prior_paq > otro.prior_paq;
}






#endif // PAQUETE_H

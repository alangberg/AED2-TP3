#ifndef PAQUETE_H
#define PAQUETE_H
#include "Pc.h"
using namespace std;

class Paquete // CAMBIAR: pasar pc por referencia
{
	public:
		Paquete(int, int, Pc&, Pc&);
		unsigned int ID() const;
		int prioridad() const;
		Pc origen() const;
		Pc destino() const;
		bool operator<(const Paquete& otro) const;
    private:
        unsigned int id_paq;
        int prior_paq;
        Pc* pc_origen;
        Pc* pc_destino;
};





Paquete::Paquete(int i, int p, Pc& o, Pc& d){
	id_paq = i;
	prior_paq = p;
	*pc_origen = o;
	*pc_destino = d;
}


unsigned int Paquete::ID() const{
	return id_paq;
} 

int Paquete::prioridad() const{
	return prior_paq;
} 

Pc Paquete::origen() const{
	return *pc_origen;
} 

Pc Paquete::destino() const{
	return *pc_destino;
} 

bool Paquete::operator<(const Paquete& otro) const{
	return prior_paq > otro.prior_paq;
}






#endif // PAQUETE_H
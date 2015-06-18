#ifndef RED_H_INCLUDED
#define RED_H_INCLUDED

#include ../Conjunto/"Conjunto.h"


#include <ostream>

namespace aed2;


template <typename T>
class Red
{
	public:
		/// Crea una red vacía. (Operación ArrancarRed())
		Red();
		/// Crea por copia una Red (operación Copiar())
		Red(const Red& otro);
		/// Destruye el conjunto, incluyendo los T alojados
		~Red();
		/// Operacion de asignacion
		Red<T>& operator=(const Red<T>& otra);
		/// Operaciones básicas
		Conjunto<Pc> mostrarComputadoras();
		void agregarCompu(const Pc& p);
		void conectar(const Pc& p1, const Interfaz i1, const Pc& p2, const Interfaz i2);
		bool estanConectadas(const Pc& p1, const Pc& p2);
		Interfaz interfazQueUsan(const Pc& p1, const Pc& p2);
		Conjunto<Pc> conectadoCon(const Pc& p1);
		bool interfazUsada(const Pc& p1, const Interfaz i1);
		Conjunto<Lista<Pc>> caminosMinimos(const Pc& p1, const Pc& p2);
		bool existeCamino(const Pc& p1, const Pc& p2);

	private:
        Dicc<Ip, Conjunto<Interfaz>> interfaces;
        Dicc<Ip, Conjunto<Ip>> vecinos;
        Lista<> conexiones; //FALTA COMPLETAR TUPLA PC,INTERFAZ,PC,INTERFAZ!!!!

};


#endif
/**
 * Modulo Diccionario Lineal
 * Algoritmos y Estructuras de Datos 2
 */

#ifndef AED2_DICC_H_INCLUDED
#define	AED2_DICC_H_INCLUDED

#include "Lista.h"

#include <ostream>

/* Descomentar este flag para habilitar los chequeos internos de PRE
 * OJO que invalida las complejidades exportadas de algunas funciones
 */
#define DEBUG 1

namespace aed2
{

template<class K,class S>
class Dicc
{
	public:

		// Forward declarations. Las definiciones estan mas abajo.
		class Iterador;
		class const_Iterador;

		Dicc();

		Dicc(const Dicc<K,S>& otro);

		Dicc<K,S>& operator = (const Dicc<K,S>& otro);

		Iterador Definir(const K& clave, const S& significado);
		Iterador DefinirRapido(const K& clave, const S& significado);

		bool Definido(const K& clave) const;

		const S& Significado(const K& clave) const;
		S& Significado(const K& clave);

		void Borrar(const K& clave);

		Nat CantClaves() const;

		Iterador CrearIt();
		const_Iterador CrearIt() const;

		/** 
		 * Estas funciones son utiles para saber si algo esta definido
		 * y ver cual es su signficado, sin recorrer dos veces.
		 * Si la clave no esta definida, Iterador.HaySiguiente() 
		 * retorna falso. Si la clave esta definida, Iterador.Siguiente()
		 * retorna el elemento buscado.
		 */
		Iterador Buscar(const K&);
		const_Iterador Buscar(const K&) const;

		struct Elem
		{
			Elem(const K& c, S& s)
				: clave(c), significado(s)
			{}

			const K& clave;
			S& significado;
		};

		struct const_Elem
		{
			const_Elem(const K& c, const S& s)
				: clave(c), significado(s)
			{}

			const K& clave;
			const S& significado;

			// Para sacar esto de aca, necesitariamos definir rasgos y otras
			// yerbas. Lamentablemente, sino C++ no reconoce bien los tipos.
			friend std::ostream& operator << (std::ostream& os, const const_Elem& e)
			{
				os << e.clave << ":" << e.significado;
				return os;
			}
		};

		class Iterador
		{
			public:

				Iterador();

				Iterador(const typename Dicc<K, S>::Iterador& otro);

				Iterador& operator=(const typename Dicc<K, S>::Iterador& otro);

				bool operator==(const typename Dicc<K,S>::Iterador&) const;

				bool HaySiguiente() const;
				bool HayAnterior() const;

				Elem Siguiente() const;
				Elem Anterior() const;

				
				K& SiguienteClave() const;
				S& SiguienteSignificado() const;
				
				const K& AnteriorClave() const;
				const S& AnteriorSignificado() const;
				

				void Avanzar();
				void Retroceder();

				void EliminarSiguiente();
				void EliminarAnterior();

			private:

				Iterador(Dicc<K,S>* d);

				friend typename Dicc<K,S>::Iterador Dicc<K,S>::CrearIt();

				typename Lista<K>::Iterador itC;
				typename Lista<S>::Iterador itS;

				friend class Dicc<K, S>::const_Iterador;
		}; // class Iterador

		class const_Iterador
		{
			public:

				const_Iterador();

				const_Iterador(const typename Dicc<K,S>::Iterador& otro);

				const_Iterador(const typename Dicc<K, S>::const_Iterador& otro);

				const_Iterador& operator=(const typename Dicc<K, S>::const_Iterador& otro);

				bool operator==(const typename Dicc<K,S>::const_Iterador&) const;

				bool HaySiguiente() const;
				bool HayAnterior() const;
				
				const K& SiguienteClave() const;
				const S& SiguienteSignificado() const;
				
				const K& AnteriorClave() const;
				const S& AnteriorSignificado() const;
				
				const_Elem Siguiente() const;
				const_Elem Anterior() const;
				void Avanzar();
				void Retroceder();
			private:
				const_Iterador(const Dicc<K,S>* d);
				friend typename Dicc<K,S>::const_Iterador Dicc<K,S>::CrearIt() const;
				typename Lista<K>::const_Iterador itC;
				typename Lista<S>::const_Iterador itS;
		}; // class const_Iterador

	private:

		Lista<K> claves_;

		Lista<S> significados_;

}; // class Dicc

/**
 * Operador ostream de Dicc
 */
template<class K, class S>
std::ostream& operator << (std::ostream& os, const Dicc<K,S>& d);

/**
 * Operador comparacion
 */
template<class K, class S>
bool operator == (const Dicc<K,S>& d1, const Dicc<K,S>& d2);

	// ---------------------------------------------------------
	//  class Dicc
	// ---------------------------------------------------------

template<class K, class S>
Dicc<K,S>::Dicc()
{}

template<class K, class S>
Dicc<K,S>::Dicc(const Dicc<K,S>& otro)
	: claves_(otro.claves_), significados_(otro.significados_)
{}

template<class K, class S>
Dicc<K,S>& Dicc<K,S>::operator=(const Dicc<K,S>& otro)
{
	claves_ = otro.claves_;
	significados_ = otro.significados_;

	return *this;
}

template<class K, class S>
typename Dicc<K,S>::Iterador Dicc<K,S>::Definir(const K& clave, const S& significado)
{
	Iterador it = Buscar(clave);

	// Si la clave existe, cambio el significado
	if(it.HaySiguiente()) {
		it.Siguiente().significado = significado;
	// Si la clave no existe, agrego la definicion
	} else {
		it = DefinirRapido(clave, significado);
	}

	return it;
}

template<class K, class S>
typename Dicc<K,S>::Iterador Dicc<K,S>::DefinirRapido(const K& clave, const S& significado)
{
	// Me aseguro que se cumpla la precondicion
	// OJO que esto invalida la complejidad
	#ifdef DEBUG
	assert( !Definido(clave) );
	#endif

	claves_.AgregarAdelante(clave);
	significados_.AgregarAdelante(significado);

	return CrearIt();
}

template<class K, class S>
bool Dicc<K,S>::Definido(const K& clave) const
{
	return Buscar(clave).HaySiguiente();
}

template<class K, class S>
const S& Dicc<K,S>::Significado(const K& clave)const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert( Definido(clave) );
	#endif

	return Buscar(clave).Siguiente().significado;
}

template<class K, class S>
S& Dicc<K,S>::Significado(const K& clave)
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert( Definido(clave) );
	#endif

	return Buscar(clave).Siguiente().significado;
}

template<class K, class S>
void Dicc<K,S>::Borrar(const K& clave)
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert( Definido(clave) );
	#endif

	Buscar(clave).EliminarSiguiente();
}

template<class K, class S>
Nat Dicc<K,S>::CantClaves() const
{
	return claves_.Longitud();
}

template<class K, class S>
typename Dicc<K,S>::Iterador Dicc<K,S>::CrearIt()
{
	return Iterador(this);
}

template<class K, class S>
typename Dicc<K,S>::const_Iterador Dicc<K,S>::CrearIt() const
{
	return const_Iterador(this);
}

	// ---------------------------------------------------------
	//  class Dicc::Iterador
	// ---------------------------------------------------------

template<class K, class S>
Dicc<K,S>::Iterador::Iterador()
{}

template<class K, class S>
Dicc<K,S>::Iterador::Iterador(const typename Dicc<K, S>::Iterador& otro)
	: itC( otro.itC ), itS( otro.itS )
{}

template<class K, class S>
typename Dicc<K,S>::Iterador& Dicc<K,S>::Iterador::operator = (const typename Dicc<K, S>::Iterador& otro)
{
	itC = otro.itC;
	itS = otro.itS;

	return *this;
}

template<class K, class S>
bool Dicc<K,S>::Iterador::HaySiguiente() const
{
	return itC.HaySiguiente();
}

template<class K, class S>
bool Dicc<K,S>::Iterador::HayAnterior() const
{
	return itC.HayAnterior();
}


template<class K, class S>
K& Dicc<K,S>::Iterador::SiguienteClave() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	return itC.Siguiente();
}

template<class K, class S>
S& Dicc<K,S>::Iterador::SiguienteSignificado() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	return itS.Siguiente();
}


template<class K, class S>
typename Dicc<K,S>::Elem Dicc<K,S>::Iterador::Siguiente() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	return Elem(itC.Siguiente(), itS.Siguiente());
}


template<class K, class S>
const K& Dicc<K,S>::Iterador::AnteriorClave() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	return itC.Anterior();
}

template<class K, class S>
const S& Dicc<K,S>::Iterador::AnteriorSignificado() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HayAnterior());
	#endif
	
	return itS.Anterior();
}


template<class K, class S>
typename Dicc<K,S>::Elem Dicc<K,S>::Iterador::Anterior() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	return Elem(itC.Anterior(), itS.Anterior());
}

template<class K, class S>
void Dicc<K,S>::Iterador::Avanzar()
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	itC.Avanzar();
	itS.Avanzar();
}

template<class K, class S>
void Dicc<K,S>::Iterador::Retroceder()
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	itC.Retroceder();
	itS.Retroceder();
}

template<class K, class S>
Dicc<K,S>::Iterador::Iterador(Dicc<K,S>* d)
	: itC( d->claves_.CrearIt() ), itS( d->significados_.CrearIt() )
{}

template<class K, class S>
void Dicc<K,S>::Iterador::EliminarSiguiente()
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif
	
	itC.EliminarSiguiente();
	itS.EliminarSiguiente();
}

template<class K, class S>
void Dicc<K,S>::Iterador::EliminarAnterior()
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	itC.EliminarAnterior();
	itS.EliminarAnterior();
}

	// ---------------------------------------------------------
	//  class Dicc::const_Iterador
	// ---------------------------------------------------------

template<class K, class S>
Dicc<K,S>::const_Iterador::const_Iterador()
{}

template<class K, class S>
Dicc<K,S>::const_Iterador::const_Iterador(const typename Dicc<K,S>::Iterador& otro)
	: itC( otro.itC ), itS( otro.itS )
{}

template<class K, class S>
Dicc<K,S>::const_Iterador::const_Iterador(const typename Dicc<K, S>::const_Iterador& otro)
	: itC( otro.itC ), itS( otro.itS )
{}

template<class K, class S>
typename Dicc<K,S>::const_Iterador& Dicc<K,S>::const_Iterador::operator = (const typename Dicc<K, S>::const_Iterador& otro)
{
	itC = otro.itC;
	itS = otro.itS;

	return *this;
}

template<class K, class S>
bool Dicc<K,S>::const_Iterador::HaySiguiente() const
{
	return itC.HaySiguiente();
}

template<class K, class S>
bool Dicc<K,S>::const_Iterador::HayAnterior() const
{
return itC.HayAnterior();
}


template<class K, class S>
const K& Dicc<K,S>::const_Iterador::SiguienteClave() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	return itC.Siguiente();
}

template<class K, class S>
const S& Dicc<K,S>::const_Iterador::SiguienteSignificado() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	return itS.Siguiente();
}


template<class K, class S>
typename Dicc<K,S>::const_Elem Dicc<K,S>::const_Iterador::Siguiente() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	return const_Elem(itC.Siguiente(), itS.Siguiente());
}


template<class K, class S>
const K& Dicc<K,S>::const_Iterador::AnteriorClave() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	return itC.Anterior();
}

template<class K, class S>
const S& Dicc<K,S>::const_Iterador::AnteriorSignificado() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	return itS.Anterior();
}


template<class K, class S>
typename Dicc<K,S>::const_Elem Dicc<K,S>::const_Iterador::Anterior() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	return const_Elem(itC.Anterior(), itS.Anterior());
}

template<class K, class S>
void Dicc<K,S>::const_Iterador::Avanzar()
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	itC.Avanzar();
	itS.Avanzar();
}

template<class K, class S>
void Dicc<K,S>::const_Iterador::Retroceder()
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	itC.Retroceder();
	itS.Retroceder();
}

template<class K, class S>
Dicc<K,S>::const_Iterador::const_Iterador(const Dicc<K,S>* d)
	: itC(d->claves_.CrearIt()), itS(d->significados_.CrearIt())
{}

template<class K, class S>
bool Dicc<K,S>::const_Iterador::operator == (const typename Dicc<K,S>::const_Iterador& otro) const
{
	return itC == otro.itC && itS == otro.itS;
}

template<class K, class S>
bool Dicc<K,S>::Iterador::operator==(const typename Dicc<K,S>::Iterador& otro) const
{
	return itC == otro.itC && itS == otro.itS;
}

	// ---------------------------------------------------------
	//  funciones auxiliares
	// ---------------------------------------------------------

template<class K, class S>
typename Dicc<K,S>::Iterador Dicc<K,S>::Buscar(const K& clave)
{
	typename Dicc<K,S>::Iterador it = CrearIt();

	while(it.HaySiguiente() && it.Siguiente().clave != clave)
	{
		it.Avanzar();
	}

	return it;
}

template<class K, class S>
typename Dicc<K,S>::const_Iterador Dicc<K,S>::Buscar(const K& clave) const
{
	typename Dicc<K,S>::const_Iterador it = CrearIt();

	while(it.HaySiguiente() && !(it.Siguiente().clave == clave))
	{
		it.Avanzar();
	}

	return it;
}

template<class K, class S>
std::ostream& operator<<(std::ostream& os, const Dicc<K,S>& d)
{
	return Mostrar(os, d, '{', '}');
}

template<class K, class S>
bool operator == (const Dicc<K,S>& d1, const Dicc<K,S>& d2)
{
	bool retval = d1.CantClaves() == d2.CantClaves();

	typename Dicc<K,S>::const_Iterador it1 = d1.CrearIt();

	while(retval and it1.HaySiguiente())
	{
		typename Dicc<K,S>::const_Iterador it2 = d2.Buscar(it1.Siguiente().clave);

		retval = it2.HaySiguiente() and it1.Siguiente().significado == it2.Siguiente().significado;

		it1.Avanzar();
	}

	return retval;
}

} // namespace aed2

#endif	//AED2_DICC_H_INCLUDED

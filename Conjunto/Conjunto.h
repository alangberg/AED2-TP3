/**
 * Modulo Conjunto Lineal
 * Algoritmos y Estructuras de Datos 2
 */

#ifndef AED2_CONJUNTO_H_INCLUDED
#define	AED2_CONJUNTO_H_INCLUDED

#include "../driver-test-cpp/aed2/Dicc.h"

#include <ostream>

/* Descomentar este flag para habilitar los chequeos internos de PRE
 * OJO que invalida las complejidades exportadas de algunas funciones
 */
#define DEBUG 1

namespace aed2
{

template <typename T>
class Conjunto
{
	public:

		// Forward declarations. Las definiciones estan mas abajo.
		class Iterador;
		class const_Iterador;

		Conjunto();

		Conjunto(const Conjunto<T>& otro);

		Conjunto<T>& operator = (const Conjunto<T>& otro);

		Iterador Agregar(const T& elemento);
		Iterador AgregarRapido(const T& elemento);

		bool Pertenece(const T& elemento) const;
		bool EsVacio() const;

		void Eliminar(const T& elemento);

		Nat Cardinal() const;

		const T& DameUno() const;
		void SinUno();
		void Unir(const Conjunto<T>& c);

		Iterador CrearIt();
		const_Iterador CrearIt() const;
		


		class Iterador
		{
			public:

				Iterador();

				Iterador(const typename Conjunto<T>::Iterador& otro);

				Iterador& operator=(const typename Conjunto<T>::Iterador& otro);

				bool operator==(const typename Conjunto<T>::Iterador&) const;

				bool HaySiguiente() const;
				bool HayAnterior() const;

				T& Siguiente() const;
				T& Anterior() const;

				void Avanzar();
				void Retroceder();

				void EliminarSiguiente();
				void EliminarAnterior();

			private:

				Iterador(Conjunto<T>* c): itC( c->dic.CrearIt() ){}

				friend typename Conjunto<T>::Iterador Conjunto<T>::CrearIt();

				typename Dicc<T,bool>::Iterador itC;

				friend class Conjunto<T>::const_Iterador;
		}; // class Iterador

	class const_Iterador
		{
			public:

				const_Iterador();

				const_Iterador(const typename Conjunto<T>::Iterador& otro);

				const_Iterador(const typename Conjunto<T>::const_Iterador& otro);

				const_Iterador& operator=(const typename Conjunto<T>::const_Iterador& otro);

				bool operator==(const typename Conjunto<T>::const_Iterador&) const;

				bool HaySiguiente() const;
				bool HayAnterior() const;
			
				const T& Siguiente() const;
				const T& Anterior() const;
				
				void Avanzar();
				void Retroceder();

			private:

				const_Iterador(const Conjunto<T>* c): itC( c->dic.CrearIt() ){}

				friend typename Conjunto<T>::const_Iterador Conjunto<T>::CrearIt() const;

				typename Dicc<T,bool>::const_Iterador itC;

				
		}; // class const_Iterador

	private:
		
		Dicc<T,bool> dic;

}; // class Conjunto

/**
 * Operador ostream de Conjunto
 */
template<class T>
std::ostream& operator << (std::ostream& os, const Conjunto<T>& c);

/**
 * Operador comparacion
 */
template<class T>
bool operator == (const Conjunto<T>& d1, const Conjunto<T>& d2);

	// ---------------------------------------------------------
	//  class Conjunto
	// ---------------------------------------------------------

template <typename T>
Conjunto<T>::Conjunto()
{}

template <typename T>
Conjunto<T>::Conjunto(const Conjunto<T>& otro)
	: dic(otro.dic)
{}

template <typename T>
Conjunto<T>& Conjunto<T>::operator=(const Conjunto<T>& otro)
{
	dic = otro.dic;

	return *this;
}

template <typename T>
typename Conjunto<T>::Iterador Conjunto<T>::Agregar(const T& elemento)
{
	dic.Definir(elemento, true);
	Iterador it = CrearIt();
	while (it.Siguiente() != elemento){
		it.Avanzar();
	}
	return it;
}

template <typename T>
typename Conjunto<T>::Iterador Conjunto<T>::AgregarRapido(const T& elemento)
{
	dic.DefinirRapido(elemento, true);
	return CrearIt();
}

template <typename T>
bool Conjunto<T>::Pertenece(const T& elemento) const
{
	return dic.Definido(elemento);
}

template <typename T>
bool Conjunto<T>::EsVacio() const
{
	return dic.CantClaves() == 0;
}

template <typename T>
void Conjunto<T>::Eliminar(const T& elemento)
{
	if(dic.Definido(elemento)){
		dic.Borrar(elemento);
	}
}

template <typename T>
Nat Conjunto<T>::Cardinal() const
{
	return dic.CantClaves();
}

template <typename T>
const T& Conjunto<T>::DameUno() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(Cardinal() != 0);
	#endif
	const_Iterador it = CrearIt();
	return it.Siguiente();	
}

template <typename T>
void Conjunto<T>::SinUno()
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(Cardinal() != 0);
	#endif
	Iterador it = CrearIt();
	it.EliminarSiguiente();
}

template <typename T>
void Conjunto<T>::Unir(const Conjunto<T>& c)
{
	const_Iterador it = c.CrearIt();
	while (it.HaySiguiente()) {
		if (! Pertenece(it.Siguiente()) ) {
			AgregarRapido(it.Siguiente());
		}
		it.Avanzar();
	}
}

template <typename T>
typename Conjunto<T>::Iterador Conjunto<T>::CrearIt()
{
	return Iterador(this);
}

template <typename T>
typename Conjunto<T>::const_Iterador Conjunto<T>::CrearIt() const
{
	return const_Iterador(this);
}

	// ---------------------------------------------------------
	//  class Conjunto::Iterador
	// ---------------------------------------------------------

template <typename T>
Conjunto<T>::Iterador::Iterador()
{}

template <typename T>
Conjunto<T>::Iterador::Iterador(const typename Conjunto<T>::Iterador& otro)
	: itC( otro.itC )
{}

template <typename T>
typename Conjunto<T>::Iterador& Conjunto<T>::Iterador::operator = (const typename Conjunto<T>::Iterador& otro)
{
	itC = otro.itC;

	return *this;
}

template <typename T>
bool Conjunto<T>::Iterador::HaySiguiente() const
{
	return itC.HaySiguiente();
}

template <typename T>
bool Conjunto<T>::Iterador::HayAnterior() const
{
	return itC.HayAnterior();
}

template <typename T>
T& Conjunto<T>::Iterador::Siguiente() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	return itC.SiguienteClave();
}

template <typename T>
T& Conjunto<T>::Iterador::Anterior() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	return itC.AnteriorClave();
}

template <typename T>
void Conjunto<T>::Iterador::Avanzar()
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	itC.Avanzar();
}

template <typename T>
void Conjunto<T>::Iterador::Retroceder()
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	itC.Retroceder();
}

template <typename T>
void Conjunto<T>::Iterador::EliminarSiguiente()
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif
	itC.EliminarSiguiente();
}


	// ---------------------------------------------------------
	//  class Conjunto::const_Iterador
	// ---------------------------------------------------------

template <typename T>
Conjunto<T>::const_Iterador::const_Iterador()
{}

template <typename T>
Conjunto<T>::const_Iterador::const_Iterador(const typename Conjunto<T>::Iterador& otro)
	: itC( otro.itC )
{}

template <typename T>
Conjunto<T>::const_Iterador::const_Iterador(const typename Conjunto<T>::const_Iterador& otro)
	: itC( otro.itC )
{}

template <typename T>
typename Conjunto<T>::const_Iterador& Conjunto<T>::const_Iterador::operator = (const typename Conjunto<T>::const_Iterador& otro)
{
	itC = otro.itC;

	return *this;
}

template <typename T>
bool Conjunto<T>::const_Iterador::HaySiguiente() const
{
	return itC.HaySiguiente();
}

template <typename T>
bool Conjunto<T>::const_Iterador::HayAnterior() const
{
return itC.HayAnterior();
}

template <typename T>
const T& Conjunto<T>::const_Iterador::Siguiente() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	return itC.SiguienteClave();
}

template <typename T>
const T& Conjunto<T>::const_Iterador::Anterior() const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	return itC.AnteriorClave();
}

template <typename T>
void Conjunto<T>::const_Iterador::Avanzar()
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	itC.Avanzar();
}

template <typename T>
void Conjunto<T>::const_Iterador::Retroceder()
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	itC.Retroceder();
}

	// ---------------------------------------------------------
	//  funciones auxiliares
	// ---------------------------------------------------------

template <typename T>
std::ostream& operator<<(std::ostream& os, const Conjunto<T>& c)
{
	return Mostrar(os, c, '[', ']');
}

template <typename T>
bool operator == (const Conjunto<T>& d1, const Conjunto<T>& d2)
{
	bool retval = d1.Cardinal() == d2.Cardinal();
	typename Conjunto<T>::const_Iterador it = d1.CrearIt();
	while (retval && it.HaySiguiente()){
		retval = d2.Pertenece(it.Siguiente());
		it.Avanzar(); 
	}

	return retval;
}



} // namespace aed2

#endif	//AED2_DICC_H_INCLUDED


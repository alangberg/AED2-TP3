/*
 * Solucion de la ejercitacion del uso de iteradores.
 */

#include "Lista.h"

#include <iostream>				// std::cout, std::endl
using namespace std;
using namespace aed2;

/**
 * Cantidad de elementos de l
 */
template<typename T>
int cant( const Lista<T>& l ) {
  	int res = 0;
  	typename Lista<T>::const_Iterador miIter = l.crearIt();
  	while(miIter.haySiguiente()){
  		res++;
  		miIter.Avanzar();
  	}
  	return res;
}

/**
 * String con el contenido de l
 */
template<typename T>
void mostrar( const Lista<T>& l ) {
	Mostrar(cout,l,'[',']');
	cout << endl;
}

/**
 * Modifica una lista, duplicando todos los elementos 
 * de la lista original, y devuelve esa misma.
 */
template<typename T>
Lista<T>& dobles( Lista<T>& l ) {
  typename Lista<T>::Iterador miIter = l.CrearIt();
  	while(miIter.HaySiguiente()){
  		T dato = miIter.Siguiente();
  		miIter.AgregarComoAnterior(dato);
  		miIter.Avanzar();
  	}
  	return l;
}

bool esprimo(int n){
	int i = 2;
	bool res = true;
	while(i<n){
		if(n%i==0){res = false;}
		i++;
	}
	return res;
}

/**
 * Devuelve una lista que tiene unicamente los elementos primos 
 * contenidos en la lista original.
 * Un numero entero se considera primo sii unicamente tiene 
 * dos divisores enteros, a si mismo y al numero 1.
 */
template<typename T>
Lista<T> primos( Lista<T>& l ) {
	typename Lista<T>::Iterador miIter = l.CrearIt();
	while(miIter.HaySiguiente()){
		if(!(esprimo(miIter.Siguiente()))){
			miIter.EliminarSiguiente();		
		}else{
	miIter.Avanzar();}
	}
	return l;
}

int main(int argc, char **argv) {
	Lista<int> l;
	l.AgregarAdelante(3);
	l.AgregarAdelante(12);
	l.AgregarAdelante(21);
	l.AgregarAdelante(7);
	mostrar(l);
	//mostrar(dobles(l));
	mostrar(primos(l));

	return 0;
}


#include <iostream>

using namespace std;

#include "Definicion.h"

int main(){
	Avl<Paquete> a;
	ColaPriorHeap<Paquete> col;
	DiccAvl<  Paquete, Lista<Pc> > dic;

	Conjunto<Interfaz> c;
	Pc p1("compu",c);
	Pc p2("prueba",c);
	Id i = 1;
	Prioridad pr = 10;
	Paquete p(i,pr,p1,p2);
	a.insertar(p);

	col.Encolar(p);

	Lista<Pc> l;
	dic.definir(p,l);

	Definicion d(a,col,dic);
	cout << d.xID().cardinal() << endl;

	return 0;
}


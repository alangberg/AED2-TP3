
#include <iostream>
#include "Avl.cpp"
#include "math.h"
using namespace std;



int main() {
	Avl<int> a;
	a.insertar(20);
	a.insertar(30);
	a.insertar(25);
	a.insertar(15);
	a.insertar(23);
	a.insertar(35);
	a.insertar(2);
	a.insertar(3);
	a.borrar(20);
	a.mostrar(cout);
	return 0;
}

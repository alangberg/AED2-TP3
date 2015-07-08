
#include <iostream>
#include "Avl.cpp"
#include "math.h"
#include <cstdlib>
#include "utility"
using namespace std;



int main() {
	Avl<int> a;
	a.insertar(3);
	a.insertar(4);
	a.insertar(5);
	a.insertar(6);
	a.borrar(5);
	a.borrar(6);

	
	a.mostrar(cout);

	
	return 0;
}

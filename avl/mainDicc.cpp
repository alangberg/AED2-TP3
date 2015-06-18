
#include <iostream>
#include "DiccAvl.cpp"
#include "math.h"
#include <stdlib.h>
using namespace std;



int main() {

	DiccAvl<int, char> a;
	a.definir(20, 'a');
	a.definir(10, 'b');
	a.definir(25, 'c');
	a.definir(27, 'a');
	a.borrar(20);
	a.borrar(10);
	a.definir(20, 'a');
	a.mostrar(cout);
	return 0;
}

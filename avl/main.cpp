
#include <iostream>
#include "Avl.cpp"
#include "math.h"
using namespace std;



int main() {
	Avl<int> a;
	a.insertar(20);
	a.insertar(30);
	a.insertar(40);
	a.mostrar(cout);
	return 0;
}

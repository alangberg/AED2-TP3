
#include <iostream>
#include "Avl.cpp"
#include "math.h"
#include <cstdlib>

using namespace std;



int main() {
	Avl<int> a;
	a.insertar(383);
	a.insertar(886);
	a.insertar(777);
	a.mostrar(cout);


	
	return 0;
}

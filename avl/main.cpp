
#include <iostream>
#include "Avl.cpp"
#include "math.h"
#include <cstdlib>

using namespace std;



int main() {
	Avl<int> a;
	a.insertar(5);
	bool b = a.pertenece(5);
	cout << b << endl;
	a.borrar(5);

	
	return 0;
}

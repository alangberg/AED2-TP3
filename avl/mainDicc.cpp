
#include <iostream>
#include "DiccAvl.cpp"
#include "math.h"
#include <stdlib.h>
using namespace std;



int main() {

	DiccAvl<int, int> a;
	a.definir(383,1);
	a.definir(886,1);
	a.definir(777,1);
	a.borrar(886);
	a.borrar(383);
	a.borrar(777);

	


	a.definir(12,6);
	a.definir(2,7);
	a.definir(27,8);
	a.definir(25,9);
	a.definir(28,1);
	a.definir(13,2);
	a.definir(1,4);
	a.definir(5,6);
	a.mostrar(cout);	
	a.borrar(2);
	a.borrar(1);
	a.borrar(27);
	a.borrar(28);
	a.mostrar(cout);


	return 0;
}

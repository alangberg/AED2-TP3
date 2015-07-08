
#include <iostream>
#include "DiccAvl.cpp"
#include "math.h"
#include <stdlib.h>
using namespace std;



int main() {

	DiccAvl<int, int> a;
	a.definir(9383,1);
	a.definir(886,1);
	a.definir(2777,1);
	a.definir(6915,1);
	a.definir(7793,1);
	a.definir(8335,1);
	a.definir(5386,1);
	a.definir(492,1);
	a.definir(6649,1);
	a.mostrar(cout);

	
	return 0;
}

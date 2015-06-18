#include <iostream>
#include "Conjunto.h"


using namespace std;
using namespace aed2; 

int main(){
	Conjunto<int> a = Conjunto<int>();
	a.Agregar(4);
	a.Agregar(5);
	Conjunto<int> b = Conjunto<int>();
	b.Agregar(8);
	b.Agregar(19);
	b.Agregar(7);
	b.Agregar(4);	
	b.Agregar(334);
	a.Agregar(15);
	a.Agregar(24);

	cout << a << endl;
	cout << b << endl;

	a.Unir(b);
	cout << a << endl;



	

	
	
	return 0;
}
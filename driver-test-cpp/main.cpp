#include "Driver.cpp"
#include <iostream>

using namespace aed2;
using namespace std;

int main()
{

    
 	Driver d;
 	cout << d.CantidadComputadoras()<<endl;

 	Conjunto<Interfaz> conj1;
	conj1.Agregar(1);
	conj1.Agregar(21);
	conj1.Agregar(25);
	conj1.Agregar(28);
	Ip n1 = "pc1";

	d.AgregarComputadora(n1, conj1);
	
 	cout << d.CantidadComputadoras()<<endl;
	

	cout << "fin" << endl;
	return 0;
}


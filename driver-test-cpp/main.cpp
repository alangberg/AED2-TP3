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
<<<<<<< HEAD

	Conjunto<Interfaz> conj2;
	conj2.Agregar(12);
	conj2.Agregar(8);
	conj2.Agregar(74);
	conj2.Agregar(82);
	Ip n2 = "pc2";

	d.AgregarComputadora(n2, conj2);

	d.Conectar(n1, 1, n2, 12);

	cout << d.conectadas(n1, n2) << endl;


	
 	cout << d.CantidadComputadoras()<<endl;

=======
	
 	cout << d.CantidadComputadoras()<<endl;
	
>>>>>>> 7d02fa4d4eea9c3dca578941781243c8983a538c

	cout << "fin" << endl;
	return 0;
}


#include "Driver.cpp"
#include <iostream>

using namespace aed2;
using namespace std;

int main()
{

    
 	Driver d;
 	//cout << d.CantidadComputadoras()<<endl;

 	Conjunto<Interfaz> conj1;
	conj1.Agregar(1);
	conj1.Agregar(21);
	conj1.Agregar(25);
	conj1.Agregar(28);
	Ip n1 = "pcuno";

	d.AgregarComputadora(n1, conj1);

	Conjunto<Interfaz> conj2;
	conj2.Agregar(12);
	conj2.Agregar(8);
	conj2.Agregar(74);
	conj2.Agregar(82);
	Ip n2 = "pcdos";

	d.AgregarComputadora(n2, conj2);

	Conjunto<Interfaz> conj3;
	conj3.Agregar(112);
	conj3.Agregar(95);
	conj3.Agregar(99);
	conj3.Agregar(4);
	Ip n3 = "pctres";
	
	d.AgregarComputadora(n3, conj3);

	
	d.Conectar(n1, 1, n2, 12);
	d.Conectar(n2, 8, n3, 112);


	//cout << d.conectadas(n1, n2) << endl;	
 	//cout << d.CantidadComputadoras()<<endl;
	//cout << d.conectadas(d.IesimaComputadora(0), n2) << endl;
	
	string a = d.IesimaComputadora(0);
	//cout << a << endl;
	//cout << d.CantidadInterfacesDe(n1) <<endl;

	Nat inter = d.IesimaInterfazDe(n1, 3);
	//cout << inter <<endl;
	//cout << d.InterfazUsada(n2 ,n1) <<endl;
	//cout << "fin" << endl;


	d.CrearPaquete(n1, n3, 1);
	d.AvanzarSegundo();
	//cout << d.CantidadNodosRecorridosPor(0) <<endl;
	//Computadora aux = d.IesimoNodoRecorridoPor(0, 0);
	//cout << aux << endl;
	//cout << d.CantidadEnEsperaEn(n2) <<endl;
	//Pakete p = d.IesimoEnEsperaEn(n2, 0);
	//cout << p <<endl;
	//Computadora compu = d.laQueMasEnvio();
	//cout << compu <<endl;

	Computadora compu = d.destino(0);
	cout << compu << endl;

	Prioridad prio = d.prioridad(0);
	cout << prio << endl;
	
	return 0;
}


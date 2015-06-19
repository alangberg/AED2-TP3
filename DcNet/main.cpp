#include <iostream>

#include "../Red/Red.h"
//#include "math.h"
using namespace std;
using namespace aed2;




int main() {
	//ARMO PC 
	Conjunto<Interfaz> conj1 = Conjunto<Interfaz>();
	conj1.Agregar(1);
	conj1.Agregar(21);
	Ip asd = "puto";
	Pc a = Pc(asd, conj1);
	//ARMO OTRA PC
	Conjunto<Interfaz> conj2 = Conjunto<Interfaz>();
	conj2.Agregar(12);
	conj2.Agregar(8);
	Ip nombre = "gato";
	Pc b = Pc(nombre, conj2);
	a.mostrar(cout);
	b.mostrar(cout);



	

	Nat x = 1;
	Nat y = 22;
	Paquete q = Paquete(x,y,a,b);
	cout << q.prioridad()<<endl;
	cout << q.ID()<<endl;

	Red r = Red();
	r.agregarCompu(a);
	r.agregarCompu(b);

	r.conectar(a, 1, b, 8);


	q.mostrar(cout);
	cout<< " " <<endl;
	
	Red::Conexion conex(asd, y, nombre, y);
	conex.mostrar(cout);
	cout<< " " <<endl;

	cout << r.mostrarComputadoras().Cardinal()<<endl;

	cout << r.estanConectadas(a,b) <<endl;

	cout << r.interfazQueUsan(a,b) << endl;

	cout << r.interfazQueUsan(b,a) << endl;

	








	return 0;
}

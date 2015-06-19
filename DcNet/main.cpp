#include <iostream>

#include "../Red/Red.h"
//#include "math.h"
using namespace std;
using namespace aed2;




int main() {
	Conjunto<Interfaz> conj = Conjunto<Interfaz>();
	conj.Agregar(1);
	conj.Agregar(21);
	Ip asd = "puto";
	Pc a = Pc(asd, conj);
	Pc b = Pc(a);
	Pc c = a; 
	cout <<a.IP() <<endl;

	
	cout << a.Interfaces() << endl;



	Paquete p = Paquete();

	Nat x = 1;
	Nat y = 22;
	Paquete q = Paquete(x,y,c,b);
	cout << q.prioridad()<<endl;
	cout << q.ID()<<endl;

	Red r = Red();
	r.mostrarComputadoras();
	r.agregarCompu(a);






	return 0;
}

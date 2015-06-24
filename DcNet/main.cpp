#include <iostream>
#include "DcNet.cpp"
#include "../Red/Red.h"
//#include "math.h"
using namespace std;
using namespace aed2;




int main() {
	
	//ARMO PC 
	Conjunto<Interfaz> conj1;
	conj1.Agregar(1);
	conj1.Agregar(21);
	conj1.Agregar(25);
	conj1.Agregar(28);
	Ip n1 = "pc1";
	Pc a = Pc(n1, conj1);
	//ARMO OTRA PC
	Conjunto<Interfaz> conj2;
	conj2.Agregar(12);
	conj2.Agregar(8);
	conj2.Agregar(74);
	conj2.Agregar(82);
	Ip n2 = "pc2";
	Pc b = Pc(n2, conj2);

	Conjunto<Interfaz> conj3;
	conj3.Agregar(112);
	conj3.Agregar(95);
	conj3.Agregar(99);
	conj3.Agregar(4);
	Ip n3 = "pc3";
	Pc c = Pc(n3, conj3);

	Conjunto<Interfaz> conj4;
	conj4.Agregar(19);
	conj4.Agregar(13);
	conj4.Agregar(559);
	conj4.Agregar(29);
	Ip n4 = "pc4";
	Pc d = Pc(n4, conj4);

	Conjunto<Interfaz> conj5;
	conj5.Agregar(89);
	conj5.Agregar(66);
	conj5.Agregar(79);
	conj5.Agregar(46);
	Ip n5 = "pc5";
	Pc e = Pc(n5, conj5);

	Conjunto<Interfaz> conj6;
	conj6.Agregar(1);
	conj6.Agregar(2);
	conj6.Agregar(3);
	conj6.Agregar(4);
	Ip n6 = "pc6";
	Pc f = Pc(n6, conj6);

	/*Nat x = 1;
	Nat y = 22;
	Paquete q = Paquete(x,y,a,b);*/
	
	Red r;
	r.agregarCompu(a);
	r.agregarCompu(b);
	r.agregarCompu(c);
	r.agregarCompu(d);
	r.agregarCompu(e);
	r.agregarCompu(f);


	r.conectar(a, 1, e, 89);
	r.conectar(a, 21, b, 12);
	r.conectar(a, 25, d, 19);
	r.conectar(b, 74, c, 112);
	r.conectar(b, 8, d, 13);
	r.conectar(b, 82, f, 1);
	r.conectar(c, 95, e, 66);			
	





	//cout << r.mostrarComputadoras() <<endl;


	/*Lista<int> l;
	l.AgregarAdelante(5);
	l.AgregarAdelante(12);
	l.AgregarAdelante(3);
	l.AgregarAdelante(4);
*/
	

	//cout << r.caminosMinimos(e,c) <<endl;
	//cout << r.existeCamino(a,b) <<endl;
	//cout << r.interfazUsada(a, 21)<<endl;



	
	/*Avl<Paquete> cavl = Avl<Paquete>();
	cavl.insertar(q);




	ColaPriorHeap<Paquete> cola = ColaPriorHeap<Paquete>();
	cola.Encolar(q);

	

	Lista<Pc> lista = Lista<Pc>();
	lista.AgregarAdelante(a);
	lista.AgregarAdelante(b);
	lista.AgregarAdelante(c);
	lista.AgregarAdelante(d);


	DiccAvl< Paquete, Lista<Pc> > caminos = DiccAvl< Paquete, Lista<Pc> >();
	caminos.definir(q, lista);



	Definicion def(cavl, cola, caminos);
	
	//caminos.borrar(q);
	//def.caminos().borrar(q);

	cout << def.caminos().definido(q) <<endl;

	cout << r.caminosMinimos(a,c) <<endl;
	cout << r.caminosMinimos(a,c).DameUno()[0] <<endl;

*/
	DcNet decenet(r);

	Nat x = 1;
	Nat y = 22;
	Paquete q = Paquete(x,y,a,c);
	decenet.anadirPaquete(q);	
	//decenet.avanzarSegundo();
	bool bo = decenet.enTransito(q);
	cout << bo << endl;
	//cout << decenet.enviados(a) << endl;









	return 0;
}

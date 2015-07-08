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


	DcNet decenet(r);

	Nat x = 1;
	Nat y = 22;
	Pakete q = Pakete(x,y,a,c);

	x = 5;
	y = 22;
	Pakete qq = Pakete(x,y,c,d);

	x = 2;
	y = 21;
	Pakete qw = Pakete(x,y,e,f);

	x = 3;
	y = 22;
	Pakete qe = Pakete(x,y,a,f);

	x = 10;
	y = 1;
	Pakete qr = Pakete(x,y,d,a);


	//decenet.anadirPaquete(q);
	//decenet.anadirPaquete(qq);
	decenet.anadirPaquete(qw);
/*
	cout << "en transito:" << endl;	
	bool b1 = decenet.enTransito(q);
	bool b2 = decenet.enTransito(qq);
	bool b3 = decenet.enTransito(qw);
	bool b4 = decenet.enTransito(qe);
	bool b5 = decenet.enTransito(qr);
	cout << b1 << endl;
	cout << b2 << endl;
	cout << b3 << endl;
	cout << b4 << endl;
	cout << b5 << endl;


	cout << "cantidad enviados:" << endl;
	cout << decenet.enviados(a) << endl;
	cout << decenet.enviados(b) << endl;
	cout << decenet.enviados(c) << endl;
	cout << decenet.enviados(d) << endl;
	cout << decenet.enviados(e) << endl;
	cout << decenet.enviados(f) << endl;

	cout << "compu mas enviados:" << endl;
	cout << decenet.masEnviados() << endl;

	cout << "recorrido:" << endl;
	cout << decenet.recorrido(q) << endl;
	cout << decenet.recorrido(qq) << endl;
	cout << decenet.recorrido(qw) << endl;
	//cout << decenet.recorrido(qe) << endl;
	//cout << decenet.recorrido(qr) << endl;

	cout << "paquetes:" << endl;
	decenet.paquetes(a).mostrar(cout);
	//decenet.paquetes(b).mostrar(cout); 
	decenet.paquetes(c).mostrar(cout);
	//decenet.paquetes(d).mostrar(cout);
	decenet.paquetes(e).mostrar(cout); 
	//decenet.paquetes(f).mostrar(cout); 

	cout << " " << endl;


	decenet.avanzarSegundo();

	
	cout << "en transito:" << endl;	
	b1 = decenet.enTransito(q);
	b2 = decenet.enTransito(qq);
	b3 = decenet.enTransito(qw);
	b4 = decenet.enTransito(qe);
	b5 = decenet.enTransito(qr);
	cout << b1 << endl;
	cout << b2 << endl;
	cout << b3 << endl;
	cout << b4 << endl;
	cout << b5 << endl;


	cout << "cantidad enviados:" << endl;
	cout << decenet.enviados(a) << endl;
	cout << decenet.enviados(b) << endl;
	cout << decenet.enviados(c) << endl;
	cout << decenet.enviados(d) << endl;
	cout << decenet.enviados(e) << endl;
	cout << decenet.enviados(f) << endl;

	cout << "compu mas enviados:" << endl;
	cout << decenet.masEnviados() << endl;

	cout << "recorrido:" << endl;
	cout << decenet.recorrido(q) << endl;
	cout << decenet.recorrido(qq) << endl;
	cout << decenet.recorrido(qw) << endl;
	//cout << decenet.recorrido(qe) << endl;
	//cout << decenet.recorrido(qr) << endl;

	cout << "paquetes:" << endl;
	//decenet.paquetes(a).mostrar(cout);
	decenet.paquetes(b).mostrar(cout); 
	decenet.paquetes(c).mostrar(cout);
	//decenet.paquetes(d).mostrar(cout);
	//decenet.paquetes(e).mostrar(cout); 
	//decenet.paquetes(f).mostrar(cout); 

	cout << " " << endl;


	decenet.anadirPaquete(qe);
	decenet.anadirPaquete(qr);
*/

	cout << "recorrido:" << endl;
	cout << decenet.recorrido(qw) << endl;

	decenet.avanzarSegundo();
	
	cout << "recorrido:" << endl;
	cout << decenet.recorrido(qw) << endl;

	decenet.avanzarSegundo();
	
	cout << "recorrido:" << endl;
	cout << decenet.recorrido(qw) << endl;

	return 0;
}

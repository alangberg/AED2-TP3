#include <iostream>
//#include <tuple>
#include "DcNet.cpp"
#include "Pc.h"
#include "Paquete.h"
//#include "math.h"
using namespace std;



int main() {
	Pc p(1000);
	Pc p2(50);
	Paquete paq(10,100,p,p2);
	cout << paq.origen().IP() << endl;
	return 0;
}

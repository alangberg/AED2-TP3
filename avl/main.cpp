
#include <iostream>
#include "Avl.cpp"
#include "math.h"
#include <cstdlib>
using namespace std;



int main() {
	Avl<int> a;

	int i = 0;

	while( i < 100){
		int x = rand() %10000;
		a.insertar(x);
		i++;
	}

	a.insertar(2);


	
	return 0;
}

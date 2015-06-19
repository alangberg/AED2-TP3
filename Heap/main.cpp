#include <iostream>
#include <cstdlib>
#include "Heap.cpp"


using namespace std;

int main(){

ColaPriorHeap<int> a;

int i = 0;

while( i < 1000){
	int x = rand() %10;
	a.Encolar(x);
	i++;
}

i = 0;
/*
while( i < 10){
	cout << a.Desencolar() << endl;
	i++;
}

*/
return 0;


}
#ifndef PC_H
#define PC_H
#include "../Conjunto/Conjunto.h"
using namespace std;
using namespace aed2;
class Pc
{

    public:
    	Pc(string, Conjunto<int>);
        Pc();
    	string IP();
    	void operator=(const Pc& otra);
    private:    	
        string p;
        Conjunto<int> c;


};

Pc::Pc(){    
}


Pc::Pc(string s, Conjunto<int> con){
	p = s;
    c = con;
}



string Pc::IP(){
	return p;
}

void Pc::operator=(const Pc& otra){
	p = otra.p;
    c = otra.c;
}


#endif // PC_H



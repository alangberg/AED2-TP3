#ifndef PC_H
#define PC_H
#include "../Conjunto/Conjunto.h"
#include "TiposSecundarios.h"
using namespace std;
using namespace aed2;
#include <iostream>

class Pc
{

    public:
    	Pc(const Ip&, const Conjunto<Interfaz>&);
        Pc();
    	const Ip& IP() const;
        const Conjunto<Interfaz>& Interfaces() const;
    	void operator=(const Pc& otra);
        bool operator == (const Pc& p1) const;
        void mostrar(ostream& o) const;    
    private:    	
        Ip p;
        Conjunto<Interfaz> c;


};

Pc::Pc(){}


Pc::Pc(const Ip& s, const Conjunto<Interfaz>& con): p(s), c(con) {}


const Ip& Pc::IP() const{
	return p;
}

const Conjunto<Interfaz>& Pc::Interfaces() const {
    return c;
}

void Pc::operator=(const Pc& otra){
	p = otra.p;
    c = otra.c;
}

bool Pc::operator == (const Pc& p1) const{
    return p1.p == p && p1.c == c;
}

void Pc::mostrar(ostream& o) const{
    o << "[" << p << ";" << c << "]";
}




#endif // PC_H



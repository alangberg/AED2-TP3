#ifndef PC_H
#define PC_H

using namespace std;

class Pc
{

    public:
    	Pc();
    	Pc(long int);
    	long int IP();
    	void operator=(const Pc& otra);
    private:    	
        long int p;    	
};

Pc::Pc(){
	p = 0;
}

Pc::Pc(long int n){
	p = n;
}

long int Pc::IP(){
	return p;
}

void Pc::operator=(const Pc& otra){
	p = otra.p;
}


#endif // PC_H



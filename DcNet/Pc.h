#ifndef PC_H
#define PC_H

using namespace std;

class Pc
{

    public:
    	Pc(long int);
    	long int IP();
    private:    	
        long int p;    	
};

Pc::Pc(long int n){
	p = n;
}

long int Pc::IP(){
	return p;
}


#endif // PC_H



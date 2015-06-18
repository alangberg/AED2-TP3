#ifndef DICCAvl_H
#define DICCAvl_H

using namespace std;

template<class K,class S>
class DiccAvl
{
    public:
        DiccAvl();
        void definir(const K&, const S&);
        S& significado(const K&);
        bool definido(const K&) const;
        void borrar(const K&);
        unsigned int cardinal() const;
        void mostrar(std::ostream&) const; 

    private:       
        struct Nodo
        {       
            Nodo(const K&, const S&);    
            K clave;
            S sign;
            Nodo* izq;     
            Nodo* der;
            Nodo* padre;
            int altura;
            void imprimirNodo(std::ostream&, const K&) const;             
        };
        unsigned int cant;        
        Nodo* raiz;
        Nodo* buscarPapa(const K& clave) const;
        void rebalanceo(Nodo*);
        void rotacionDerecha(Nodo*);
        void rotacionIzquierda(Nodo*);
        void rotacionDerIzq(Nodo*);
        void rotacionIzqDer(Nodo*);
        void restablecerAlt(Nodo*);
        Nodo* buscar(const K& clave) const;
};





#endif // DICCAvl_H

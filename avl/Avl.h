#ifndef AVL_H
#define AVL_H

using namespace std;

template <class T>
class Avl
{
    public:
        Avl();      
        void insertar(const T&);
        bool pertenece(const T&) const;
        void borrar(const T&);
        unsigned int cardinal() const;
        void mostrar(std::ostream&) const;            
        //Avl<T> operator=(const Avl<T>& otro);
    private:       
        struct Nodo
        {       
            Nodo(const T& v);    
            T valor;
            Nodo* izq;     
            Nodo* der;
            Nodo* padre;
            int altura;
            void imprimirNodo(std::ostream&, const T&) const;             
        };
        unsigned int cant;        
        Nodo* raiz;
        Nodo* buscarPapa(const T& clave) const;
        void rebalanceo(Nodo*);
        void rotacionDerecha(Nodo*);
        void rotacionIzquierda(Nodo*);
        void rotacionDerIzq(Nodo*);
        void rotacionIzqDer(Nodo*);
        void restablecerAlt(Nodo*);
        Nodo* buscar(const T& clave) const;
};





#endif // AVL_H

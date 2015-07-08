/*
 * Author: Fede
 * Maintainer: tfischer
 * 
 * Conjunto (lineal) imlementado sobre Diccionario (Dicc.h),
 * que está implementado sobre listas enlazadas (Lista.h).
 * 
 * Created on 30 de octubre de 2010
 */

#ifndef AED2_Conjunto_H_INCLUDED
#define	AED2_Conjunto_H_INCLUDED

#include <iostream>
#include "../driver-test-cpp/aed2/Dicc.h"

namespace aed2
{

template<class T>
class Conjunto
{
  public:

    //forward declarations
    class Iterador;
    class const_Iterador;

    // Generadores

    Conjunto();
    Conjunto(const Conjunto<T>& otro);

    Iterador Agregar(const T& e);
    Iterador AgregarRapido(const T& e);

    void Eliminar(const T& e);

    // Observadores

    bool EsVacio() const;

    bool Pertenece(const T& e) const;

    Nat Cardinal() const;

    const T& DameUno() const;
    void SinUno();
    void Unir(const Conjunto<T>& c);

    Iterador CrearIt();
    const_Iterador CrearIt() const;

    //esta funcion la agregamos aca, porque nos conviene acceder a
    //la representación.  Sino, no haria falta.
    bool operator == (const Conjunto<T>& otro) const;

    /************************************
    * Iterador de Conjunto, modificable *
    ************************************/
    class Iterador
    {
      public:

        Iterador();

        Iterador(const typename Conjunto<T>::Iterador& otra);

        Iterador& operator = (const typename Conjunto<T>::Iterador& otra);

        bool operator == (const typename Conjunto<T>::Iterador& otro) const;

        bool HaySiguiente() const;
        bool HayAnterior() const;

        const T& Siguiente() const;
        const T& Anterior() const;

        void Avanzar();
        void Retroceder();

        void EliminarAnterior();
        void EliminarSiguiente();

      private:
      
        typename Dicc<T,bool>::Iterador it_dicc_;

        Iterador(Conjunto<T>& c);

        Iterador(const typename Dicc<T,bool>::Iterador& itDict);

        friend class Conjunto<T>::const_Iterador;

        friend typename Conjunto<T>::Iterador Conjunto<T>::CrearIt();
        friend typename Conjunto<T>::Iterador Conjunto<T>::Agregar(const T&);
        friend typename Conjunto<T>::Iterador Conjunto<T>::AgregarRapido(const T&);
    };

    /*********************************************
    * const_Iterador de Conjunto, no modificable *
    *********************************************/
    class const_Iterador
    {
      public:

        const_Iterador();

        const_Iterador(const typename Conjunto<T>::Iterador& otra);

        const_Iterador(const typename Conjunto<T>::const_Iterador& otra);

        const_Iterador& operator = (const typename Conjunto<T>::const_Iterador& otra);

        bool operator==(const typename Conjunto<T>::const_Iterador& otro) const;

        bool HaySiguiente()const;
        bool HayAnterior()const;

        const T& Siguiente()const;
        const T& Anterior()const;

        void Avanzar();
        void Retroceder();

      private:

        typename Dicc<T,bool>::const_Iterador it_dicc_;

        const_Iterador(const Conjunto<T>& c);

        friend typename Conjunto<T>::const_Iterador Conjunto<T>::CrearIt() const;

    };

  private:

    Dicc<T,bool> dicc_;
};

template<class T>
std::ostream& operator<<(std::ostream&, const Conjunto<T>&);

template<class T>
bool operator==(const Conjunto<T>&, const Conjunto<T>&);

  //  Implementacion de Conjunto

template<class T>
Conjunto<T>::Conjunto()
{}

template<class T>
Conjunto<T>::Conjunto(const Conjunto<T>& otro)
  : dicc_( otro.dicc_ )
{}

template<class T>
typename Conjunto<T>::Iterador Conjunto<T>::Agregar(const T& e){
    return Iterador(dicc_.Definir(e, true));
}

template<class T>
typename Conjunto<T>::Iterador Conjunto<T>::AgregarRapido(const T& e){
    return Iterador(dicc_.DefinirRapido(e, true));
}

template<class T>
void Conjunto<T>::Eliminar(const T& e){
    if(Pertenece(e)) dicc_.Borrar(e);
}

template<class T>
bool Conjunto<T>::EsVacio() const{
    return dicc_.CantClaves()==0;
}

template<class T>
bool Conjunto<T>::Pertenece(const T& e) const{
    return dicc_.Definido(e);
}

template<class T>
Nat Conjunto<T>::Cardinal() const{
    return dicc_.CantClaves();
}

template<class T>
const T& Conjunto<T>::DameUno() const
{
  // Me aseguro que se cumpla la precondicion
  #ifdef DEBUG
  assert(Cardinal() != 0);
  #endif
  const_Iterador it = CrearIt();
  return it.Siguiente();  
}

template<class T>
void Conjunto<T>::SinUno()
{
  // Me aseguro que se cumpla la precondicion
  #ifdef DEBUG
  assert(Cardinal() != 0);
  #endif
  Iterador it = CrearIt();
  it.EliminarSiguiente();
}

template<class T>
void Conjunto<T>::Unir(const Conjunto<T>& c)
{
  const_Iterador it = c.CrearIt();
  while (it.HaySiguiente()) {
    if (! Pertenece(it.Siguiente()) ) {
      AgregarRapido(it.Siguiente());
    }
    it.Avanzar();
  }
}


template<class T>
bool Conjunto<T>::operator==(const Conjunto<T>& otro) const {
    return dicc_ == otro.dicc_;
}

template<class T>
typename Conjunto<T>::Iterador Conjunto<T>::CrearIt(){
    return Iterador(*this);
}

template<class T>
typename Conjunto<T>::const_Iterador Conjunto<T>::CrearIt() const{
    return const_Iterador(*this);
}

  // Implementacion Iterador

template<class T>
Conjunto<T>::Iterador::Iterador(const typename Conjunto<T>::Iterador& otra)
  : it_dicc_(otra.it_dicc_)
{}

template<class T>
typename Conjunto<T>::Iterador& Conjunto<T>::Iterador::operator = (const typename Conjunto<T>::Iterador& otra)
{
  it_dicc_ = otra.it_dicc_;
  return *this;
}

template<class T>
Conjunto<T>::Iterador::Iterador()
{}

template<class T>
bool Conjunto<T>::Iterador::operator == (const typename Conjunto<T>::Iterador& otro) const
{
  return it_dicc_ == otro.it_dicc_;
}

template<class T>
bool Conjunto<T>::Iterador::HaySiguiente() const
{
  return it_dicc_.HaySiguiente();
}

template<class T>
bool Conjunto<T>::Iterador::HayAnterior() const
{
  return it_dicc_.HayAnterior();
}

template<class T>
const T& Conjunto<T>::Iterador::Siguiente() const
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  return it_dicc_.SiguienteClave();
}

template<class T>
const T& Conjunto<T>::Iterador::Anterior() const
{
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  return it_dicc_.AnteriorClave();
}

template<class T>
void Conjunto<T>::Iterador::Avanzar()
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  it_dicc_.Avanzar();
}

template<class T>
void Conjunto<T>::Iterador::Retroceder()
{
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  it_dicc_.Retroceder();
}

template<class T>
void Conjunto<T>::Iterador::EliminarAnterior()
{
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  it_dicc_.EliminarAnterior();
}

template<class T>
void Conjunto<T>::Iterador::EliminarSiguiente()
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  it_dicc_.EliminarSiguiente();
}

template<class T>
Conjunto<T>::Iterador::Iterador(Conjunto<T>& c)
  : it_dicc_( c.dicc_.CrearIt() )
{}

template<class T>
Conjunto<T>::Iterador::Iterador(const typename Dicc<T,bool>::Iterador& iter)
  : it_dicc_(iter)
{}

  // Implementacion const_Iterador

template<class T>
Conjunto<T>::const_Iterador::const_Iterador()
{}

template<class T>
Conjunto<T>::const_Iterador::const_Iterador(const typename Conjunto<T>::Iterador& otra)
  : it_dicc_( otra.it_dicc_ )
{}

template<class T>
Conjunto<T>::const_Iterador::const_Iterador(const typename Conjunto<T>::const_Iterador& otra)
  : it_dicc_( otra.it_dicc_ )
{}

template<class T>
typename Conjunto<T>::const_Iterador& Conjunto<T>::const_Iterador::operator = (const typename Conjunto<T>::const_Iterador& otra)
{
  it_dicc_ = otra.it_dicc_;

  return *this;
}

template<class T>
bool Conjunto<T>::const_Iterador::operator == (const typename Conjunto<T>::const_Iterador& otro) const
{
  return it_dicc_ == otro.it_dicc_;
}

template<class T>
bool Conjunto<T>::const_Iterador::HaySiguiente() const
{
  return it_dicc_.HaySiguiente();
}

template<class T>
bool Conjunto<T>::const_Iterador::HayAnterior() const
{
  return it_dicc_.HayAnterior();
}

template<class T>
const T& Conjunto<T>::const_Iterador::Siguiente() const
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  return it_dicc_.SiguienteClave();
}

template<class T>
const T& Conjunto<T>::const_Iterador::Anterior() const
{
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  return it_dicc_.AnteriorClave();
}

template<class T>
void Conjunto<T>::const_Iterador::Avanzar()
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  it_dicc_.Avanzar();
}

template<class T>
void Conjunto<T>::const_Iterador::Retroceder()
{
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  it_dicc_.Retroceder();
}

template<class T>
Conjunto<T>::const_Iterador::const_Iterador(const Conjunto<T>& c)
  : it_dicc_( c.dicc_.CrearIt() )
{}

  // Otras implementaciones

template<class T>
bool operator==(const Conjunto<T>& c1, const Conjunto<T>& c2)
{
  return c1.operator==(c2);
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Conjunto<T>& c)
{
  return Mostrar(os, c, '{', '}');
}

}

#endif	//AED2_Conjunto_H_INCLUDED

/**
 * Modulo Red
 * Algoritmos y Estructuras de Datos 2
 */

#ifndef RED_H_INCLUDED
#define RED_H_INCLUDED

#include "../Conjunto/Conjunto.h"
#include "../DcNet/Paquete.h"
#include <ostream>
#include <cassert> 
using namespace std;
namespace aed2
{


class Red
{



	public:
		/// Crea una red vacía. (Operación ArrancarRed())
		Red();
		/// Crea por copia una Red (operación Copiar())
		Red(const Red& otro);
		/// Operacion de asignacion
		Red& operator=(const Red& otra);
		/// Operaciones básicas
		const Conjunto<Pc> mostrarComputadoras() const;
		
		void agregarCompu(const Pc& p);
		
		void conectar(const Pc& p1, const Interfaz i1, const Pc& p2, const Interfaz i2);
		
		bool estanConectadas(const Pc& p1, const Pc& p2) const;
		
		Interfaz interfazQueUsan(const Pc& p1, const Pc& p2) const;
		
		Conjunto<Pc> conectadoCon(const Pc& p1) const;
		
		bool interfazUsada(const Pc& p1, const Interfaz i1) const;
		
		Conjunto< Lista<Pc> > caminosMinimos(const Pc& p1, const Pc& p2) const;
		
		bool existeCamino(const Pc& p1, const Pc& p2);

		struct Conexion {
		
			Conexion(const Ip compu1, const Interfaz int1, const Ip compu2, const Interfaz int2)
			: pc1(compu1), i1(int1), pc2(compu2), i2(int2){}

			const Ip Prim() const{
				return pc1;
			}

			const Interfaz Seg() const{
				return i1;
			}

			const Ip Ter() const{
				return pc2;
			}

			const Interfaz Cuar() const{
				return i2;
			}

			friend ostream& operator << (ostream& os, const Conexion& c){
   				os << "{" << c.Prim() << "," << c.Seg() << "," << c.Ter() << "," << c.Cuar() << "}" <<endl;
   				return os;
			}

			Ip pc1;
			Interfaz i1;
			Ip pc2;
			Interfaz i2;

		};


	private:
        Dicc<Ip, Conjunto<Interfaz> > interfaces;
        
        Dicc<Ip, Conjunto<Ip> > vecinos;
        
        Lista<Conexion> conexiones; 

        Conjunto< Lista<Pc> > caminos(const Pc& p1, const Pc& p2) const;

        Conjunto< Lista<Pc> > auxCaminos(const Pc& p1, const Pc& p2, Lista<Pc> recorrido, Conjunto<Pc> candidatos) const;	

        Conjunto<Lista<Pc> > auxMinimos(Conjunto<Lista<Pc> > C) const;


};

Red::Red()
{}

Red::Red(const Red& otro)
	: interfaces(otro.interfaces), vecinos(otro.vecinos), conexiones(otro.conexiones)
{}

Red& Red::operator=(const Red& otra)
{
	interfaces = otra.interfaces;
	vecinos = otra.vecinos;
	conexiones = otra.conexiones;

	return *this;

}

const Conjunto<Pc> Red::mostrarComputadoras() const
{
	Conjunto<Pc> compus = Conjunto<Pc>();
	Dicc<Ip, Conjunto<Interfaz> >::const_Iterador it = interfaces.CrearIt();
	while(it.HaySiguiente()){
		Pc pc1(it.SiguienteClave(), it.SiguienteSignificado());
		compus.AgregarRapido(pc1);
		it.Avanzar();  
	}
	return compus;
}

void Red::agregarCompu(const Pc& p)
{
	assert(not mostrarComputadoras().Pertenece(p));	
	interfaces.DefinirRapido(p.IP(), p.Interfaces());
	Conjunto<Ip> c;
	vecinos.DefinirRapido(p.IP(), c);
}

void Red::conectar(const Pc& p1, const Interfaz i1, const Pc& p2, const Interfaz i2)
{
	assert(mostrarComputadoras().Pertenece(p1) && mostrarComputadoras().Pertenece(p2) && p1 != p2 && not interfazUsada(p1,i1) && not interfazUsada(p2,i2) && not estanConectadas(p1,p2));	
	Ip ip1 = p1.IP();
	Ip ip2 = p2.IP();
	Conexion c(ip1, i1, ip2, i2);
	conexiones.AgregarAdelante(c);
	Dicc<Ip, Conjunto<Ip> >::Iterador it = vecinos.CrearIt();
	while (it.SiguienteClave() != ip1 && it.SiguienteClave() != ip2){
		it.Avanzar();
	}
	if (it.SiguienteClave() == ip1) {
		it.SiguienteSignificado().AgregarRapido(ip2);
		it.Avanzar();
		while(it.SiguienteClave() != ip2){
			it.Avanzar();
		} 
		it.SiguienteSignificado().AgregarRapido(ip1);
	}else{
		it.SiguienteSignificado().AgregarRapido(ip1);
		it.Avanzar();
		while(it.SiguienteClave() != ip1){
			it.Avanzar();
		} 
		it.SiguienteSignificado().AgregarRapido(ip2);
	} 
}

bool Red::estanConectadas(const Pc& p1, const Pc& p2) const{
	assert(mostrarComputadoras().Pertenece(p1) && mostrarComputadoras().Pertenece(p2));
	Ip ip1 = p1.IP();
	Ip ip2 = p2.IP();
	return (vecinos.Significado(ip1)).Pertenece(ip2);
}

Interfaz Red::interfazQueUsan(const Pc& p1, const Pc& p2) const{
	assert(mostrarComputadoras().Pertenece(p1) && mostrarComputadoras().Pertenece(p2) && estanConectadas(p1,p2));	
	Lista<Conexion>::const_Iterador it = conexiones.CrearIt();
	Ip ip1 = p1.IP();
	Ip ip2 = p2.IP();
	while (it.HaySiguiente() && it.Siguiente().Prim() != ip1 && it.Siguiente().Ter() != ip1){
		it.Avanzar();
	}
	Interfaz res; 
	if (it.Siguiente().Prim() == ip1){
		res = it.Siguiente().Seg();
	}else{
		res = it.Siguiente().Cuar();
	}
	return res;
}

Conjunto<Pc> Red::conectadoCon(const Pc& p1) const{	
	assert(mostrarComputadoras().Pertenece(p1));
	Conjunto<Ip> c = vecinos.Significado(p1.IP());
	Conjunto<Ip>::const_Iterador it = c.CrearIt();
	Conjunto<Pc> res;
	while (it.HaySiguiente()) {
		Pc compu(it.Siguiente(), interfaces.Significado(it.Siguiente()));
		res.AgregarRapido(compu);
		it.Avanzar();
	}
	return res;
}

Conjunto< Lista<Pc> > Red::caminosMinimos(const Pc& p1, const Pc& p2) const {
	assert(mostrarComputadoras().Pertenece(p1) && mostrarComputadoras().Pertenece(p2));
	return auxMinimos(caminos(p1, p2));
}

Conjunto< Lista<Pc> > Red::caminos(const Pc& p1, const Pc& p2) const{
	Lista<Pc> recorrido;
	recorrido.AgregarAdelante(p1);
	return auxCaminos(p1, p2, recorrido, conectadoCon(p1));
}

Conjunto< Lista<Pc> > Red::auxCaminos(const Pc& p1, const Pc& p2, Lista<Pc> recorrido, Conjunto<Pc> candidatos) const {
	if ( !(candidatos.EsVacio()) ){
		if (recorrido.Ultimo() == p2){
			Conjunto< Lista<Pc> > res;
			res.AgregarRapido(recorrido);
			return res;
		}else if( !(recorrido.Esta(candidatos.DameUno())) ){
				Conjunto<Pc> aux = candidatos;
				aux.SinUno();
				Lista<Pc> copia = recorrido;
				copia.AgregarAtras(candidatos.DameUno());
				Conjunto< Lista<Pc> > aux2 = auxCaminos(p1, p2, copia, conectadoCon(candidatos.DameUno()));
				aux2.Unir(auxCaminos(p1, p2, recorrido, aux));
				return aux2;
			}else{
				Conjunto<Pc> aux = candidatos;
				aux.SinUno();
				return auxCaminos(p1, p2, recorrido, aux);
			}
	}else{
		Conjunto< Lista<Pc> > res;
		return res;
	}
}

Conjunto<Lista<Pc> > Red::auxMinimos(Conjunto<Lista<Pc> > C) const {
	Conjunto<Lista<Pc> > vacio;
	if (C.EsVacio()){
		return vacio;
	}else if (C.Cardinal() == 1){
			vacio.AgregarRapido(C.DameUno());
			return vacio;
		}else{ 
			Conjunto<Lista<Pc> > aux = C; 
			aux.SinUno();
			if(C.DameUno().Longitud() < auxMinimos(aux).DameUno().Longitud()) {
				vacio.AgregarRapido(C.DameUno());
				return vacio;
			}else if (C.DameUno().Longitud() == auxMinimos(aux).DameUno().Longitud()) {
				vacio = auxMinimos(aux);
				vacio.AgregarRapido(C.DameUno());
				return vacio;
			}else{
				return auxMinimos(aux);
			}
		}	
			
}		

bool Red::interfazUsada(const Pc& p1, const Interfaz i1) const{
	Lista<Conexion>::const_Iterador it = conexiones.CrearIt();
	while (it.HaySiguiente()){
		if((it.Siguiente().Prim() == p1.IP() && it.Siguiente().Seg() == i1) || (it.Siguiente().Ter() == p1.IP() && it.Siguiente().Cuar() == i1)){
			return true;
		}
		it.Avanzar();
	}
	return false;
}

bool Red::existeCamino(const Pc& p1, const Pc& p2){
	assert(mostrarComputadoras().Pertenece(p1) && mostrarComputadoras().Pertenece(p2));
	return caminos(p1, p2).Cardinal() > 0;
}



} // namespace aed2

#endif //RED_H_INCLUDED


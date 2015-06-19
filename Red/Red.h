/**
 * Modulo Red
 * Algoritmos y Estructuras de Datos 2
 */

#ifndef RED_H_INCLUDED
#define RED_H_INCLUDED

#include "../Conjunto/Conjunto.h"
#include "../DcNet/Paquete.h"
#include <ostream>
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
		Conjunto<Pc> mostrarComputadoras() const;
		
		void agregarCompu(const Pc& p);
		
		void conectar(const Pc& p1, const Interfaz i1, const Pc& p2, const Interfaz i2);
		
		bool estanConectadas(const Pc& p1, const Pc& p2) const;
		
		Interfaz interfazQueUsan(const Pc& p1, const Pc& p2) const;
		
		Conjunto<Pc> conectadoCon(const Pc& p1) const;
		
		bool interfazUsada(const Pc& p1, const Interfaz i1) const;
		
		Conjunto< Lista<Pc> > caminosMinimos(const Pc& p1, const Pc& p2) const;
		
		bool existeCamino(const Pc& p1, const Pc& p2) const;

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

			void mostrar(ostream& o) const{
				o << "{" << pc1 << "," << i1 << "," << pc2 << "," << i2 << "}";
			}

			Ip pc1;
			Interfaz i1;
			Ip pc2;
			Interfaz i2;

		};

	private:
        Dicc<Ip, Conjunto<Interfaz> > interfaces;
        
        Dicc<Ip, Conjunto<Ip> > vecinos;
        
        Lista<Conexion> conexiones; //FALTA COMPLETAR TUPLA PC,INTERFAZ,PC,INTERFAZ!!!!

        Conjunto< Lista<Pc> > auxCaminos(const Pc& p1, const Pc& p2, Lista<Pc> recorrido, Conjunto<Pc> candidatos) ;

        Conjunto<Lista<Pc> > Auxminimos(Conjunto<Lista<Pc> > C);

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

Conjunto<Pc> Red::mostrarComputadoras() const
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
	interfaces.DefinirRapido(p.IP(), p.Interfaces());
	Conjunto<Ip> c;
	vecinos.DefinirRapido(p.IP(), c);
}

void Red::conectar(const Pc& p1, const Interfaz i1, const Pc& p2, const Interfaz i2)
{
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
	Ip ip1 = p1.IP();
	Ip ip2 = p2.IP();
	return (vecinos.Significado(ip1)).Pertenece(ip2);
}

Interfaz Red::interfazQueUsan(const Pc& p1, const Pc& p2) const{
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

Conjunto< Lista<Pc> > Red::caminosMinimos(const Pc& p1, const Pc& p2) const{	
}

Conjunto< Lista<Pc> > Red::auxCaminos(const Pc& p1, const Pc& p2, Lista<Pc> recorrido, Conjunto<Pc> candidatos) {
	Conjunto< Lista<Pc> > res;
	if (!candidatos.EsVacio()){
		if (recorrido.Ultimo() == p2){
			Conjunto< Lista<Pc> > res;
			res.AgregarRapido(recorrido);
			return res;
		}else if(!recorrido.Esta(candidatos.DameUno())){
				Conjunto<Pc> aux = candidatos;
				aux.SinUno();
				Lista<Pc> copia = recorrido;
				copia.AgregarAtras(candidatos.DameUno());
				Conjunto< Lista<Pc> > aux2 = auxCaminos(p1, p2, copia, conectadoCon(candidatos.DameUno()));
				aux2.Unir(auxCaminos(p1, p2, recorrido, aux));
				return aux2;
			}else{
				Conjunto<Pc> aux = candidatos;
				return auxCaminos(p1, p2, recorrido, aux);
			}
	}
}

Conjunto<Lista<Pc> > Red::Auxminimos(Conjunto<Lista<Pc> > C){
			Conjunto<Lista<Pc> > vacio = Conjunto<Lista<Pc> >();
			if (C.EsVacio()){
				return Conjunto<Lista<Pc> >();
			}else if (C.Cardinal()==1){
				vacio.AgregarRapido(C.DameUno());
			}else{ 
				Conjunto<Lista<Pc> > aux = C; 
				aux.SinUno();
				if(C.DameUno().Longitud() < Auxminimos(aux).DameUno().Longitud()) {
					vacio.AgregarRapido(C.DameUno());
				}else if (C.DameUno().Longitud() == Auxminimos(aux).DameUno().Longitud()) {
					Auxminimos(aux).AgregarRapido(C.DameUno());
				}else{
					Auxminimos(aux);
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









} // namespace aed2

#endif //RED_H_INCLUDED


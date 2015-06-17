#include "TiposBasicos.h"
#include "Lista.h"

#include <ostream>

namespace aed2

{

template <typename T>
class Conjunto
{
	public:
		/// Crea un conjunto vacío. (Operación Vacia())
		Conjunto();
		/// Crea por copia un conjunto (operación Copiar())
		Conjunto(const Conjunto& otro);
		/// Destruye el conjunto, incluyendo los T alojados
		~Conjunto();
		/// Operacion de asignacion
		Conjunto<T>& operator=(const Conjunto<T>& otra);

		/// Operaciones básicas
		void agregar(const T& elem);
		//typename Lista<T>::Iterador agregar_rapido(const T& elem);
		bool es_vacio() const;
		bool pertenece(const T& elem);
		//typename Lista<T>::Iterador eliminar(const T& elem);
		Nat cardinal() const;
		//void unir(Conjunto<T>& c1, const Conjunto<T> c2);
		T& dameUno();
		//void sinUno();

	private:
		Lista<T> l;
};
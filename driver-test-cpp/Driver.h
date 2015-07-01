#ifndef DRIVER_H_
#define DRIVER_H_

#include "Tipos.h"
#include "../Conjunto/TiposBasicos.h"
#include "../DcNet/DcNet.cpp"


namespace aed2 {

class Driver
{
    public:

        Driver();

        ~Driver();

        /// Observadores Red //////////////////////////////////////////////////////////

        Nat CantidadComputadoras() const;
        const Computadora& IesimaComputadora(const Nat i) const ;
        
        Nat CantidadInterfacesDe(const Computadora& c) const;
        const Interfaz& IesimaInterfazDe(const Computadora& c, const Nat i) const ;

        const Interfaz& IntefazUsada(const Computadora& c1, const Computadora& c2) const;

        bool conectadas(const Computadora& c1, const Computadora& c2) const;

        /// Armado Red ////////////////////////////////////////////////////////////////

        void AgregarComputadora(const Computadora& ip, const Conjunto<Interfaz>& ci);
        
        void Conectar(const Computadora& c1, const Interfaz& i1, const Computadora& c2, const Interfaz& i2);
    

       /// Observadores DCNet //////////////////////////////////////////////////////////////
    
        Nat CantidadNodosRecorridosPor(const Pakete& p) const;
        const Computadora& IesimoNodoRecorridoPor(const Pakete& p) const;

        Nat CantidadEnviadosPor(const Computadora& c) const;
    
        Nat CantidadEnEsperaEn(const Computadora& c) const;
        const Pakete& IesimoEnEsperaEn(const Computadora& c) const;

        /// Acciones DCNet ////////////////////////////////////////////////////////////

        void CrearPaquete(const Computadora& origen, const Computadora& destino, Nat prioridad);
        
        void AvanzarSegundo();
        
        const Computadora& laQueMasEnvio() const;
        
        // Auxiliares para ver los Paketes
        const Computadora& origen(const Pakete& p) const; 
        const Computadora& destino(const Pakete& p) const; 
        Nat prioridad(const Pakete& p) const; 
        
    private:

    	DcNet d;
    	int id_paquetes;

    /*********************************************************************
     * TODO: Va a ser necesario instanciar privadamente un Modulo DCNet *
     * con el cuál interactuar. Además, pueden declarar todas las        *
     * funciones auxiliares que les hagan falta.                         *
     *********************************************************************/

}; // class Driver


} // namespace aed2

#endif // DRIVER_H_

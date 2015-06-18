#ifndef DCNET_H
#define DCNET_H
//#include <tuple>
#include "Pc.h"
#include "Paquete.h"
#include "../Conjunto/Conjunto.h"
using namespace std;
using namespace aed2;


class DcNet
{
    public:
        // DcNet(const Red&);  
        // void anadirPaquete(const Paquete&);
        // void avanzarSegundo();
        // Red verRed() const;
        // Lista<Pc> recorrido(const Paquete&) const;
        // int enviados(const Pc&) const;
        // Conjunto<Paquete> paquetes(const Pc&) const;
        // bool enTransito?(const Paquete&) const;
        Pc masEnviado() const;
    private:       
        // DiccTrie<Pc,Definicion> paquetes;
        // tuple<Pc,int> masEnviados;
        // Red red;
        // DiccAvl<Pc,DiccAvl<Pc,Pc>>
        Pc aux;
};





#endif // DCNET_H



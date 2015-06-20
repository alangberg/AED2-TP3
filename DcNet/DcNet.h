#ifndef DCNET_H
#define DCNET_H
//#include <tuple>
#include "Pc.h"
#include "Paquete.h"
#include "Definicion.h"
#include "../Red/Red.h"
#include "../Conjunto/Conjunto.h"
#include "../avl/DiccAvl.h"
using namespace std;
using namespace aed2;


class DcNet
{
    public:
        DcNet(const Red&);  
        void anadirPaquete(const Paquete&);
        void avanzarSegundo();
        Red verRed() const;
        Lista<Pc> recorrido(const Paquete&) const;
        int enviados(const Pc&) const;
        Conjunto<Paquete> paquetes(const Pc&) const;
        bool enTransito(const Paquete&) const;
        Pc masEnviados() const;
    private:       
        Dicc<Pc,Definicion> pc_paquetes; //DiccTrie<Pc,Definicion> paquetes;
        Pc pc_masEnviados;
        int cant_MasEnviados;
        //tuple<Pc,int> masEnviados; Hace falta??
        Red red;
        DiccAvl< Pc,DiccAvl<Pc,Pc> > siguientes;
};





#endif // DCNET_H



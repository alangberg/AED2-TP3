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
        DcNet();
        DcNet(const Red&);  
        void anadirPaquete(const Paquete&);
        void avanzarSegundo();
        const Red verRed() const;
        Lista<Pc> recorrido(const Paquete&) const;
        int enviados(const Pc&) const;
        Avl<Paquete> paquetes(const Pc&) const;
        bool enTransito(const Paquete&) const;
        Pc masEnviados() const;
        DcNet& operator=(const DcNet& otro);

    private:
        struct Tupla {           


            Tupla(const Paquete& p, const Lista<Pc>& l, const Pc& cp) : compu(cp), paq(p), list(l){}

            const Paquete Prim() const{
                return paq;
            }

            const Lista<Pc> Seg() const{
                return list;
            }

            const Pc Ter() const{
                return compu;
            }
            
            Paquete paq;
            Lista<Pc> list;
            Pc compu;
        };


        Dicc<Pc,Definicion> pc_paquetes; //DiccTrie<Pc,Definicion> pc_paquetes;
        Pc pc_masEnviados;
        int cant_MasEnviados;
        Red red;
        Dicc< Pc,Dicc<Pc,Pc> > siguientes; // DiccTrie. avl no respetaba complejidad
};





#endif // DCNET_H



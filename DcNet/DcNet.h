#ifndef DCNET_H
#define DCNET_H
//#include <tuple>
#include "Pc.h"
#include "Paquete.h"
#include "Definicion.h"
#include "../Red/Red.h"
#include "../Conjunto/Conjunto.h"
#include "../Conjunto/DiccTrie.h"
#include "../avl/DiccAvl.h"
using namespace std;
using namespace aed2;


class DcNet
{
    public:
        DcNet();
        DcNet(const Red&);  
        void anadirPaquete(const Pakete&);
        void avanzarSegundo();
        const Red verRed() const;
        Lista<Pc> recorrido(const Pakete&);
        int enviados(const Pc&);
        Avl<Pakete> paquetes(const Pc&);
        bool enTransito(const Pakete&);
        Pc masEnviados() const;
        DcNet& operator=( DcNet& otro);

    private:
        struct Tupla {           


            Tupla(const Pakete& p, const Lista<Pc>& l, const Pc& cp) : compu(cp), paq(p), list(l){}

            const Pakete Prim() const{
                return paq;
            }

            const Lista<Pc> Seg() const{
                return list;
            }

            const Pc Ter() const{
                return compu;
            }
            
            Pakete paq;
            Lista<Pc> list;
            Pc compu;
        };


        DiccString<Definicion> pc_paquetes;
        Pc pc_masEnviados;
        int cant_MasEnviados;
        Red red;
        DiccString<DiccString<Pc> > siguientes; 
};





#endif // DCNET_H



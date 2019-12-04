#ifndef Pierna_H_INCLUDED
#define Pierna_H_INCLUDED

#include "aux.h"
#include "esfera.h"
#include "cilindro.h"
#include "cubo.h"


// *****************************************************************************
//
// Clase Pierna: La pierna de Bender
//
// *****************************************************************************

class Pierna{
    private:
        Esfera * esfera_sup=nullptr;
        Cubo * pie=nullptr;
        Cilindro * cilindro=nullptr;
    public:
        Pierna(Material m,Tupla3f color);   
        void draw(int modo,bool puntos,bool lineas,bool solido,bool tapas);
};


#endif

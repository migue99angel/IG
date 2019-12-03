#ifndef Brazo_H_INCLUDED
#define Brazo_H_INCLUDED

#include "aux.h"
#include "esfera.h"
#include "cilindro.h"


// *****************************************************************************
//
// Clase Brazo: El brazo de Bender
//
// *****************************************************************************

class Brazo{
    private:
        Esfera * esfera_sup=nullptr;
        Esfera * esfera_inf=nullptr;
        Cilindro * cilindro=nullptr;
        float angulo;
        const int incremento = 1;
    public:
        Brazo(Material m, Tupla3f color);  
        void draw(int modo,bool puntos,bool lineas,bool solido,bool tapas);  
        void moverBrazo();
        inline float getHombro(){return this->esfera_sup->getRadio();}
};


#endif

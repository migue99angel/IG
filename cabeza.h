#ifndef Cabeza_H_INCLUDED
#define Cabeza_H_INCLUDED

#include "aux.h"
#include "esfera.h"
#include "cilindro.h"


// *****************************************************************************
//
// Clase Cabeza: La cabeza de Bender
//
// *****************************************************************************

class Cabeza{
    private:
        Esfera * little_esfera=nullptr;
        Esfera * esfera=nullptr;
        Cilindro * cilindro=nullptr;
        Cilindro * little_cilindro=nullptr;
        Esfera * ojo_izq = nullptr;
        Esfera * ojo_der = nullptr;
        Esfera * pupila_izq = nullptr;
        Esfera * pupila_der = nullptr;
        int x = 0;

    public:
        Cabeza(Material m,Tupla3f color);    
        void draw(int modo,bool puntos,bool lineas,bool solido,bool tapas);
        inline void setAlturaAntena(int valor){ this->x += valor; }
        inline int getAlturaAntena(){return x;}
};


#endif

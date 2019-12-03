#ifndef Bender_H_INCLUDED
#define Bender_H_INCLUDED

#include "aux.h"
#include "pierna.h"
#include "brazo.h"
#include "cabeza.h"


// *****************************************************************************
//
// Clase Bender (Modelo jerárquico). Práctica 4
//
// *****************************************************************************

class Bender{
    private:
        Pierna * pierna_izq = nullptr;
        Pierna * pierna_der = nullptr;
        Brazo * brazo_izq = nullptr;
        Brazo * brazo_der = nullptr;
        Cabeza * cabeza = nullptr;
        Cilindro * tronco = nullptr;
    public:
        Bender(Material m);   
        void draw(int modo,bool puntos,bool lineas,bool solido,bool tapas); 
};


#endif

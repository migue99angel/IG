// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luz.h

//
// #############################################################################

#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"
class Luz
{
    public:
        Luz();
        void activar();
    protected:
        Tupla4f posicion;
        GLenum id;
        Tupla4f colorAmbiente;    
        Tupla4f colorDifuso;
        Tupla4f colorEspecular;

};

#endif
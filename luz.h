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
        //Si el booleano esta a true es posicional, si no, es direccional
        bool tipo;
            //Cambiar ángulo
    virtual void variarAnguloAlpha(float incremento){};
    virtual void variarAnguloBeta(float incremento){};
};

#endif
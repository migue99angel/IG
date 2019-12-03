// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzposicional.h

//
// #############################################################################

#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "luz.h"


class LuzPosicional : public Luz
{
    public:
        LuzPosicional(Tupla3f pos,GLenum idLuzOpenGL,Tupla4f colorAmbiente,Tupla4f colorDifuso,Tupla4f colorEspecular);
        inline bool esDireccional(){return false;}
};

#endif
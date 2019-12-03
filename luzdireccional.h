// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzdireccional.h

//
// #############################################################################

#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "luz.h"


class LuzDireccional : public Luz
{
    protected:
        float alpha;
        float beta;
        
    public:
        LuzDireccional(Tupla2f direccion,GLenum idLuzOpenGL,Tupla4f colorAmbiente,Tupla4f colorDifuso,Tupla4f colorEspecular);
        //Cambiar ángulo
        void variarAnguloAlpha(float incremento)override;
        void variarAnguloBeta(float incremento)override;
        void posUpdate();
        inline bool esDireccional(){return true;}
};

#endif
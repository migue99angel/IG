#include "luzposicional.h"

//Constructor por defecto
LuzPosicional::LuzPosicional(Tupla3f pos,GLenum idLuzOpenGL,Tupla4f colorAmbiente,Tupla4f colorDifuso,Tupla4f colorEspecular)
{
    this->posicion(0)=pos(0);
    this->posicion(1)=pos(1);
    this->posicion(2)=pos(2);
    this->posicion(3)=1;

    this->id = idLuzOpenGL;

    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;


}


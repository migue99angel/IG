#include "luzdireccional.h"

//Constructor por defecto
LuzDireccional::LuzDireccional(Tupla2f direccion,GLenum idLuzOpenGL,Tupla4f colorAmbiente,Tupla4f colorDifuso,Tupla4f colorEspecular){

    //Falta calcular la direccion a traves del alfa
    this->id = idLuzOpenGL;

    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;

    this->activar();
}


#include "luzdireccional.h"

//Constructor por defecto
LuzDireccional::LuzDireccional(Tupla2f direccion,GLenum idLuzOpenGL,Tupla4f colorAmbiente,Tupla4f colorDifuso,Tupla4f colorEspecular){
    alpha = direccion[0];
    beta = direccion[1];

    posUpdate();

    this->posicion[3] = 0.0; // Para luz direccional

    //Falta calcular la direccion a traves del alfa
    this->id = idLuzOpenGL;

    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;

}

//Cambiar ángulo
void LuzDireccional::variarAnguloAlpha(float incremento){
    alpha+=incremento;
    posUpdate();
}
void LuzDireccional::variarAnguloBeta(float incremento){
    beta+=incremento;
    posUpdate();
}

void LuzDireccional::posUpdate(){
    this->posicion[0] = sin(alpha*(M_PI/180));
    this->posicion[1] = sin(beta*(M_PI/180));
    this->posicion[2] = sin(alpha*(M_PI/180)) * cos(beta*(M_PI/180));
}


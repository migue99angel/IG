#include "material.h"
Material::Material(){}

Material::Material(Tupla4f ambiente,Tupla4f especular, Tupla4f difuso, float brillo){
    this->ambiente = ambiente;
    this->especular = especular;
    this->difuso = difuso;
    this->brillo = brillo;
}

void Material::aplicar(){
    glMaterialfv(GL_FRONT,GL_AMBIENT,this->ambiente);
    glMaterialfv(GL_FRONT,GL_SPECULAR,this->especular);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,this->difuso);
    const GLfloat * b = new GLfloat(brillo);
    glMaterialfv(GL_FRONT,GL_SHININESS, b);
}
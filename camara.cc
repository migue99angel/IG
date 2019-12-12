#include "camara.h"

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up , int tipo, float left, float right,float near,float far)
{
    this->eye = eye;
    this->at = at;
    this->up = up;
    this->tipo = tipo;
    this->left = left;
    this->right = right;
    this->near = near;
    this->far = far;
}

void Camara::rotarXExaminar(float angle)
{

}

void Camara::rotarYExaminar(float angle)
{

}

void Camara::rotarZExaminar(float angle)
{

}

void Camara::rotarXFirstPerson(float angle)
{
    
}

void Camara::rotarYFirstPerson(float angle)
{

}

void Camara::rotarZFirstPerson(float angle)
{

}

void Camara::mover(float x, float y, float z)
{

}

void Camara::zoom(float factor)
{

}

void Camara::setObserver()
{

}

void Camara::setProyeccion()
{
    
}

void Camara::girar(int x, int y)
{
    this->rotarXExaminar(x);
    this->rotarYExaminar(y);
}
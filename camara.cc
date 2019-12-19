#include "camara.h"

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up , int tipo, float width, float high,float near,float far)
{
    this->eye = eye;
    this->at = at;
    this->up = up.normalized();

    this->tipo = tipo;
    this->near = near;
    this->far = far;

    //Calculo el aspecto que es la relación entre el ancho y el alto 
    this->aspect = width/high;
    
    this->left = high/2;
    this->top = width/2;

    //La diferencia del vector at y el vector eye nos dará el vector director
    this->Vd(0) = at(0) - eye(0);
    this->Vd(1) = at(1) - eye(1);
    this->Vd(2) = at(2) - eye(2);

    //Calculamos la Vx que es perpendicular a up y Vd
    this->Vx = this->Vd.cross(up);
    this->Vx = Vx.normalized();
    //Vy es perpendicular a Vx y Vd
    this->Vy = this->Vx.cross(Vd);
    this->Vy = Vy.normalized();
    //Calculo el angulo de visión fovY. atan devuelve radianes y gluPerpective trabaja en grados
    this->fovY = (atan(near/high) * 180/M_PI);
}

void Camara::rotarXExaminar(float angle)
{
    examinar(0,angle);
}

void Camara::rotarYExaminar(float angle)
{
    examinar(1,angle);
}

void Camara::rotarZExaminar(float angle)
{
    examinar(2,angle);
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
/*******************************************
 * Función que reasigna las coordenadas de eye
********************************************/
void Camara::mover(float x, float y, float z)
{
    this->eye = {x,y,z};
}

void Camara::zoom(float factor)
{

}
/***********************************************
 * Función que realiza la llamada a gluLookAt
 ***********************************************/ 
void Camara::setObserver()
{
    gluLookAt(eye(0),eye(1),eye(2),at(0),at(1),at(2),up(0),up(1),up(2));
}

void Camara::setProyeccion()
{
    if(tipo == 0)
        glOrtho(-left,left,-top,top,near,far);

    if(tipo == 1)
        gluPerspective(fovY,aspect,near,far);    
}

void Camara::girar(int x, int y)
{
    this->rotarXExaminar(x);
    this->rotarYExaminar(y);
}
/**********************************************************************
* Funcion que rota un vector(el vector director) sobre un eje definido
* 0 para el eje x
* 1 para el eje y
* 2 para el eje z
* angulo: el angulo que se va a rotar
***********************************************************************/
void Camara::examinar(int eje,float angulo)
{
    Tupla3f Up_recal,V_ex;
    //Actualizamos el vector director

    V_ex(0) = eye(0) - at(0);
    V_ex(1) = eye(1) - at(1);
    V_ex(2) = eye(2) - at(2);

    angulo = (angulo * 180/M_PI) ;
    
    switch (eje)
    {
    case 0:
        V_ex = RotarEjeArbitrario(Vy,V_ex,angulo);
        Up_recal = RotarEjeArbitrario(Vy,up,angulo);
        this->Vx = RotarEjeArbitrario(Vy,Vx,angulo); 
        break;
    case 1:
        V_ex = RotarEjeArbitrario(Vx,V_ex,angulo);
        Up_recal = RotarEjeArbitrario(Vx,up,angulo);
        this->Vy = RotarEjeArbitrario(Vx,Vy,angulo); 
        break;
    case 2:

        break;
    }        
    //Actualizamos el up
    this->up = Up_recal;

    //Recalculo el eye
    mover( V_ex(0) + at(0) , V_ex(1) + at(1) , V_ex(2) + at(2) );
    
}
/***************************************************************************
 * Función que multiplica la matriz de rotación de un eje por un vector
 ***************************************************************************/
Tupla3f Camara::RotarEjeArbitrario(Tupla3f eje,Tupla3f vector,float angulo)
{
    Tupla3f mRotacion = {0,0,0};
    
    mRotacion(0) = vector(0)*(cos(angulo) + pow(eje(0),2) * (1 - cos(angulo))) + vector(1)*(eje(1)*eje(0)*(1-cos(angulo)) + eje(2)*sin(angulo)) + vector(2)*(eje(2)*eje(0)*(1-cos(angulo)) - eje(1)*sin(angulo)) ;
    mRotacion(1) = vector(0)*(eje(0)*eje(1)*(1-cos(angulo)) - eje(2)*sin(angulo)) + vector(1)*(cos(angulo) + pow(eje(1),2)*(1 - cos(angulo))) + vector(2)*(eje(2)*eje(1)*(1-cos(angulo)) + eje(0)*sin(angulo));
    mRotacion(2) = vector(0)*(eje(2)*eje(0)*(1-cos(angulo)) + eje(1)*sin(angulo)) + vector(1)*(eje(2)*eje(1)*(1-cos(angulo)) - eje(0)*sin(angulo)) + vector(2)*(cos(angulo) + pow(eje(2),2) * (1 - cos(angulo)));

    return mRotacion;
}
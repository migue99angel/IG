#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

class Camara{
    private:
        Tupla3f eye,at,up;
        Tupla3f Vx; //Eje x del sistema de coordenadas de vista
        Tupla3f Vy; //Eje y del sistema de coordenadas de vista
        Tupla3f Vd; //Diferencia entre el eye y el at (Vector director)
        int tipo;  // 0 para Ortogonal 1 para Perspectiva
        float left, near, far;
        float fovY;//Field of view en el eje Y
        float aspect; //Relacion entre el ancho y el alto
        float  top;
        bool seleccion = false;

    public:
        Camara(Tupla3f eye, Tupla3f at, Tupla3f up , int tipo, float width, float high,float near,float far);
        void rotarXExaminar(float angle);
        void rotarYExaminar(float angle);
        void rotarXFirstPerson(float angle);
        void rotarYFirstPerson(float angle);
        void mover(float x, float y, float z);
        void zoom(float factor);    
        void setObserver();
        void setProyeccion();
        void girar(int x, int y);
        void girarPrimeraPersona(int x, int y);
        void examinar(int eje,float angulo);
        void rotarFirstPerson(int eje,float angulo);
        void setAt(Tupla3f seleccion);
        Tupla3f RotarEjeArbitrario(Tupla3f eje,Tupla3f vector,float angulo);
        inline float getAncho() {return this->left*2;}
        inline float getAlto() {return this->top*2;}
        inline bool getSeleccion(){return seleccion;}
        inline void setSeleccion(bool s){seleccion = s;}
};


#endif
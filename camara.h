#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

class Camara{
    private:
        Tupla3f eye;
        Tupla3f at;
        Tupla3f up;
        int tipo;  // 0 para Ortogonal 1 para Perspectiva
        float left, right, near, far;

    public:
        Camara(Tupla3f eye, Tupla3f at, Tupla3f up , int tipo, float left, float right,float near,float far);
        void rotarXExaminar(float angle);
        void rotarYExaminar(float angle);
        void rotarZExaminar(float angle);
        void rotarXFirstPerson(float angle);
        void rotarYFirstPerson(float angle);
        void rotarZFirstPerson(float angle);
        void mover(float x, float y, float z);
        void zoom(float factor);    
        void setObserver();
        void setProyeccion();
        void girar(int x, int y);
};


#endif
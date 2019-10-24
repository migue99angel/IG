
#include "cono.h"


Cono::Cono(int num_vert_perf,int num_instancias_perf,float r,float h){
    std::vector<Tupla3f> perfil;
    this->altura=h;
    this->radio=r;
    float x;
    float y;
    perfil.push_back(Tupla3f(0,altura,0));
    for(int i = 0; i < num_vert_perf; ++i){
        x=-(r*i)/h;
        y=((-x)*h+1)/r;
        if(x<radio && y<altura)
         perfil.push_back(Tupla3f(x,y,0));
    }
    this->crearMalla(perfil,num_instancias_perf,true,true);
}


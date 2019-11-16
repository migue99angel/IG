
#include "cono.h"


Cono::Cono(int num_vert_perf,int num_instancias_perf,float r,float h,Tupla3f c){
    std::vector<Tupla3f> perfil;
    this->altura=h;
    this->radio=r;
    
    perfil.push_back(Tupla3f(radio,0,0));
    perfil.push_back(Tupla3f(0,altura,0));


    this->crearMalla(perfil,num_instancias_perf,true);
    this->aniadirColor(c);

}


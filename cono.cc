
#include "cono.h"


Cono::Cono(int num_vert_perf,int num_instancias_perf,float r,float h){
    std::vector<Tupla3f> perfil;
    this->altura=h;
    this->radio=r;
    float x;
    float y;
    perfil.push_back(Tupla3f(0,altura,0));
    //Para obtener las cordenadas x e y he calculado la recta que pasa por los puntos 
    //(0,h) y (r,0), he despejado la x y la he calculado dando valores, luego la
    //sustituyo en la fórmula para la obtención de y y obtengo valores que están en la recta que 
    //tomaré como perfil 
    for(int i = 0; i < num_vert_perf; ++i){
        x=-(r*i)/h;
        y=((-x)*h+1)/r;
        //Si no hacemos esta comprobación tomará una recta hacia el infinito
        if(x<radio && y<altura)
         perfil.push_back(Tupla3f(x,y,0));
    }
    this->crearMalla(perfil,num_instancias_perf,true,true);
}


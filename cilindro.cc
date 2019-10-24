#include "aux.h"
#include "malla.h"
#include "cilindro.h"

Cilindro::Cilindro(){}

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio){
    std::vector<Tupla3f> perfil;
    float altura_original=altura, aux=altura;

    for(int i = 0; i < num_vert_perfil; ++i){
        perfil.push_back(Tupla3f(radio,altura_original,0));
        altura_original=altura_original/2;
    }
    
    this->crearMalla(perfil,num_instancias_perf,true,true);
    this->color.resize(v.size());
}
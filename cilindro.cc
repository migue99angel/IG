#include "aux.h"
#include "malla.h"
#include "cilindro.h"


Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio,Tupla3f c){
    std::vector<Tupla3f> perfil;

    perfil.push_back(Tupla3f(radio,altura,0));
    perfil.push_back(Tupla3f(radio,0,0));

  
    this->crearMalla(perfil,num_instancias_perf,true);
    this->aniadirColor(Tupla3f(c));
    calcular_normales();
}
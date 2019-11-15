#include "aux.h"
#include "malla.h"
#include "esfera.h"

Esfera::Esfera(int num_vert_perf,int num_instancias_perf,float r,Tupla3f c)
{
    std::vector<Tupla3f> perfil;
    this->radio = r;
    float  x, y;
    v.clear();

    for(int i=1; i<=num_vert_perf-1; i++){


            x = sin((i*M_PI)/num_vert_perf )*radio;
            y = cos((i*M_PI)/num_vert_perf )*radio; 

            perfil.push_back(Tupla3f(x,y,0));

    }

    this->crearMalla(perfil,num_instancias_perf,true);
    this->aniadirColor(c);
    calcular_normales();

}
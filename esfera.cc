#include "aux.h"
#include "malla.h"
#include "esfera.h"

Esfera::Esfera(int num_vert_perf,int num_instancias_perf,float r,Tupla3f c)
{
    std::vector<Tupla3f> perfil;
    this->radio = r;
    float incr = M_PI/num_vert_perf, x, y, z;
    v.clear();

    for(int i=0; i<=num_vert_perf; i++){

            x = cos( (M_PI/2) + i*(2*M_PI/2)/num_vert_perf )*radio;
            y = sin( (M_PI/2) + i*(2*M_PI/2)/num_vert_perf)*radio; 
            z = 0;

            perfil.push_back(Tupla3f(x,y,z));

        }
    
    this->crearMalla(perfil,num_instancias_perf,false,false);
    this->aniadirColor(c);
}
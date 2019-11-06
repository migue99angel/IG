#include "aux.h"
#include "malla.h"
#include "esfera.h"

Esfera::Esfera(int num_vert_perf,int num_instancias_perf,float r,Tupla3f c)
{
    std::vector<Tupla3f> perfil;
    this->radio = r;
    float incr = M_PI/20, x, y, z;
    v.clear();

    for(float i=0; i < M_PI; i += incr){
        for(float j=0;j<2*M_PI;j += incr){
            x = radio * ((float) sin(i))*((float) cos(j)); 
            y = radio * ((float) cos(i)); 
            z = radio * ((float) sin(i))*((float) sin(j));

            perfil.push_back(Tupla3f(x,z,y));
        }
    }
    this->crearMalla(perfil,num_instancias_perf,false,false);
    this->aniadirColor(c);
}
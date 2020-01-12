#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"
class Material{
    private:

        Tupla4f ambiente;
        Tupla4f especular;
        Tupla4f difuso;
        float brillo;

    public:
        Material();
        Material(Tupla4f ambiente,Tupla4f especular, Tupla4f difuso, float brillo);
        void aplicar();
        inline Tupla4f getAmbiente(){return this->ambiente;}
        inline Tupla4f getEspecular(){return this->especular;}
        inline Tupla4f getDifuso(){return this->difuso;}
        inline void setAmbiente(Tupla4f t){ this->ambiente = t;}
        inline void setEspecular(Tupla4f t){ this->especular = t;}
        inline void setDifuso(Tupla4f t){ this->difuso = t;}

};

#endif
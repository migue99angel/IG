#ifndef Bender_H_INCLUDED
#define Bender_H_INCLUDED

#include "aux.h"
#include "pierna.h"
#include "brazo.h"
#include "cabeza.h"


// *****************************************************************************
//
// Clase Bender (Modelo jerárquico). Práctica 4
//
// *****************************************************************************

class Bender{
    private:
        Pierna * pierna_izq = nullptr;
        Pierna * pierna_der = nullptr;
        Brazo * brazo_izq = nullptr;
        Brazo * brazo_der = nullptr;
        Cabeza * cabeza = nullptr;
        Cilindro * tronco = nullptr;
        int v_animacion;
        bool hacia_delante_pierna_der;
        bool hacia_delante_pierna_izq;
        bool haciaAtras = false;
        bool paso;
        int n_pasos;
    public:
        Bender(Material m,int v_animacion);   
        void draw(int modo,bool puntos,bool lineas,bool solido,bool tapas); 
        void moverPiernaIzq();
        void moverPiernaDer();
        void moverBrazoIzq();
        void moverBrazoDer();
        void moverCuello();
        void mover(int animacion);
        void andar();
        void andarHaciaAtras();
        void setVelocidad(float v);
        inline int getNPasos(){return n_pasos;}
        inline bool getAtras(){return this->haciaAtras;}
        inline void setAtras(bool atras){this->haciaAtras = atras;}
        float anguloPiernaIzq,anguloPiernaDer,anguloBrazoIzq,anguloBrazoDer,anguloCuello;
};


#endif

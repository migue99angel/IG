// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cilindro.h

//
// #############################################################################

#ifndef Cilindro_H_INCLUDED
#define Cilindro_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cilindro con centro en el origen y lado unidad por defecto

class Cilindro : public ObjRevolucion
{
   private:
      float altura;
      float radio;
   public:
   Cilindro( int num_vert_perfil=2,  int num_instancias_perf=20,  float altura=40,  float radio=5,Tupla3f c=Tupla3f(0.0,0.5,0.5)) ;
   inline float getAltura() {return altura;}
   inline float getRadio() {return radio;}
} ;




#endif

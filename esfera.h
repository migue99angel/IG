// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: esfera.h

//
// #############################################################################

#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// esfera con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class Esfera : public ObjRevolucion
{
   public:
   Esfera(int num_vert_perf=20,int num_instancias_perf=20,float r=20,Tupla3f c=Tupla3f(1.0,0,0));
   private:
   float radio;

} ;


#endif
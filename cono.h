// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cono.h

//
// #############################################################################

#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cono con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class Cono : public ObjRevolucion
{
   public:
   Cono(int num_vert_perf=10,int num_instancias_perf=20,float r=20,float h=20);
   private:
   float altura, radio;

} ;


#endif
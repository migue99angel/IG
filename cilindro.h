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
// (tiene 9 vertices y 6 caras)

class Cilindro : public ObjRevolucion
{
   public:
   Cilindro( int num_vert_perfil=5,  int num_instancias_perf=50,  float altura=15,  float radio=10,Tupla3f c=Tupla3f(0,0,1.0)) ;
} ;




#endif

#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class Cuadro : public Malla3D
{
   private:
      float lado;
   public:
      Cuadro();
      Cuadro(float l);
      void obtenerPuntosCoordenadas();
} ;

#endif
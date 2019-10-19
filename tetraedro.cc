#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{

   // inicializar la tabla de vértices
   Tupla3f a(-MAX/2,-MAX/2,-MAX/2), b(0,-MAX/2,MAX/2),c(MAX/2,-MAX/2,-MAX/2),d(0,MAX/2,0);
   v.push_back(a);
   v.push_back(b);
   v.push_back(c);
   v.push_back(d);
    
   // inicializar la tabla de caras o triángulos:
   Tupla3i ver1(0,1,3),ver2(1,2,3),ver3(2,0,3),ver4(0,2,1);
   f.push_back(ver1);
   f.push_back(ver2);
   f.push_back(ver3);
   f.push_back(ver4);
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

}


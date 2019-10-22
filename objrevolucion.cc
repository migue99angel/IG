#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include <math.h> //Para usar M_PI


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {

}
//Para completar este constructor es necesario usar la funcion read_vertices
//de la clase ply_reader, obtener el perfil original y luego llamar a crearMalla

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   std::vector<Tupla3f> perfil;
   ply::read_vertices(archivo,perfil);
   crearMalla(perfil,num_instancias);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
    crearMalla(archivo,num_instancias);
}
//El tamaño de perfil_original se corresponde con el M del pseudocódigo
//y num_instancias_perfil es el valor de N
//Se debe añadir un bool para las tapas
void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
   v.clear();
   //Aquí creo las instancias de los perfiles
   for(int i=0;i<num_instancias;++i){
      for(int j=0;j<perfil_original.size();++j){
         Tupla3f v_aux;
         v_aux(0) = cos((2*M_PI*i)/num_instancias)*perfil_original[j][0];
         v_aux(1) = perfil_original[j][1];
         v_aux(2) = sin((2*M_PI*i)/num_instancias)*perfil_original[j][0];
         v.push_back(v_aux);
      }
   }

   f.clear();
   int a,b;
   //Aquí creo los triangulos
   for(int i=0;i<num_instancias;i++){
      for(int j=0;j<perfil_original.size()-1;j++){
         a=perfil_original.size()*i+j;
         b=perfil_original.size()*((i+1)%num_instancias)+j;
         Tupla3i tr(a,b,b+1),tr2(a,b+1,a+1);
         f.push_back(tr);
         f.push_back(tr2);
      }
   }
}

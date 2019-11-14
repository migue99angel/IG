#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include <math.h> //Para usar M_P
#include <stack>



// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion(){}
//Para completar este constructor es necesario usar la funcion read_vertices
//de la clase ply_reader, obtener el perfil original y luego llamar a crearMalla

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapas)
{
   std::vector<Tupla3f> perfil;
   ply::read_vertices(archivo,perfil);
   crearMalla(perfil,num_instancias, tapas);
   aniadirColor(Tupla3f(0,0,1.0));
   if(nv.empty())
      calcular_normales();
      
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapas)
{
    crearMalla(archivo,num_instancias, tapas);
    aniadirColor(Tupla3f(0,0,1.0));
    if(nv.empty())
      calcular_normales();
      
}
//El tamaño de perfil_original se corresponde con el M del pseudocódigo
//y num_instancias_perfil es el valor de N
//Se debe añadir un bool para las tapas
void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias,bool tapas)
{
   if(perfil_original[0](1) > perfil_original[perfil_original.size()-1](1))
     perfil_original=generarOrdenInverso(perfil_original);

   v.clear();
   //v.resize(num_instancias*perfil_original.size());
   //Aquí creo las instancias de los perfiles


   for(int i=0;i<num_instancias;i++){
      for(int j=0;j<perfil_original.size();j++){
         Tupla3f v_aux;
         v_aux(0) = sin((2*M_PI*i)/num_instancias)*perfil_original[j][0];
         v_aux(1) = perfil_original[j][1];
         v_aux(2) = cos((2*M_PI*i)/num_instancias)*perfil_original[j][0];
         v.push_back(v_aux);
      }
   }

   f.clear();
   int a,b;
   //Aquí creo los triangulos
   for(int i=0;i<num_instancias;i++){
      for(int j=0;j<perfil_original.size()-1;j++)
      {
         a=perfil_original.size()*i+j;
         b=perfil_original.size()*((i+1)%num_instancias)+j;
         Tupla3i tr(a,b,b+1),tr2(a,b+1,a+1);
         f.push_back(tr);
         f.push_back(tr2);
      }
   }
   Tupla3f tapaSup, tapaInf;
   if(tapas)
   {
      if(existeTapaSup(perfil_original,num_instancias))
      {
         tapaSup = perfil_original[0];
         perfil_original.erase(perfil_original.begin());
      }
      else{
         tapaSup(0) = 0.0;
         tapaSup(1) = perfil_original[0](1);
         tapaSup(2) = 0.0;
      }
   
      if(existeTapaInf(perfil_original,num_instancias))
      {
         tapaInf = perfil_original[perfil_original.size()-1];
         perfil_original.pop_back();
      }
      else{
         tapaInf(0) = 0.0;
         tapaInf(1) = perfil_original[perfil_original.size()-1](1);
         tapaInf(2) = 0.0;
      }

        // Introducimos los vértices
        this->v.push_back(tapaSup);
        this->v.push_back(tapaInf);

        // Generamos los triángulos
        for(int i=0; i < num_instancias; i++){
            Tupla3i caraSup(perfil_original.size()*((i+1)%num_instancias),perfil_original.size()*i,num_instancias*perfil_original.size());
            this->f.push_back(caraSup);
        }

        for(int i=0; i < num_instancias; i++){
            Tupla3i caraInf(num_instancias*perfil_original.size()+1,perfil_original.size()*(i+1)-1,perfil_original.size()*(((i+1)%num_instancias)+1)-1);
            this->f.push_back(caraInf);
        }
    }
}


//Función que comprueba que el polo sur coincide con el centro de la tapa inferior
bool ObjRevolucion::existeTapaInf(std::vector<Tupla3f> perfil_original, int num_instancias)
{
   return (perfil_original[perfil_original.size()-1](0) == 0.0 && perfil_original[perfil_original.size()-1](1) == 0.0);     
}

//Función que comprueba que el polo norte coincide con el centro de la tapa superior
bool ObjRevolucion::existeTapaSup(std::vector<Tupla3f> perfil_original, int num_instancias)
{
   return (perfil_original[0](0) == 0.0 && perfil_original[0](1) == 0.0);
}
//Función que genera la inversa del perfil con ayuda de una pila auxiliar
std::vector<Tupla3f> ObjRevolucion::generarOrdenInverso(std::vector<Tupla3f> perfil_original)
{
   std::stack<Tupla3f> pila;

    for(int i=0; i < perfil_original.size(); i++){
        pila.push(perfil_original[i]);
    }

    perfil_original.clear();

    while(!pila.empty()){
       perfil_original.push_back(pila.top());
       pila.pop();
    }

    return perfil_original;

}

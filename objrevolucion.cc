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
   this->M = archivo.size();
   this->N  =num_instancias;
   std::vector<Tupla3f> perfil;
   ply::read_vertices(archivo,perfil);
   crearMalla(perfil,num_instancias, tapas);
   aniadirColor(Tupla3f(0,0,1.0));

   //Como ya he creado las caras y el objeto revolución ya puedo calcular las normales
   if(nv.empty())
      calcular_normales();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapas)
{
   this->perf_original = archivo;
   crearMalla(archivo,num_instancias, tapas);
   aniadirColor(Tupla3f(0,0,1.0));

   //Como ya he creado las caras y el objeto revolución ya puedo calcular las normales
   if(nv.empty())
      calcular_normales();
      
}
//El tamaño de perfil_original se corresponde con el M del pseudocódigo
//y num_instancias_perfil es el valor de N
//Se debe añadir un bool para las tapas
void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias,bool tapas)
{
   this->perf_original = perfil_original;

   if(perfil_original[0](1) > perfil_original[perfil_original.size()-1](1))
     perfil_original=generarOrdenInverso(perfil_original);

   v.clear();
   this->num_instancias = num_instancias;
   Tupla3f tapaSup, tapaInf;
   //Compruebo la existencia de tapas, en caso de que exista el polo correspondiente lo saco
   if(existeTapaSup(perfil_original,num_instancias))
   {
      tapaSup = perfil_original[0];
      perfil_original.erase(perfil_original.begin());
   }
   //Si no existe el polo correspondiente lo genero
   else{
      tapaSup = {0.0,perfil_original[0](1),0.0};
   }

   if(existeTapaInf(perfil_original,num_instancias))
   {
      tapaInf = perfil_original[perfil_original.size()-1];
      perfil_original.pop_back();
   }
   else{
      tapaInf = {0.0,perfil_original[perfil_original.size()-1](1),0.0};
   }
   
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

   //Añado los polos
   v.push_back(tapaSup);
   v.push_back(tapaInf);
   
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
   // Finalmente genero los triangulos de las tapas
        for(int i=0; i < num_instancias; i++){
            Tupla3i caraSup(perfil_original.size()*((i+1)%num_instancias),perfil_original.size()*i,num_instancias*perfil_original.size());
            this->f.push_back(caraSup);
            //Esta variable cuenta el múmero de triángulos de las tapas para la visualización opcional de ellas o no en tiempo de ejecucion
            contador++;
        }

        for(int i=0; i < num_instancias; i++){
            Tupla3i caraInf(num_instancias*perfil_original.size()+1,perfil_original.size()*(i+1)-1,perfil_original.size()*(((i+1)%num_instancias)+1)-1);
            this->f.push_back(caraInf);
            //Esta variable cuenta el múmero de triángulos de las tapas para la visualización opcional de ellas o no en tiempo de ejecucion
            contador++;
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


void ObjRevolucion::draw_ModoInmediato(char L,bool tapas)
{

  // visualizar la malla usando glDrawElements,
  //Habilito el uso de un array de vértices
  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer(3, GL_FLOAT, 0,v.data() );


  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, 0, nv.data());

  //Activo el uso del vector de colores
  glEnableClientState(GL_COLOR_ARRAY);
  //Elijo el comienzo de dicho vector 
  switch (L)
  {
   case 'P':
     glColorPointer(3,GL_FLOAT,0,colorPuntos.data());break;
   case 'L':
     glColorPointer(3,GL_FLOAT,0,colorLinea.data()); break;
  default:
      glColorPointer(3,GL_FLOAT,0,color.data()); break;
  }
   if(!ct.empty()){
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2,GL_FLOAT,0,ct.data());
   }  
   if(tapas)
      glDrawElements( GL_TRIANGLES, 3* f.size(), GL_UNSIGNED_INT, f.data() ) ;
   else
      glDrawElements( GL_TRIANGLES, 3*f.size()-contador*3, GL_UNSIGNED_INT, f.data() ) ;

 
  
  //Deshabilitar el array de vértices
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);

}
// -----------------------------------------------------------------------------
//Visualización en modo Chess
void ObjRevolucion::draw_Chess(bool tapas)
{

      if(f.size()%2 == 1)
         f.pop_back(); 

      for(int i=0;i<f.size();i+=2){
         fimpar.push_back(f[i]);
         fpar.push_back(f[i+1]);
      }
 
    
      cimpar.resize(color.size());
      cpar.resize(color.size());
      
      for(unsigned i = 0; i < cpar.size() ; i++){
         cpar[i]=Tupla3f(0.0,255.0,0.0);
         cimpar[i]=Tupla3f(0.0,0.0,255.0);
      }

      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_COLOR_ARRAY);
      glShadeModel(GL_FLAT);
      glVertexPointer(3,GL_FLOAT,0,v.data());

      glColorPointer(3,GL_FLOAT,0,cpar.data());
      glDrawElements(GL_TRIANGLES, fpar.size()*3, GL_UNSIGNED_INT ,fpar.data());

      glColorPointer(3,GL_FLOAT,0,cimpar.data());
      glDrawElements(GL_TRIANGLES, fimpar.size()*3, GL_UNSIGNED_INT ,fimpar.data());

      glDisableClientState(GL_COLOR_ARRAY);
      glDisableClientState( GL_VERTEX_ARRAY );


}

void ObjRevolucion::draw_ModoDiferido(char L,bool tapas)
{
   if(id_vbo_ver==0 && id_vbo_tri==0){
      id_vbo_ver=CrearVBO(GL_ARRAY_BUFFER,v.size()*3*sizeof(float),v.data());
      id_vbo_tri=CrearVBO(GL_ELEMENT_ARRAY_BUFFER,f.size()*3*sizeof(int),f.data());
   }
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   //especificar localización y formato de la tabla de vértices, habilitar tabla
   glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver ); //activar VBO de vértices
   glVertexPointer( 3, GL_FLOAT, 0, 0 ); //especifica formato y offset (=0)
   glBindBuffer( GL_ARRAY_BUFFER, 0 ); //desactivar VBO de vértices.
   glEnableClientState( GL_VERTEX_ARRAY ); //habilitar tabla de vértices
   
  switch (L)
  {
   case 'P':
     glColorPointer(3,GL_FLOAT,0,colorPuntos.data());
     break;
   case 'L':
     glColorPointer(3,GL_FLOAT,0,colorLinea.data());
     break;
  default:
      glColorPointer(3,GL_FLOAT,0,color.data());
     break;
  }

   if(!ct.empty()){
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2,GL_FLOAT,0,ct.data());
   }   

   glEnableClientState(GL_NORMAL_ARRAY);
   glNormalPointer(GL_FLOAT, 0, nv.data());
   //visualizar triángulos con glDrawElements (puntero a tabla == 0)
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri ); //activar VBO de triángulos
   if(tapas)
      glDrawElements( GL_TRIANGLES, 3* f.size(), GL_UNSIGNED_INT, 0 ) ;
   else
      glDrawElements( GL_TRIANGLES, 3* f.size() - num_instancias*3, GL_UNSIGNED_INT, 0 ) ;

   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); //desactivar VBO de triángulos

   //desactivar uso de array de vértices
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void ObjRevolucion::draw(int modo,bool puntos,bool lineas,bool solido,bool tapas)
{
   if(nv.empty())
      calcular_normales();
      
   mat->aplicar();
      if(this->text != nullptr){
      obtenerPuntosCoordenadas();
      this->text->activar();
   }

   if(glIsEnabled(GL_TEXTURE_2D) && this->text == nullptr)
      glDisable(GL_TEXTURE_2D); 
      
   if(puntos){
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      switch (modo)
      {
         case 1: draw_ModoInmediato('P',tapas); break;
         case 2: draw_ModoDiferido('P',tapas); break;
         case 3: draw_Chess(tapas); break;
         
      }
   }
   if(lineas){
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      switch (modo)
      {
         case 1: draw_ModoInmediato('L',tapas); break;
         case 2: draw_ModoDiferido('L',tapas); break;
         case 3: draw_Chess(tapas); break;
         
      }
   }
   if(solido){
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      switch (modo)
      {
         case 1: draw_ModoInmediato('F',tapas); break;
         case 2: draw_ModoDiferido('F',tapas); break;
         case 3: draw_Chess(tapas); break;
         
      }
   }   

}

void ObjRevolucion::obtenerPuntosCoordenadas()
{
   if(ct.empty())
   {
      CalcularDistanciasPerfil();
      std::vector<Tupla2f> aux;

      for( float i = 0; i < this->num_instancias; ++i ){
         for (float j = 0; j < M; ++j)
               aux.push_back({i / this->num_instancias , (float)this->distancias_perfil[j]/this->distancias_perfil[M-1]});
      }

      for(int i = aux.size()-1; i > 0; --i)
         ct.push_back(aux[i]);
   }
}

void ObjRevolucion::CalcularDistanciasPerfil()
{
   this->distancias_perfil.clear();
   this->distancias_perfil.push_back(0);

   for(int i = 1; i < this->perf_original.size(); ++i )
      distancias_perfil[i] = distancias_perfil[i-1] + calcularDistanciaVertices(perf_original[i-1],perf_original[i]);

}
/*
* Función que calcula la distancia entre dos vertices
*/
double ObjRevolucion::calcularDistanciaVertices(Tupla3f anterior, Tupla3f siguiente)
{
   double x = pow(anterior(0)-siguiente(0),2);
   double y = pow(anterior(1)-siguiente(1),2);
   double z = pow(anterior(2)-siguiente(2),2);

   return sqrt(x+y+z);
}
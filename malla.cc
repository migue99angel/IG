#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{
  // visualizar la malla usando glDrawElements,
  //Habilito el uso de un array de vértices
  glEnableClientState( GL_VERTEX_ARRAY );
  //indicar el formato y la dirección de memoria del array de vértices
  //(son tuplas de 3 valores float, sin espacio entre ellas)
  glVertexPointer(3, GL_FLOAT, 0,v.data() );
  //Activo el uso del vector de colores
  glEnableClientState(GL_COLOR_ARRAY);
  //Elijo el comienzo de dicho vector 
  glColorPointer(3,GL_FLOAT,0,color.data());

  //Sirve para que no se vea difuminado
  glShadeModel(GL_FLAT);
  //visualizar, indicando: tipo de primitiva y número de índices,
  //tipo de los índices y dirección de la tabla de índices
  glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT ,f.data());
  
  //Deshabilitar el array de vértices
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}

//Visualización en modo Chess
void Malla3D::draw_Chess()
{

}
// -----------------------------------------------------------------------------
GLuint Malla3D::CrearVBO( GLuint tipo_vbo,GLuint tamanio_bytes, GLvoid * puntero_ram )
{
   GLuint id_vbo ;               //resultado: identificador de VBO
   glGenBuffers( 1, & id_vbo ); //crear nuevo VBO, obtener identificador (nunca 0)
   glBindBuffer( tipo_vbo, id_vbo );//activar el VBO usando su identificador

   //esta instrucción hace la transferencia de datos desde RAM hacia GPU
   glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );
   glBindBuffer( tipo_vbo, 0 );     //desactivación del VBO (activar 0)
   return id_vbo ;   //devolver el identificador resultado
}
// -----------------------------------------------------------------------------

void Malla3D::draw_ModoDiferido()
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

   //visualizar triángulos con glDrawElements (puntero a tabla == 0)
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri ); //activar VBO de triángulos
   glDrawElements( GL_TRIANGLES, 3* f.size(), GL_UNSIGNED_INT, 0 ) ;
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); //desactivar VBO de triángulos

   //desactivar uso de array de vértices
   glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(int modo, GLenum visual)
{
  glPolygonMode(GL_FRONT_AND_BACK,visual);
   switch (visual)
   {
      case GL_POINT: glPolygonMode(GL_FRONT_AND_BACK,GL_POINT); break;
      case GL_LINE: glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
      case GL_FILL: glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
   }

   switch (modo)
   {
      case 1: draw_ModoInmediato();
      case 2: draw_ModoDiferido();
      case 3: draw_Chess();
   }
      

}


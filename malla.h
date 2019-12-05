// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:
   Malla3D();

   // dibuja el objeto en modo inmediato
   virtual void draw_ModoInmediato(char L);

   // dibuja el objeto en modo diferido (usando VBOs)
   virtual void draw_ModoDiferido(char L);

   //dibuja el objeto en modo ajedrez
   virtual void draw_Chess();

   GLuint CrearVBO( GLuint tipo_vbo,GLuint tamanio_bytes, GLvoid * puntero_ram );
   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   //varibale modo determina si se va a visualizar en modo inmediato o diferido, GLenum es el modo de visualizacion
   virtual void draw(int modo,bool puntos,bool lineas,bool solido);
   void aniadirColor(Tupla3f cl);
   //Añade un material
   void setMaterial(Material m);
   //void setTextura(Textura text);
   protected:
   
   void calcular_normales() ; // calcula tabla de normales de las caras (práctica 3)
   void calcular_normales_vertices() ; // calcula tabla de normales de las caras (práctica 3)

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3f> color,cimpar,cpar,colorLinea,colorPuntos;  // tabla de colores
   std::vector<Tupla3i> f, fimpar, fpar ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> nv; //tabla de normales de vértices
   std::vector<Tupla3f> nc; //tabla de normales de caras;
   std::vector<Tupla2f> ct; //tabla de coordenadas de textura
   Material * mat = nullptr;
   //Textura * text = nullptr;
   bool ajedrez = false;
   const int MAX=100;
   GLuint id_vbo_ver=0,id_vbo_tri=0;
} ;


#endif

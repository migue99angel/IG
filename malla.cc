#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************
Malla3D::Malla3D(){}
// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(char L)
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

  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, 0, nv.data());


  //Sirve para que no se vea difuminado
  //glShadeModel(GL_FLAT);
  //visualizar, indicando: tipo de primitiva y número de índices,
  //tipo de los índices y dirección de la tabla de índices
  glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT ,f.data());
  
  //Deshabilitar el array de vértices
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);


}
// -----------------------------------------------------------------------------
//Visualización en modo Chess
void Malla3D::draw_Chess()
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

void Malla3D::draw_ModoDiferido(char L)
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

   glEnableClientState(GL_NORMAL_ARRAY);
   glNormalPointer(GL_FLOAT, 0, nv.data());
   //visualizar triángulos con glDrawElements (puntero a tabla == 0)
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri ); //activar VBO de triángulos
   glDrawElements( GL_TRIANGLES, 3* f.size(), GL_UNSIGNED_INT, 0 ) ;
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); //desactivar VBO de triángulos

   //desactivar uso de array de vértices
   glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato, a draw_ModoDiferido o bien a draw_Chess

void Malla3D::draw(int modo,bool puntos,bool lineas,bool solido)
{
   if(nv.empty())
      calcular_normales();
      
   mat->aplicar();
   if(puntos){
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      switch (modo)
      {
         case 1: draw_ModoInmediato('P'); break;
         case 2: draw_ModoDiferido('P'); break;
         case 3: draw_Chess(); break;
         
      }
   }
   if(lineas){
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      switch (modo)
      {
         case 1: draw_ModoInmediato('L'); break;
         case 2: draw_ModoDiferido('L'); break;
         case 3: draw_Chess(); break;
         
      }
   }
   if(solido){
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      switch (modo)
      {
         case 1: draw_ModoInmediato('F'); break;
         case 2: draw_ModoDiferido('F'); break;
         case 3: draw_Chess(); break;
         
      }
   }   

}
// -----------------------------------------------------------------------------
//Esta función inicializar el vector de colores 
void Malla3D::aniadirColor(Tupla3f cl)
{
   Tupla3f aux1=Tupla3f(0.5,0.5,0);
   Tupla3f aux2=Tupla3f(0,0.5,1);
   colorLinea.clear();
   colorPuntos.clear();
   color.clear();

   for(int i=0;i<v.size();++i){
      color.push_back(cl);
      colorLinea.push_back(aux1);
      colorPuntos.push_back(aux2);
   }
   //Añado de nuevo el color para darle color a la tapa de abajo
   color.push_back(cl); 
   colorLinea.push_back(aux1);
   colorPuntos.push_back(aux2);  
}
// -----------------------------------------------------------------------------
//Función para el cálculo de las normales de las caras
void Malla3D::calcular_normales(){
   //Nos aseguramos de que las tablas de normales están vacías al principio
   nc.clear();
   nv.clear();
   //Obtenemos las normales de las caras
   for(int i = 0; i < f.size(); i++){
      //Cogemos los vertices de cada cara
      Tupla3f p = v[f[i](0)];
      Tupla3f q = v[f[i](1)];
      Tupla3f r = v[f[i](2)];

      //Se calculan los vectores a y b correspondientes a dos aristas mediante
      //la diferencia de dos puntos

      Tupla3f a = q-p;
      Tupla3f b = r-p;


      //Obtenemos el vector perpendicular a la cara mediante el producto vectorial de a y b
      Tupla3f mc = a.cross(b);

      Tupla3f normalizado = mc.normalized();

      //Ahora normalizamos el vector mc para obtener el vector perpendicular normalizado y lo introducimos a la tabla
      nc.push_back(mc);
   }
   calcular_normales_vertices();
}

void Malla3D::calcular_normales_vertices(){
   //Inicializo el vector al tamaño del vector de vértices, y todas las componentes a 0
   
   nv = std::vector<Tupla3f>(v.size(), {0, 0, 0});
   //Ahora obtenemos las normales de los vértices, que se define como la sumatoria de las normales de todas las caras adyacentes
   for(int i=0;i<f.size();i++){
      nv[f[i][0]] = (nv[f[i][0]] + nc[i]).normalized();
      nv[f[i][1]] = (nv[f[i][1]] + nc[i]).normalized();
      nv[f[i][2]] = (nv[f[i][2]] + nc[i]).normalized();
      
   }
}

void Malla3D::setMaterial(Material m)
{
   mat = new Material(m);
}
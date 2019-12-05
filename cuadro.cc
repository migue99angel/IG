#include "aux.h"
#include "cuadro.h"

Cuadro::Cuadro(float lado)
{
   this->lado = lado;

   Tupla3f a(0,0,0), b(lado,0,0), c(0,lado,0), d(lado,lado,0);        

   
   v.push_back(a);
   v.push_back(b);
   v.push_back(c);
   v.push_back(d);

   // inicializar la tabla de caras o triángulos:
 
   Tupla3i ver1(2,0,1),ver2(1,3,2);


   f.push_back(ver1);
   f.push_back(ver2);

     
    // inicializar la tabla de colores
    Tupla3f a1(0.7,0.7,0.7);

    color.push_back(a1);
    color.push_back(a1);
    color.push_back(a1);
    color.push_back(a1); 


    colorLinea.push_back(Tupla3f(1.0,0,0));   
    colorLinea.push_back(Tupla3f(1.0,0,0));   
    colorLinea.push_back(Tupla3f(1.0,0,0));   
    colorLinea.push_back(Tupla3f(1.0,0,0));   


    colorPuntos.push_back(Tupla3f(0,0,1.0));
    colorPuntos.push_back(Tupla3f(0,0,1.0));
    colorPuntos.push_back(Tupla3f(0,0,1.0));
    colorPuntos.push_back(Tupla3f(0,0,1.0));       

}

void Cuadro::setTextura(Textura &text)
{
    this->text = text;
    obtenerPuntosCoordenadas();
}

void Cuadro::obtenerPuntosCoordenadas()
{
   this->ct.push_back({0,0});
   this->ct.push_back({text.width,0});
   this->ct.push_back({0,text.height});
   this->ct.push_back({text.width,text.height});
}

void Cuadro::draw(int modo,bool puntos,bool lineas,bool solido)
{
   if(nv.empty())
      calcular_normales();
      
   mat->aplicar();
   text.activar();
   setTextura(text);
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
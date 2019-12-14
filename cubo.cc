#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   this->lado = lado;
   // inicializar la tabla de vértices
   //a->0 b->1 c->2 d->3 e->4 x->5 g->6 h->7 
   Tupla3f a(0,0,0), b(lado/2,0,0),c(lado/2,lado/2,0),d(0,lado/2,0),
            e(0,0,-lado/2), x(lado/2,0,-lado/2), g(lado/2,lado/2,-lado/2),h(0,lado/2,-lado/2);         

   
   v.push_back(a);
   v.push_back(b);
   v.push_back(c);
   v.push_back(d);
   v.push_back(e);
   v.push_back(x);
   v.push_back(g);
   v.push_back(h);


    
   // inicializar la tabla de caras o triángulos:
 
   Tupla3i ver1(0,1,2),ver2(0,2,3),  //Cara de frente
           ver3(5,4,7),ver4(5,7,6),  //Cara de atrás
           ver5(0,7,4),ver6(0,3,7),  //Lat izq
           ver7(1,6,2),ver8(1,5,6),  //Lat der
           ver9(2,6,7),ver10(2,7,3),  //Arriba
           ver11(5,1,0),ver12(5,0,4); //Abajo
        

   f.push_back(ver1);
   f.push_back(ver2);
   f.push_back(ver3);
   f.push_back(ver4);
   f.push_back(ver5);
   f.push_back(ver6);
   f.push_back(ver7);
   f.push_back(ver8);
   f.push_back(ver9);
   f.push_back(ver10);
   f.push_back(ver11);
   f.push_back(ver12);

     
    // inicializar la tabla de colores
    Tupla3f a1(0.7,0.7,0.7), b1(0.7,0.7,0.7),c1(0.7,0.7,0.7), 
            d1(0.7,0.7,0.7), e1(0.7,0.7,0.7), f1(0.7,0.7,0.7), 
            g1(0.7,0.7,0.7),h1(0.7,0.7,0.7);

    color.push_back(a1);
    color.push_back(b1);
    color.push_back(c1);
    color.push_back(d1); 
    color.push_back(e1);
    color.push_back(f1);
    color.push_back(g1);
    color.push_back(h1);
  

    colorLinea.push_back(Tupla3f(1.0,0,0));   
    colorLinea.push_back(Tupla3f(1.0,0,0));   
    colorLinea.push_back(Tupla3f(1.0,0,0));   
    colorLinea.push_back(Tupla3f(1.0,0,0));   
    colorLinea.push_back(Tupla3f(1.0,0,0));   
    colorLinea.push_back(Tupla3f(1.0,0,0));   
    colorLinea.push_back(Tupla3f(1.0,0,0));   
    colorLinea.push_back(Tupla3f(1.0,0,0));

    colorPuntos.push_back(Tupla3f(0,0,1.0));
    colorPuntos.push_back(Tupla3f(0,0,1.0));
    colorPuntos.push_back(Tupla3f(0,0,1.0));
    colorPuntos.push_back(Tupla3f(0,0,1.0));
    colorPuntos.push_back(Tupla3f(0,0,1.0));
    colorPuntos.push_back(Tupla3f(0,0,1.0));
    colorPuntos.push_back(Tupla3f(0,0,1.0));
    colorPuntos.push_back(Tupla3f(0,0,1.0));
       

}

void Cubo::obtenerPuntosCoordenadas()
{ 
        this->ct.clear();

        this->ct.push_back({0,0});
        this->ct.push_back({0,1});
        this->ct.push_back({1,0});
        this->ct.push_back({1,1});
        this->ct.push_back({1,1});
        this->ct.push_back({1,0});
        this->ct.push_back({0,1});
        this->ct.push_back({0,0});

}

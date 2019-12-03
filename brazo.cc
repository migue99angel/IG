#include "brazo.h"

Brazo::Brazo(Material m,Tupla3f color){
    this->esfera_sup = new Esfera(20,20,5,{0,0,0});
    this->esfera_inf = new Esfera(20,20,5,{0,0,0});
    this->cilindro = new Cilindro(5,50,40,5,color);
    
    this->cilindro->setMaterial(m);
    this->esfera_inf->setMaterial(m);
    this->esfera_sup->setMaterial(m);

    this->angulo = 0;
}

void Brazo::draw(int modo,bool puntos,bool lineas,bool solido,bool tapas){
    glPushMatrix();
                glPushMatrix();
                    this->esfera_sup->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0,-cilindro->getAltura()-(cilindro->getRadio())/2,0);
                    this->esfera_inf->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0,-cilindro->getAltura()-(cilindro->getRadio())/2,0);
                    this->cilindro->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();
    glPopMatrix();
}

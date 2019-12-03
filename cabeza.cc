#include "cabeza.h"

Cabeza::Cabeza(Material m,Tupla3f color){
    this->little_esfera = new Esfera(20,20,2.5,color);
    this->esfera = new Esfera(20,20,10,color);
    this->cilindro = new Cilindro(5,50,15,10,color);
    this->little_cilindro = new Cilindro(5,50,20,1.5,color);

    little_esfera->setMaterial(m);
    esfera->setMaterial(m);
    cilindro->setMaterial(m);
    little_cilindro->setMaterial(m);

    this->angulo = 0;
}


void Cabeza::draw(int modo,bool puntos,bool lineas,bool solido,bool tapas){
    glPushMatrix();
                glRotatef(angulo,0,1,0);
                glPushMatrix();
                    this->cilindro->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0,cilindro->getAltura(),0);
                    this->esfera->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0,cilindro->getAltura()+(esfera->getRadio())/2,0);
                    this->little_cilindro->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0,cilindro->getAltura()+(esfera->getRadio())/2 + little_cilindro->getAltura(),0);
                    this->little_esfera->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();
    glPopMatrix();
}

void Cabeza::moverCabeza(){
    this->angulo += incremento;
}
#include "cabeza.h"

Cabeza::Cabeza(Material m,Tupla3f color){
    Tupla3f ojos(1,1,1);
    Tupla3f pupilas(0,0,0);
    this->little_esfera = new Esfera(20,20,2.5,pupilas);
    this->esfera = new Esfera(20,20,10,color);
    this->cilindro = new Cilindro(5,50,15,10,color);
    this->little_cilindro = new Cilindro(5,50,20,1.5,color);
    this->ojo_der = new Esfera(20,20,2.5,ojos);
    this->ojo_izq = new Esfera(20,20,2.5,ojos);
    this->pupila_der = new Esfera(20,20,1,pupilas);
    this->pupila_izq = new Esfera(20,20,1,pupilas);
    

    little_esfera->setMaterial(m);
    esfera->setMaterial(m);
    cilindro->setMaterial(m);
    little_cilindro->setMaterial(m);
    ojo_der->setMaterial(m);
    ojo_izq->setMaterial(m);
    pupila_der->setMaterial(m);
    pupila_izq->setMaterial(m);
}


void Cabeza::draw(int modo,bool puntos,bool lineas,bool solido,bool tapas){
    glPushMatrix();

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
                    glTranslatef(0,cilindro->getAltura()+(esfera->getRadio())/2 + little_cilindro->getAltura() + this->x,0);
                    this->little_esfera->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(-ojo_izq->getRadio()/2,cilindro->getAltura(),cilindro->getRadio());
                    this->ojo_izq->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(ojo_der->getRadio()/2,cilindro->getAltura(),cilindro->getRadio());
                    this->ojo_der->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(-ojo_izq->getRadio()/2,cilindro->getAltura(),cilindro->getRadio()+ojo_izq->getRadio()/1.5);
                    this->pupila_izq->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(ojo_der->getRadio()/2,cilindro->getAltura(),cilindro->getRadio()+ojo_der->getRadio()/1.5);
                    this->pupila_der->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

    glPopMatrix();
}

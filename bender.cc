#include "bender.h"

Bender::Bender(Material m){
    Tupla3f gris(0.7,0.7,0.7);
    this->brazo_der = new Brazo(m,gris);
    this->brazo_izq = new Brazo(m,gris);
    this->pierna_der = new Pierna(m,gris);
    this->pierna_izq = new Pierna(m,gris);
    this->cabeza = new Cabeza(m,gris);
    this->tronco = new Cilindro(5,50,40,15,gris);
    this->tronco->setMaterial(m);
    this->anguloBrazoDer = this->anguloBrazoIzq = this->anguloCuello = this->anguloPiernaDer = this->anguloPiernaIzq = 0;
}

void Bender::draw(int modo,bool puntos,bool lineas,bool solido,bool tapas){
        glPushMatrix();
                glPushMatrix();
                    this->tronco->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glScalef(0.75,0.75,0.75);
                    glTranslatef(-tronco->getRadio()-brazo_izq->getHombro(),0.95*tronco->getAltura(),0);
                    glRotatef(this->anguloBrazoIzq,0,0,1);
                    this->brazo_izq->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    
                    glScalef(0.75,0.75,0.75);
                    glTranslatef(tronco->getRadio()+brazo_der->getHombro(),0.95*tronco->getAltura(),0);
                    glRotatef(this->anguloBrazoDer,1,0,0);
                    this->brazo_der->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glRotatef(this->anguloPiernaDer,1,0,0);
                    glScalef(0.5,0.5,0.5);
                    glTranslatef(-tronco->getRadio()/2,0,0);
                    this->pierna_der->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glRotatef(this->anguloPiernaIzq,0,0,1);
                    glScalef(0.5,0.5,0.5);
                    glTranslatef(tronco->getRadio()/2,0,0);
                    this->pierna_izq->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glRotatef(this->anguloCuello,0,1,0);
                    glTranslatef(0,tronco->getAltura(),0);
                    this->cabeza->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();
    glPopMatrix();
}

void Bender::moverBrazoDer(float inc){
    this->anguloBrazoDer += inc;
}

void Bender::moverBrazoIzq(float inc){
    this->anguloBrazoIzq += inc;
}

void Bender::moverPiernaDer(float inc){
    this->anguloPiernaDer += inc;
}

void Bender::moverPiernaIzq(float inc){
    this->anguloPiernaIzq += inc;
}

void Bender::moverCuello(float inc){
    this->anguloCuello += inc;
}
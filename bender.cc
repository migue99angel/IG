#include "bender.h"

Bender::Bender(Material m,int v_animacion){
    Tupla3f gris(0.7,0.7,0.7);
    this->brazo_der = new Brazo(m,gris);
    this->brazo_izq = new Brazo(m,gris);
    this->pierna_der = new Pierna(m,gris);
    this->pierna_izq = new Pierna(m,gris);
    this->cabeza = new Cabeza(m,gris);
    this->tronco = new Cilindro(5,50,40,15,gris);
    this->tronco->setMaterial(m);
    this->anguloBrazoDer = this->anguloBrazoIzq = this->anguloCuello = this->anguloPiernaDer = this->anguloPiernaIzq = 0;
    this->v_animacion = v_animacion;
    this->hacia_delante_pierna_der = false;
    this->hacia_delante_pierna_izq = false;
    bool paso = false;
    this->n_pasos = 0;
}

void Bender::draw(int modo,bool puntos,bool lineas,bool solido,bool tapas){
        glPushMatrix();
                glTranslatef(0,0,n_pasos);
                
                glPushMatrix();
                    this->tronco->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glScalef(0.75,0.75,0.75);
                    glTranslatef(-tronco->getRadio()-brazo_izq->getHombro(),0.95*tronco->getAltura(),0);
                    glRotatef(this->anguloBrazoIzq,1,0,0);
                    this->brazo_izq->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glScalef(0.75,0.75,0.75);
                    glTranslatef(tronco->getRadio()+brazo_der->getHombro(),0.95*tronco->getAltura(),0);
                    glRotatef(this->anguloBrazoDer,1,0,0);
                    this->brazo_der->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glScalef(0.5,0.5,0.5);
                    glTranslatef(-tronco->getRadio()/2,0,0);
                    glRotatef(this->anguloPiernaDer,1,0,0);
                    this->pierna_der->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glScalef(0.5,0.5,0.5);
                    glTranslatef(tronco->getRadio()/2,0,0);
                    glRotatef(this->anguloPiernaIzq,1,0,0);
                    this->pierna_izq->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glRotatef(this->anguloCuello,0,1,0);
                    glTranslatef(0,tronco->getAltura(),0);
                    this->cabeza->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();


    glPopMatrix();
}

void Bender::moverAntena()
{
    if(this->cabeza->getAlturaAntena() <= 50 && !baja)
    {
        this->cabeza->setAlturaAntena(1);
    }

    if(this->cabeza->getAlturaAntena() == 50)
        baja = true;

    if(this->cabeza->getAlturaAntena() >= 0 && baja)
    {
        this->cabeza->setAlturaAntena(-1); 
    }

    if(this->cabeza->getAlturaAntena() == 0)
        baja = false;    
}

void Bender::moverBrazoDer(){
    this->anguloBrazoDer -= v_animacion;
    this->anguloBrazoDer = static_cast<int>(this->anguloBrazoDer)%(360);
}

void Bender::moverBrazoIzq(){
    this->anguloBrazoIzq -= v_animacion;
    this->anguloBrazoIzq = static_cast<int>(this->anguloBrazoIzq)%(360);
}

void Bender::moverPiernaDer(){
    if(this->anguloPiernaDer < 90 && !hacia_delante_pierna_der)
        this->anguloPiernaDer += v_animacion;
    if(this->anguloPiernaDer >= 90)
        hacia_delante_pierna_der = true;    
    if(hacia_delante_pierna_der)
        this->anguloPiernaDer -= v_animacion;
    if(hacia_delante_pierna_der && anguloPiernaDer <= -90)
       hacia_delante_pierna_der = false;    
}

void Bender::moverPiernaIzq(){
    if(this->anguloPiernaIzq < 90 && !hacia_delante_pierna_izq)
        this->anguloPiernaIzq += v_animacion;
    if(this->anguloPiernaIzq >= 90)
        hacia_delante_pierna_izq = true;    
    if(hacia_delante_pierna_izq)
        this->anguloPiernaIzq -= v_animacion;
    if(hacia_delante_pierna_izq && anguloPiernaIzq <= -90)
       hacia_delante_pierna_izq = false;  
}

void Bender::moverCuello(){
    this->anguloCuello += v_animacion;
    this->anguloCuello = static_cast<int>(this->anguloCuello)%(360);
}

void Bender::mover(int animacion){
    switch (animacion)
    {
        case 1:
            this->moverBrazoDer();
        break;
        case 2:
            this->moverBrazoIzq();
        break;
        case 3:
            this->moverPiernaDer();
        break;
        case 4:
            this->moverPiernaIzq();
        break;
        case 5:
            this->moverCuello();
        break;
        case 6:
            this->anguloPiernaDer = 0;
            this->anguloBrazoIzq  = 0;
            this->andar();
        break;
    }
}

void Bender::andar(){
    if(this->anguloPiernaDer > v_animacion)
        this->anguloPiernaDer = 0;
    if(this->anguloPiernaIzq > v_animacion)
        this->anguloPiernaIzq = 0;   
    this->n_pasos++;
    if(paso){
        if(this->n_pasos % 2 == 0){
            this->anguloPiernaDer += v_animacion;
        }
        else{
            this->anguloPiernaDer -= v_animacion;
            paso =false;
        }
    }
    else{
        if(this->n_pasos % 2 == 0){
            this->anguloPiernaIzq += v_animacion;
        }
        else{
            this->anguloPiernaIzq -= v_animacion;
            paso =true;
        }
    }
}

void Bender::andarHaciaAtras(){
    if(this->anguloPiernaDer > v_animacion)
        this->anguloPiernaDer = 0;
    if(this->anguloPiernaIzq > v_animacion)
        this->anguloPiernaIzq = 0;   
    this->n_pasos--;
    if(paso){
        if(this->n_pasos % 2 == 0){
            this->anguloPiernaDer -= v_animacion;
        }
        else{
            this->anguloPiernaDer += v_animacion;
            paso =false;
        }
    }
    else{
        if(this->n_pasos % 2 == 0){
            this->anguloPiernaIzq -= v_animacion;
        }
        else{
            this->anguloPiernaIzq += v_animacion;
            paso = true;
        }
    }
}

void Bender::setVelocidad(float v){
    if(v > 0 && v_animacion < 100)
        this->v_animacion += v;
    if(v < 0 && v_animacion > 0)
        this->v_animacion += v;    
}
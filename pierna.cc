#include "pierna.h"

Pierna::Pierna(Material m,Tupla3f color){
    esfera_sup = new Esfera(20,20,5,Tupla3f(0,0,0));
    pie = new Cubo(25);
    cilindro = new Cilindro(5,50,40,5,color);

    this->esfera_sup->setMaterial(m);
    this->pie->setMaterial(m);
    this->cilindro->setMaterial(m);

    this->angulo = 0; 
}

void Pierna::moverPierna(){
    this->angulo += incremento;
}

void Pierna::draw(int modo,bool puntos,bool lineas,bool solido,bool tapas){
    glPushMatrix();
                glRotatef(angulo,0,0,1);
                glPushMatrix();
                    this->esfera_sup->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();

                glPushMatrix();
                    glScalef(1,1,2);
                    glTranslatef(-this->pie->getLado()/4,-cilindro->getAltura()-(cilindro->getRadio()),this->pie->getLado()/4);
                    this->pie->draw(modo,puntos,lineas,solido);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0,-cilindro->getAltura()-(cilindro->getRadio())/2,0);
                    this->cilindro->draw(modo,puntos,lineas,solido,tapas);
                glPopMatrix();
    glPopMatrix();

}
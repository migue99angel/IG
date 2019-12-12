#include "textura.h"
Textura::Textura(){}

Textura::Textura(const Textura &t)
{
    this->operator=(t);
}
Textura::Textura(std::string archivo,GLuint id)
{  
    
    if(pimg == nullptr){
        this->textura_id = id;
        
        pimg = new jpg::Imagen(archivo);
           
        this->width = pimg->tamX();
        this->height = pimg->tamY();

        for(int i=0; i < this->width; ++i)
            for(int j = 0; j < this->height; ++j){
                this->texels.push_back( pimg->leerPixel(i,j));
                //std::cout<<"Leemos el pixel: "<< (pimg->leerPixel(i,j))[3]<<"\n";
            }

        glGenTextures(1, &textura_id);  
    }

}

void Textura::activar()
{
    
    // Se activa esta textura en concreto
    glBindTexture(GL_TEXTURE_2D, textura_id);

    // Cómo se usa el color de los texels con la iluminación activada
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

    // Cómo se selecciona el texel a partir de una coordenada de textura
    // Magnificación
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Minificación
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    // Cuando las coordenadas de textura no están en el rango [0,1][0,1]
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Se construye la textura
    gluBuild2DMipmaps(GL_TEXTURE_2D,
                        GL_RGB,
                        pimg->tamX(),
                        pimg->tamY(),
                        GL_RGB,
                        GL_UNSIGNED_BYTE,
                        pimg->leerPixels());

}

Textura& Textura::operator = (const Textura &t)
{
    this->height = t.height;
    this->width = t.width;
    this->pimg = t.pimg;
    this->texels = t.texels;
}

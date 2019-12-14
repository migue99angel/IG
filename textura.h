#ifndef Textura_H_INCLUDED
#define Textura_H_INCLUDED
#include "aux.h"
#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"

// *****************************************************************************
//
// clase para aplicar texturas a Mallas3D
//
// *****************************************************************************

class Textura{
    private:
        GLuint textura_id = 0;
        unsigned char* texels;
        jpg::Imagen * pimg = nullptr;
        unsigned int width,height;
    public:
        Textura();
        Textura(std::string archivo,GLuint textura);
        Textura(const Textura &t);
        void activar();
        inline GLuint getID(){return this->textura_id;}
        inline unsigned char* getCoordenadas(){return texels;}
        inline unsigned int getAncho(){return width;}
        inline unsigned int getAlto(){return height;}
        Textura& operator = (const Textura &t);
};
#endif
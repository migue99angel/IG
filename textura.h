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
        std::vector<unsigned char*> texels;
        
       
    public:
        Textura();
        Textura(std::string archivo,GLuint textura);
        void activar();
        jpg::Imagen * pimg = nullptr;
        inline std::vector<unsigned char*> getCoordenadas(){return texels;}
        unsigned int width,height;
};
#endif
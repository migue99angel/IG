#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "ply_reader.h"
#include "objply.h"
#include "tetraedro.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luzposicional.h"
#include "luzdireccional.h"
#include "luz.h"
#include "bender.h"
#include "cuadro.h"
#include "camara.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,SELANIMACION} menu;
class Escena
{

   private:

   

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    


   void clear_window();

   menu modoMenu=NADA;
   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
   Cilindro * cilindro=nullptr;
   Bender * bender = nullptr;
   Brazo * brazo = nullptr;
   Cono * cono=nullptr;
   Cuadro * cuadro = nullptr;
   Esfera * esfera=nullptr;
   ObjPLY * ant=nullptr;
   ObjPLY * bet=nullptr;
   ObjRevolucion * peon=nullptr;
   ObjRevolucion * peon2=nullptr;
   LuzPosicional * luz1 = nullptr;
   LuzDireccional * luz_2 = nullptr;
   Textura text;
   Textura lata;
   Textura monaLisa;
   Camara * camaras[5];
   int toDraw = 1, modo=1,n_animacion=0;
   GLenum visual = GL_FILL;
   bool Iluminacion = false;
   bool puntos=false, lineas=false, solido=true;
   bool ajedrez = false;
   bool tapas=true;
   bool animacion = false;
   bool pause = true;
   int angulo = 0;
   bool arriba = true;
   bool variaAlpha; //Controla si varia alpha o beta
   bool estadoRaton = false; //variable de estado para controlar el movimiento del ratón
   int camaraActiva; //Variable que controla cual es la camara activa en cada instante
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );
    void animarModeloJerarquico();
    void animarLuces();
    inline bool getPause(){return this->pause;}
    void ratonMovido(int x,int y);
    inline void setEstadoRaton(bool mov){this->estadoRaton = mov;}
};
#endif

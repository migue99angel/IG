

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "objrevolucion.h"

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena....
    cilindro = new Cilindro();
    cubo = new Cubo;
    tetraedro = new Tetraedro;
    ant = new ObjPLY("plys/ant.ply");
    bet = new ObjPLY("plys/beethoven.ply"); 
    cono = new Cono();
    peon = new ObjRevolucion("plys/peon.ply",50,true,true);
    
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
   glEnable (GL_CULL_FACE);   //No se dibujan las caras traseras
	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
    ejes.draw();

    switch(toDraw)
    {
       
       case 1:
         tetraedro->draw(modo);
         break;
       case 2:
         cubo->draw(modo);
         break; 
       case 3:
          glPushMatrix();
            glTranslatef(20,45,0);
            glScalef(5,5,5);
            glRotatef(180,0,0,1);
            cono->draw(modo);
          glPopMatrix();
          glPushMatrix();
            glScalef(2.5,2.5,2.5);
            glTranslatef(-20,0,0);
            cilindro->draw(modo);
          glPopMatrix();

         break;
       case 4:
          glPushMatrix();
            glScalef(5,5,5);
            cilindro->aniadirColor(Tupla3f(0,0,1.0));
            cilindro->draw(modo);
          glPopMatrix();
         break;
       case 5:
          glPushMatrix();
            glScalef(50,50,50);
            peon->draw(modo);
          glPopMatrix();
         break;
       case 6:
          glPushMatrix();
             glScalef(25,25,25);
            bet->draw(modo);
          glPopMatrix();
         break;
       default:
         glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
         ejes.draw();
         break;    
    }
    
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
       case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
       case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO; 
         break ;
       case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         break ;
       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         break ;
       case 'T' :
         if(modoMenu == SELOBJETO){
            toDraw = 1;
         }  
         break;
       case 'C' : 
         if(modoMenu == SELOBJETO){
            toDraw = 2;
         }  
         break;
       case 'E' : 
         if(modoMenu == SELOBJETO){
            toDraw = 3;
         }  
         break;
       case 'W' : 
         if(modoMenu == SELOBJETO){
            toDraw = 4;
         }  
         break;
       case 'P' : 
         if(modoMenu == SELVISUALIZACION){
            glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
         }  
         else if (modoMenu == SELOBJETO){
            toDraw = 5;
         }
         break;
       case 'L' : 
         if(modoMenu == SELVISUALIZACION){
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
         }  
         break;
       case 'S' : 
         if(modoMenu == SELVISUALIZACION){
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
         }  
         break;
       case '1' : 
         if(modoMenu == SELDIBUJADO){
            modo = 1;
         }  
         break;  
       case '2' : 
         if(modoMenu == SELDIBUJADO){
            modo = 2;
         }  
         break;
       case '3' : 
         if(modoMenu == SELDIBUJADO){
            modo = 3;
         }  
         break;
       case '6' : 
         if(modoMenu == SELOBJETO){
            toDraw = 6;
         }  
         break;



            
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}

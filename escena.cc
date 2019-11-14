

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
    //Componentes del material
    Tupla4f ambiente(0.0215,0.1745,0.0215, 0.6);
    Tupla4f especular(0.07568, 	0.61424, 0.07568, 0.6);
    Tupla4f difuso(	0.633, 0.727811, 0.633, 0.6);
    //Componentes luz
    Tupla3f pos(500,-500,500);
    Tupla4f luz(0.0,0.0,0.0,0.0);
    Tupla4f luz2(1.0,1.0,1.0,1.0);
    Tupla4f luz3(1.0,1.0,1.0,1.0);
    // crear los objetos de la escena....
    //cono = new Cono();
    cilindro = new Cilindro();
    cubo = new Cubo;
    tetraedro = new Tetraedro;
    ant = new ObjPLY("plys/ant.ply");
    //bet = new ObjPLY("plys/beethoven.ply");
    peon = new ObjRevolucion("plys/peon.ply",50,true);
    esfera = new Esfera();
    luz1 = new LuzPosicional(pos,GL_LIGHT0,luz,luz2,luz3);
    Material  material_ejemplo=Material(ambiente,especular,difuso,100.0);
  
    cubo->setMaterial(material_ejemplo);
    peon->setMaterial(material_ejemplo);
    cilindro->setMaterial(material_ejemplo);
    esfera->setMaterial(material_ejemplo);
    //cono->setMaterial(material_ejemplo);
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

    if(Iluminacion){
      glEnable(GL_LIGHTING);
      glEnable(GL_NORMALIZE);
      glShadeModel(GL_SMOOTH);
      
    }
    else{
      if(glIsEnabled(GL_LIGHTING))
        glDisable(GL_LIGHTING);
    }

    switch(toDraw)
    { 
       case 1:
         tetraedro->draw(modo);
         luz1->activar();
         break;
       case 2:
         luz1->activar();
         cubo->draw(modo);
         break; 
       case 3:
          glPushMatrix();
            glScalef(2.5,2.5,2.5);
            glTranslatef(-20,0,-20);
            luz1->activar();
            cilindro->draw(modo);
          glPopMatrix();

         break;
       case 4:
          /*glPushMatrix();
            luz1->activar();
          glPopMatrix();*/
          glPushMatrix();
            luz1->activar();
            glTranslatef(50,0,0);
            esfera->draw(modo);
          glPopMatrix();
         break;
       case 5:
          luz1->activar();
          glPushMatrix();
            glScalef(50,50,50);
            glTranslatef(2,0,0);
            peon->draw(modo);
          glPopMatrix();
         break;
       case 6:
          glPushMatrix();
             //glScalef(50,50,50);
             luz1->activar();
            cilindro->aniadirColor(Tupla3f(1,0,0)); 
            cilindro->draw(modo);
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
            Iluminacion = false;
         }  
         else if (modoMenu == SELOBJETO){
            toDraw = 5;
         }
         break;
       case 'L' : 
         if(modoMenu == SELVISUALIZACION){
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            Iluminacion = false;
         }  
         break;
       case 'S' : 
         if(modoMenu == SELVISUALIZACION){
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            Iluminacion = false;
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
            Iluminacion = false;
         }  
         break;
       case '6' : 
         if(modoMenu == SELOBJETO){
            toDraw = 6;
         }  
         break;
        case 'I' : 
         if(modoMenu == SELVISUALIZACION){
            Iluminacion = true;
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

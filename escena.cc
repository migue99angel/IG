

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
    Tupla4f ambiente_esmerald(0.0215,0.1745,0.0215, 1.0);
    Tupla4f especular_esmerald(0.07568, 	0.61424, 0.07568, 1.0);
    Tupla4f difuso_esmerald(	0.633, 0.727811, 0.633, 1.0);

    Tupla4f ambiente_obsidian(0.05375,	0.05,0.06625, 1.0);
    Tupla4f especular_obsidian(0.332741, 0.328634, 0.346435, 1.0);
    Tupla4f difuso_obsidian(	0.18275, 0.17, 0.22525, 1.0);

    
    Tupla4f ambiente_pearl(0.25,0.20725,0.20725, 1.0);
    Tupla4f especular_pearl(0.296648,0.296648, 0.296648, 1.0);
    Tupla4f difuso_pearl(	1, 0.829,0.829, 1.0);

    Tupla4f ambiente_gold(	0.19125,	0.0735,	0.0225, 1.0);
    Tupla4f especular_gold(0.256777,0.137622,	0.086014, 1.0);
    Tupla4f difuso_gold(0.7038	,0.27048,	0.0828, 1.0);

    Tupla4f ambiente_brass(	0.329412, 0.223529, 0.027451, 1.0);
    Tupla4f especular_brass(0.992157,	0.941176,	0.807843, 1.0);
    Tupla4f difuso_brass(0.780392,	0.568627,	0.113725, 1.0);

    //Componentes luz
    Tupla3f pos(0,0,100);
    Tupla2f dir(0,0);
    Tupla4f luz(1.0,1.0,1.0,1.0);
    Tupla4f luz2(1.0,1.0,1.0,1.0);
    Tupla4f luz3(0.0,0.0,0.0,1.0);

    // crear los objetos de la escena....
    cono = new Cono();
    cilindro = new Cilindro(5,50,10,1);
    cubo = new Cubo;
    tetraedro = new Tetraedro;
    ant = new ObjPLY("plys/ant.ply");
    //bet = new ObjPLY("plys/beethoven.ply");
    peon = new ObjRevolucion("plys/peon.ply",50,true);
    peon2 = new ObjRevolucion("plys/peon.ply",50,true);
    esfera = new Esfera();
    luz1 = new LuzPosicional(pos,GL_LIGHT2,luz,luz2,luz3);
    luz_2 = new LuzDireccional(dir,GL_LIGHT1,luz,luz2,luz3);
    cuadro = new Cuadro(100);
    

    Material  esmerald = Material(ambiente_esmerald,especular_esmerald,difuso_esmerald, 128.0*0.6);
    Material obsidian = Material(ambiente_obsidian,especular_obsidian,difuso_obsidian,128*0.3);
    Material pearl = Material(ambiente_pearl,especular_pearl,difuso_pearl,0.088*128);
    Material gold = Material(ambiente_gold,especular_gold,difuso_gold,0.1*128);
    Material brass = Material(ambiente_brass,especular_brass,difuso_brass,128*0.21794872);

    text = Textura("jpgs/text-madera.jpg",0);
    
    cubo->setMaterial(esmerald);
    peon->setMaterial(esmerald);
    cilindro->setMaterial(gold);
    esfera->setMaterial(gold);
    peon2->setMaterial(pearl);
    ant->setMaterial(esmerald);
    bender = new Bender(brass,10);
    cono->setMaterial(pearl);
    cuadro->setMaterial(pearl);
    cuadro->setTextura(text);
    cuadro->obtenerPuntosCoordenadas();
    cubo->setTextura(text);
    cubo->obtenerPuntosCoordenadas();
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
  if(glIsEnabled(GL_LIGHTING))
    glDisable(GL_LIGHTING);

    ejes.draw();

    if(Iluminacion){
      glEnable(GL_LIGHTING);
      glEnable(GL_NORMALIZE);
      glShadeModel(GL_SMOOTH);
      glEnable(GL_TEXTURE_2D);
      luz1->activar();
    }
    else{
      if(glIsEnabled(GL_LIGHTING))
        glDisable(GL_LIGHTING);

      if(glIsEnabled(GL_TEXTURE_2D))
        glDisable(GL_TEXTURE_2D);  
    }
     
      
    switch(toDraw)
    { 
       case 1:
          glPushMatrix();
            glTranslatef(0,0,-20);
            cuadro->draw(modo,puntos,lineas,solido);
          glPopMatrix();

          glPushMatrix();
            bender->draw(modo,puntos,lineas,solido,tapas);
          glPopMatrix();

         break;
       case 2:
          glPushMatrix();
            glScalef(200,200,200);
            cubo->draw(modo,puntos,lineas,solido);
          glPopMatrix();
         break; 
       case 3:
          glPushMatrix();
            glTranslatef(-20,0,-20);
            cilindro->draw(modo,puntos,lineas,solido,tapas);
          glPopMatrix();
          glPushMatrix();
            glScalef(50,50,50);
            glTranslatef(-2,0,0);
            peon2->draw(modo,puntos,lineas,solido,tapas);
          glPopMatrix();
          glPushMatrix();
          glScalef(50,50,50);
            glTranslatef(2,0,0);
            peon->draw(modo,puntos, lineas, solido,tapas);
          glPopMatrix();
          glPushMatrix();
            glTranslatef(0,-100,20);
            esfera->draw(modo,puntos,lineas,solido,tapas);
          glPopMatrix();
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
         if(SELANIMACION){
           this->bender->mover(n_animacion);
         }
         break ;
       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         break ;
       case 'T' :
         if(modoMenu == SELOBJETO){
            toDraw = 1;
         }else{
            if(modoMenu == SELVISUALIZACION){
              tapas = !tapas;
            }
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
         }  
         break;
       case 'P' : 
         if(modoMenu == SELVISUALIZACION){
            puntos=!puntos;
            Iluminacion = false;
         }  
         else if (modoMenu == SELOBJETO){
         }
         break;
       case 'L' : 
         if(modoMenu == SELVISUALIZACION){
            lineas = !lineas;
            Iluminacion = false;
         }  
         break;
       case 'S' : 
         if(modoMenu == SELVISUALIZACION){
           solido = !solido;
            Iluminacion = false;
         }  
         break;
       case '1' : 
         if(modoMenu == SELDIBUJADO){
            modo = 1;
         }
         else{
           if(modoMenu == SELANIMACION && animacion){
             n_animacion = 1;
           }
         }  
         break;  
       case '2' : 
         if(modoMenu == SELDIBUJADO){
            modo = 2;
         } 
         else{
           if(modoMenu == SELANIMACION && animacion){
             n_animacion = 2;
           }
         }   
         break;
       case 'A' : 
         if(modoMenu == SELVISUALIZACION){
          Iluminacion = false;
          ajedrez = !ajedrez;
          if(ajedrez)  
            modo = 3;
          else 
            modo = 1;
         }
         else{
            modoMenu = SELANIMACION;
            animacion = true;
         }  
         break;
       case '6' : 
         if(modoMenu == SELANIMACION){
           n_animacion = 6;
         }  
         break;
        case 'I' : 
         if(modoMenu == SELVISUALIZACION){
           if(!Iluminacion)
            Iluminacion = true;
            else
              Iluminacion = false;
         }  
         break;
         case 'J' : 
            if(modoMenu == SELANIMACION)
              this->pause = !this->pause;
         break;
        case '<':
          if(modoMenu == SELVISUALIZACION){
            if(Iluminacion){
                if(luz_2->esDireccional()){
                  if (angulo == 0) 
                    luz_2->variarAnguloAlpha(1);
                  else 
                    luz_2->variarAnguloBeta(1);
                }
              }
            }
          break;
        case '>':
            if(modoMenu == SELVISUALIZACION){
            if(Iluminacion){
                if(luz_2->esDireccional()){
                  if (angulo == 0) 
                    luz_2->variarAnguloAlpha(-1);
                  else 
                    luz_2->variarAnguloBeta(-1);
                }
              }
            }
         break;
         case '3':
           if(modoMenu == SELANIMACION ){
             n_animacion = 3;
           }     
          break;
          case '4':
           if(modoMenu == SELANIMACION && animacion){
             n_animacion = 4;
           }     
          break;
          case '5':
           if(modoMenu == SELANIMACION && animacion){
             n_animacion = 5;
           }     
          break;
          case '+':
           if(modoMenu == SELANIMACION && animacion){
             bender->setVelocidad(1.25);
           }     
          break;
          case '-':
           if(modoMenu == SELANIMACION && animacion){
             bender->setVelocidad(0.75);
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

void Escena::animarModeloJerarquico()
{
  if(!pause){
    if(bender->getNPasos()<100)
      this->bender->andar();
    
    else{
      if(bender->anguloBrazoDer > -180)
        this->bender->moverBrazoDer();
    }
    if(bender->getNPasos() == 100 && bender->anguloBrazoDer == -180)
      this->bender->moverCuello();
  }
  
}

void Escena::animarLuces()
{
  if( Iluminacion)
  {
    if((luz1)->getPos()(1) < 30 && arriba)
      this->luz1->changePos({0,5,0});

    if(luz1->getPos()(1) == 30)
      arriba = false;  

    if((luz1)->getPos()(1) >-30  && !arriba)
      this->luz1->changePos({0,-5,0});  

    if(luz1->getPos()(1) == -30 && !arriba)
      arriba = true;    
  }
}
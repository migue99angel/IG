

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
    cilindro = new Cilindro(2,20,4,1);
    cubo = new Cubo;
    tetraedro = new Tetraedro;
    coche = new ObjPLY("plys/big_dodge.ply");
    peon = new ObjRevolucion("plys/peon.ply",50,true);
    peon2 = new ObjRevolucion("plys/peon.ply",50,true);
    esfera = new Esfera();
    luz1 = new LuzPosicional(pos,GL_LIGHT2,luz,luz2,luz3);
    luz_2 = new LuzDireccional(dir,GL_LIGHT1,luz,luz2,luz3);
    cuadro = new Cuadro(100);
    pared_izq = new Cuadro(100);
    cartel = new Cuadro(100);

    Material  esmerald = Material(ambiente_esmerald,especular_esmerald,difuso_esmerald, 128.0*0.6);
    Material obsidian = Material(ambiente_obsidian,especular_obsidian,difuso_obsidian,128*0.3);
    Material pearl = Material(ambiente_pearl,especular_pearl,difuso_pearl,0.088*128);
    Material gold = Material(ambiente_gold,especular_gold,difuso_gold,0.1*128);
    Material brass = Material(ambiente_brass,especular_brass,difuso_brass,128*0.21794872);

    text = Textura("jpgs/text-madera.jpg",0);
    lata = Textura("jpgs/text-lata-1.jpg",1);
    pared = Textura("jpgs/pared.jpg",3);
    publi = Textura("jpgs/publi.jpg",4);

    cubo->setMaterial(esmerald);
    peon->setMaterial(esmerald);
    cilindro->setMaterial(gold);
    esfera->setMaterial(gold);
    peon2->setMaterial(pearl);
    coche->setMaterial(esmerald);
    bender = new Bender(brass,10);
    cono->setMaterial(pearl);
    cartel->setMaterial(pearl);
    pared_izq->setMaterial(pearl);
    cuadro->setMaterial(pearl);


    cuadro->setTextura(text);
    cubo->setTextura(text);
    cilindro->setTextura(lata);
    pared_izq->setTextura(pared);
    cartel->setTextura(publi);

    cuadro->aniadirColor({1.0,1.0,0});
    pared_izq->aniadirColor({0.5,1.0,0.5});
    

    camaras[0] = new  Camara( Tupla3f{600,100,1000}, Tupla3f{0,0,0}, Tupla3f{0,1,0},1,(float)50, (float)50, (float)50,(float)2000);
    camaras[1] = new  Camara( Tupla3f{0,0,600}, Tupla3f{0,0,0}, Tupla3f{0,1,0},0,(float)500, (float)500, (float)50,(float)2000);
    camaras[2] = new  Camara( Tupla3f{0,50,-100}, Tupla3f{0,0,0}, Tupla3f{0,1,0},0,(float)500, (float)500, (float)50,(float)2000);
    camaras[3] = new  Camara( Tupla3f{-600,100,1000}, Tupla3f{0,0,0}, Tupla3f{0,1,0},1,(float)50, (float)50, (float)50,(float)2000);

    camaraActiva = 0;

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
  change_projection(1);
  change_observer();
  
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla

  if(glIsEnabled(GL_LIGHTING))
    glDisable(GL_LIGHTING);

    ejes.draw();

    if(Iluminacion){
      glEnable(GL_LIGHTING);
      glEnable(GL_NORMALIZE);
      glShadeModel(GL_SMOOTH);
      glEnable(GL_TEXTURE_2D);
      luz1->activar();
      luz_2->activar();
    }
    else{
      if(glIsEnabled(GL_LIGHTING))
        glDisable(GL_LIGHTING);

      if(glIsEnabled(GL_TEXTURE_2D))
        glDisable(GL_TEXTURE_2D);  
    }
    glPushMatrix();

    glPushMatrix();
      glTranslatef(300,0,0);
      glScalef(70,70,70);
      cubo->draw(modo,puntos,lineas,solido);
    glPopMatrix();

    glPushMatrix();
      glScalef(10,10,10);
      glTranslatef(-50,-1.5,-50);
      glRotatef(0,0,1,0);
      pared_izq->draw(modo,puntos,lineas,solido);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-450,-1.5,200);
      glRotatef(90,0,1,0);
      cartel->draw(modo,puntos,lineas,solido); 
      glPopMatrix();

    glPushMatrix();
      glScalef(12,12,12);
      glTranslatef(-50,-1.5,50);
      glRotatef(270,1,0,0);
      cuadro->draw(modo,puntos,lineas,solido);
    glPopMatrix();

    glPushMatrix();
        Tupla3f p(-300,0,150);
        cilindro->setPosicion(p);
        glTranslatef(p(0),p(1),p(2));
        glScalef(30,30,30);
      cilindro->draw(modo,puntos,lineas,solido,tapas);
    glPopMatrix();

    glPushMatrix();
      Tupla3f p3(-100,2,150);
      esfera->setPosicion(p3);
      glTranslatef(p3(0),p3(1),p3(2));
      glScalef(5,5,5);
      esfera->draw(modo,puntos,lineas,solido,tapas);
    glPopMatrix();

    glPushMatrix();
    glScalef(15,15,15);
      glTranslatef(-2.5,0,0);
      peon->draw(modo,puntos, lineas, solido,tapas);
    glPopMatrix();

    glPushMatrix();
    glScalef(15,15,15);
      peon->draw(modo,puntos, lineas, solido,tapas);
    glPopMatrix();

    glPushMatrix();
    glScalef(15,15,15);
    glTranslatef(2.5,0,0);
      peon->draw(modo,puntos, lineas, solido,tapas);
    glPopMatrix();

    glPushMatrix();
    glScalef(15,15,15);
    glTranslatef(-1.25,0,2);
      peon->draw(modo,puntos, lineas, solido,tapas);
    glPopMatrix();

    glPushMatrix();
    glScalef(15,15,15);
    glTranslatef(1.25,0,2);
      peon->draw(modo,puntos, lineas, solido,tapas);
    glPopMatrix();

    glPushMatrix();
    glScalef(15,15,15);
    glTranslatef(0,0,4);
      peon->draw(modo,puntos, lineas, solido,tapas);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,0,500);
      glRotatef(180,0,1,0);
      bender->draw(modo,puntos,lineas,solido,tapas);
    glPopMatrix();

    glPushMatrix();
      Tupla3f p2(500,15,5);
      coche->setPosicion(p2);
      glTranslatef(p2(0),p2(1),p2(2));
      glScalef(10,10,10);
      coche->draw(modo,puntos,lineas,solido);
    glPopMatrix();

glPopMatrix();


         


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
         }else{
            if(modoMenu == SELVISUALIZACION){
              tapas = !tapas;
            }
         }  
         break;
       case 'C' : 
         if(modoMenu == SELOBJETO){
            toDraw = 2;
         }else
         {
            modoMenu = SELCAMARA;
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
           if(modoMenu == SELANIMACION){
             n_animacion = 1;
           }
           else
           {
             if(modoMenu == SELCAMARA)
             {
              camaraActiva = 1;
             }
           }
           
         }  
         break;  
       case '2' : 
         if(modoMenu == SELDIBUJADO){
            modo = 2;
         } 
         else{
           if(modoMenu == SELANIMACION){
             n_animacion = 2;
           }
          else
           {
             if(modoMenu == SELCAMARA)
              camaraActiva = 2;
           }
         }   
         break;
       case 'A' : 
         if(modoMenu == SELVISUALIZACION && !Iluminacion){
            ajedrez = !ajedrez;
            if(ajedrez)  
              modo = 3;
            else 
              modo = 1;
         }
         if(modoMenu == NADA || modoMenu == SELANIMACION){
            this->pause = !this->pause;
         }
         if(modoMenu == SELVISUALIZACION && Iluminacion)
            variaAlpha = true;  
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

        case '<':
          if(modoMenu == SELVISUALIZACION){
            if(Iluminacion){
                if(luz_2->esDireccional()){
                  if (variaAlpha) 
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
                  if (variaAlpha) 
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
           }else
           {
            if(modoMenu == SELCAMARA)
              camaraActiva = 3;
           }
          break;
          case '4':
           if(modoMenu == SELANIMACION){
             n_animacion = 4;
           }  
          break;
          case '5':
           if(modoMenu == SELANIMACION){
             n_animacion = 5;
           }     
          break;
          case '+':
           if(modoMenu == SELANIMACION && !pause){
             bender->setVelocidad(1);
           }     
          break;
          case '-':
           if(modoMenu == SELANIMACION && !pause){
             bender->setVelocidad(-1);
           }     
          break;
          case 'B':
           if(modoMenu == SELVISUALIZACION && Iluminacion){
             variaAlpha = false;
           }     
          break;
          case '0':
           if(modoMenu == SELCAMARA ){
             camaraActiva = 0;
           }    
          break;
          case 'M':
            if(modoMenu == NADA){
              modoMenu = SELANIMACION;
            }
            if(SELANIMACION && pause){
              this->bender->mover(n_animacion);
            }
          break;

          case '7':
           if(modoMenu == SELANIMACION){
             n_animacion = 7;
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
         if(camaras[camaraActiva] != nullptr)
          camaras[camaraActiva]->rotarXFirstPerson(-0.001);
         break;
	   case GLUT_KEY_RIGHT:
         if(camaras[camaraActiva] != nullptr)
          camaras[camaraActiva]->rotarXFirstPerson(0.001);
         break;
	   case GLUT_KEY_UP:
         if(camaras[camaraActiva] != nullptr)
          camaras[camaraActiva]->rotarYFirstPerson(-0.001);
         break;
	   case GLUT_KEY_DOWN:
         if(camaras[camaraActiva] != nullptr)
          camaras[camaraActiva]->rotarYFirstPerson(0.001);
         break;
	   case GLUT_KEY_PAGE_UP:
        if(camaras[camaraActiva] != nullptr)
         camaras[camaraActiva]->zoom(1);
         break;
	   case GLUT_KEY_PAGE_DOWN:
        if(camaras[camaraActiva] != nullptr)
         camaras[camaraActiva]->zoom(-1);
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

   //glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );

   if(camaras[camaraActiva] != nullptr)
    camaras[camaraActiva]->setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = (newWidth/10)/**camaras[camaraActiva]->getAlto()/camaras[camaraActiva]->getAncho()*/;
   Height = (newHeight/10)/**camaras[camaraActiva]->getAlto()/camaras[camaraActiva]->getAncho()*/;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

/*void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}*/

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   camaras[camaraActiva]->setObserver();
}

void Escena::animarModeloJerarquico()
{
  // if(!pause){
  //   if(bender->getNPasos()<100)
  //     this->bender->andar();
    
  //   else{
  //     if(bender->anguloBrazoDer > -180)
  //       this->bender->moverBrazoDer();
  //   }
  //   if(bender->getNPasos() == 100 && bender->anguloBrazoDer == -180)
  //     this->bender->moverCuello();
    
    // if(bender->getNPasos()<100)
    //    this->bender->andar();
    if(!pause){
      this->bender->moverAntena();
      this->bender->moverCuello();
      this->bender->moverBrazoDer();
      this->bender->moverBrazoIzq();
      this->bender->moverPiernaDer();
      this->bender->moverPiernaIzq();
    }


    



  // }
  
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

void Escena::objetosSeleccionables()
{
  if(!Iluminacion)
  {
    Tupla3f c_esf = esfera->getColor();
    Tupla3f c_coche = coche->getColor();

    if(c_esf(0) < 1.0 && c_esf(1) < 1.0 && c_esf(2) < 1.0)
      c_esf = {(float)(c_esf(0) + 0.1),(float)(c_esf(1) + 0.1),(float)(c_esf(2) + 0.1)};
    else
      c_esf = {0.0,0,0};
      
    if(c_coche(0) < 1.0 && c_coche(1) < 1.0 && c_coche(2) < 1.0)
      c_coche = {(float)(c_coche(0) + 0.1),((float)c_coche(1) + 0.1),(float)(c_coche(2) + 0.1)};
    else
      c_coche = {0.0,0,0};

    esfera->aniadirColor(c_esf);
    coche->aniadirColor(c_coche);
  }else
  {
    Material* m_coche = coche->getMaterial();
    Material* m_esfera = esfera->getMaterial();
    Tupla4f c_amb = m_coche->getAmbiente();
    Tupla4f e_amb = m_esfera->getAmbiente();

    if(c_amb(0) < 0.5 && c_amb(1) < 0.5 && c_amb(2) < 0.5 && c_amb(3) < 0.5)
        m_coche->setAmbiente({(float)(c_amb(0) + 0.1),(float)(c_amb(1) + 0.1),(float)(c_amb(2) + 0.1),(float)(c_amb(3) + 0.1)});
    else
      m_coche->setAmbiente({0,0,0,0});

    if(e_amb(0) < 1.0 && e_amb(1) < 1.0 && e_amb(2) < 1.0 && e_amb(3) < 1.0)
        m_esfera->setAmbiente({(float)(e_amb(0) + 0.1),(float)(e_amb(1) + 0.1),(float)(e_amb(2) + 0.1),(float)(e_amb(3) + 0.1)});
    else
      m_esfera->setAmbiente({0,0,0,0});  

    coche->setMaterial(*m_coche);  
    esfera->setMaterial(*m_esfera);
  }
}
/***************************************************************
 *En esta funcion comprobaremos si el botón derecho está pulsado
*en ese caso actualizaremos la posición de la cámara en función
*del desplazamiento del cursor 
****************************************************************/
void Escena::ratonMovido(int x, int y)
{
  if(camaras[camaraActiva]->getSeleccion() && click) 
  {
    camaras[camaraActiva]->rotarXExaminar((x - xant)*0.0001);
    camaras[camaraActiva]->rotarYExaminar((y - yant)*0.0001);

    xant = x;
    yant = y;
  }else
  {
    if(click)
    {
      camaras[camaraActiva]->rotarXFirstPerson((x - xant)*0.0001);
      camaras[camaraActiva]->rotarYFirstPerson((y - yant)*0.0001);

      xant = x;
      yant = y;
    }
  }
}

void Escena::clickRaton(int boton, int estado,int x, int y)
{
   if(boton == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN ) 
   {
      click = 1;
      xant = x;
      yant = y;
   }
   else
   {
      if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN ) 
      {
        xsel = x;
        ysel = y;
        dibujarSeleccion();
      }else
      {
        if(boton == 3 && estado == GLUT_UP)
        {
          if(camaras[camaraActiva] != nullptr)
            camaras[camaraActiva]->zoom(1);
        }else
        {
          if(boton == 4 && estado == GLUT_UP)
          {
            if(camaras[camaraActiva] != nullptr)
              camaras[camaraActiva]->zoom(-1);
          }else
          {
            click = false;
          }
        }
      }
   }
}

void Escena::dibujarSeleccion()
{
  bool luces = false, texturas = false;
  if(glIsEnabled(GL_LIGHTING))
  {
    luces = true;
    Iluminacion = false;
    glDisable(GL_LIGHTING);
  }

  if(glIsEnabled(GL_TEXTURE_2D))
  {
    texturas = true;
    glDisable(GL_TEXTURE_2D);
  }
  //Salvaguardamos los valores de estas variables para restablecerlos al terminar la seleccion
  int m = modo;
  bool l = lineas, s = solido, p = puntos;

  modo = 1;
  lineas = false, puntos = false, solido = true;


  //Asignamos los colores necesarios para la selección
  asignarColoresSeleccion();

  //Dibujamos la escena con los colores de seleccion
  dibujar();
  
  GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);
  float  buffer_seleccion[4];
  glReadPixels(xsel,viewport[3]-ysel,1,1,GL_RGB,GL_FLOAT,(void*)buffer_seleccion);


  //Restauramos los colores anteriores a la seleccion
  restaurarColoresSeleccion();
  
  //Vemos cual ha sido el objeto seleccionado
  if(round(buffer_seleccion[0]*10)/10 == 0.0 && round(buffer_seleccion[1]*10)/10 == 0.0 && round(buffer_seleccion[2]*10)/10 == 0.0)
  {
    std::cout<<"Ha seleccionado el coche:\n";
    this->camaras[camaraActiva]->setAt(coche->getPosicion());
    this->camaras[camaraActiva]->setSeleccion(true);
  }else
    {
      if(round(buffer_seleccion[0]*10)/10 == 0.1 && round(buffer_seleccion[1]*10)/10 == 0.1 && round(buffer_seleccion[2]*10)/10 == 0.1)
      {
        this->camaras[camaraActiva]->setSeleccion(true);
        std::cout<<"Ha seleccionado la esfera:\n";
        this->camaras[camaraActiva]->setAt(esfera->getPosicion());
      }else
      {
        this->camaras[camaraActiva]->setSeleccion(false);
        std::cout<<"No ha seleccionado ningún objeto seleccionable\n";
        this->camaras[camaraActiva]->setAt({0,0,0});  //Si no se selecciona ningún objeto seleccionable fijamos el at en el origen
      }
    }
    

  //Al terminar ponemos xsel ysel a valores nulos
  xsel = -1; 
  ysel = -1;

  if(luces){
    glEnable(GL_LIGHTING);
    Iluminacion = true;
  }

  if(texturas)
    glEnable(GL_TEXTURE_2D);  

  //Restauramos los valores que anteriormente guardabamos
  modo = m;
  lineas = l, puntos = p, solido = s;  
}

void Escena::asignarColoresSeleccion()
{
  this->coche->aniadirColor({0.0,0.0,0.0});
  this->esfera->aniadirColor({0.1,0.1,0.1});
}

void Escena::restaurarColoresSeleccion()
{
  this->coche->aniadirColor({0.5,0.2,1.0});
  this->esfera->aniadirColor({0.0,0.5,0.5});
}
// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************


class ObjRevolucion : public Malla3D
{
   public:
   ObjRevolucion();
   ObjRevolucion(const std::string & archivo, int num_instancias, bool tapas=true) ;
   ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapas=true) ;
   void draw(int modo,bool puntos,bool lineas,bool solido,bool tapas) ;
   void draw_ModoInmediato(char L,bool tapas) ;
   void draw_Chess(bool tapas) ;
   void draw_ModoDiferido(char L,bool tapas) ;
   int contador=0;
private:
    int num_instancias;
    bool tapas = true;
    std::vector<float> distancias_perfil;
    void gestionDeTapas(std::vector<Tupla3f> &perfil_original, int num_instancias);
    bool existeTapaInf(std::vector<Tupla3f> perfil_original, int num_instancias);
    bool existeTapaSup(std::vector<Tupla3f> perfil_original, int num_instancias);
    std::vector<Tupla3f> generarOrdenInverso(std::vector<Tupla3f> perfil_original);
    void obtenerPuntosCoordenadas();
    void CalcularDistanciasPerfil();
    double calcularDistanciaVertices(Tupla3f anterior, Tupla3f siguiente);
    std::vector<Tupla3f> perf_original;
protected:
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias,bool tapas);
    int N,M;
} ;




#endif

#pragma once

#include "./SDLutil.h"
#include "./ImageLoader.h"
#include "../../utils/Observador/Observador.h"
#include "../../utils/Observador/Identificable.h"
#include "../Controlador/ControladorScroll.h"
#include "../../Servidor/modelo/EstadoNivel.h"

class VistaScroll: public Observador, public Identificable{

	private:
		int _id;
		double x;
		double y;
		double alto;
		double ancho;		
		bool esNecesarioRefrescar;
		double anchoNivel;
		double altoNivel;
		SDLutil* utilidadSDL;
		Posicion posicionInicial,posicionFinal;

	public:
		VistaScroll(double x,double y,double alto,double ancho, double anchoNivel, double altoNivel,SDL_Surface* pantalla,int id);
		~VistaScroll(void);

		void graficar(SDL_Surface*,EstadoNivel*);
		void obtenerTilesLimites(Posicion& posicionInicial, Posicion& posicionFinal);
		void actualizar(class Observable* s);
		int id();

		// Getters
		double getX(void);
		double getY(void);
		double getAlto(void);
		double getAncho(void);
		bool getEsNecesarioRefrescar(void);

		// Setters
		void setEsNecesarioRefrescar(bool boolRefrescar);

};
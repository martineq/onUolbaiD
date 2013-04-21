#pragma once

#include "./SDLutil.h"
#include "./ImageLoader.h"
#include <winsock.h>  // Para usar InterlockedIncrement()
#include "../../utils/Observador/Observador.h"
#include "../../utils/Observador/Identificable.h"
#include "../../Servidor/modelo/ModeloScroll.h"
#include "../Controlador/ControladorScroll.h"

class VistaScroll: public Observador, public Identificable{

	private:
		//int id;
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
		static long contador; // Para generar ID's Automáticos

	public:
		VistaScroll(double x,double y,double alto,double ancho, double anchoNivel, double altoNivel,SDL_Surface* pantalla);
		~VistaScroll(void);

		void graficar(SDL_Surface*);
		void obtenerTilesLimites(Posicion& posicionInicial, Posicion& posicionFinal);
		void actualizar(class Observable* s);
		int id() const;

		// Getters
		//int getId(void);
		double getX(void);
		double getY(void);
		double getAlto(void);
		double getAncho(void);
		bool getEsNecesarioRefrescar(void);

		// Setters
		void setEsNecesarioRefrescar(bool boolRefrescar);

};
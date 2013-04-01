#pragma once

#include <winsock.h>  // Para usar InterlockedIncrement()
#include "../../utils/Observador/Observable.h"
#include "../../utils/Observador/Observador.h"
#include "../../utils/Constantes/Constantes.h"
#include <list>

class ModeloScroll: public Observable{

	private:
		int x, y, ancho, alto;
		int margen, velocidad;
		std::list<Observador*> observadores;
		bool calcularPosicion(int mouseX, int mouseY);

		int id;	// ID Autom�tico

	public:
		ModeloScroll(int tAncho, int tAlto, int tMargen, int tVelocidad, int personajeX, int personajeY, int idPersonaje);
		~ModeloScroll(void);

		void actualizar(int mouseX, int mouseY);
		int getX();
		int getY();
		int getAlto();
		void setAlto(int nuevoAlto);
		void setAncho(int nuevoAncho);
		int getAncho();
		int getMargen();
		
		void agregarObservador(Observador *m);
		void removerObservador(Observador *m);

		void cambiarEstado();
		int obtenerId(void);

		
};


// TODO: Importante: El m�todo cambiarEstado() tiene que estar regulado por un timer para poder controlar
//                   el tr�fico de datos que le ser� enviado al VistaScroll. La idea es que el ModeloLoop
//					 tenga ese timer y cada cierto per�odo (1/15 seg) ordene a toda la lista de ModeloScroll 
//					 que contiene ModeloNivel hacer el cambiarEstado(), si es que de verdad cambi� el estado.
//					 De esta manera el Modelo calcula todo lo que le llega a trav�s del controlador,
//					 pero s�lo lo env�a a la Vista cuando esta lo necesita. (Lo pongo ac� para no olvidarme)
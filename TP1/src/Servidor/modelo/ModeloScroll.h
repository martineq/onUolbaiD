#pragma once

#include <winsock.h>  // Para usar InterlockedIncrement()
#include "../../utils/Observador/Observable.h"
#include "../../utils/Observador/Observador.h"
#include "../../utils/Constantes/Constantes.h"
#include "ModeloEntidad.h"
#include <list>
#include <math.h>

class ModeloScroll: public Observable{

	private:
		int x, y, pPantallaAncho, pPantallaAlto, tEscenarioAncho, tEscenarioAlto;
		int margen, velocidad;
		std::list<Observador*> observadores;
		bool calcularPosicion(int mouseX, int mouseY);

		int id;	// ID a partir del id del jugador

	
	

	public:
		ModeloScroll(int pPantallaAncho, int pPantallaAlto, int tEscenarioAncho, int tEscenarioAlto, int tMargen, int tVelocidad, int personajeX, int personajeY, int idPersonaje);
		~ModeloScroll(void);

		void actualizar(int mouseX, int mouseY);
		int getX();
		int getY();
		int getAlto();
		void setAlto(int nuevoAlto);
		void setAncho(int nuevoAncho);
		int getAncho();
		int getMargen();
		
		//void agregarObservador(Observador *m);
		//void removerObservador(Observador *m);

		void cambiarEstado();
		int obtenerId(void);

		bool enMargen(int x, int y);
		
};


// TODO: Importante: El método cambiarEstado() tiene que estar regulado por un timer para poder controlar
//                   el tráfico de datos que le será enviado al VistaScroll. La idea es que el ModeloLoop
//					 tenga ese timer y cada cierto período (1/15 seg) ordene a toda la lista de ModeloScroll 
//					 que contiene ModeloNivel hacer el cambiarEstado(), si es que de verdad cambió el estado.
//					 De esta manera el Modelo calcula todo lo que le llega a través del controlador,
//					 pero sólo lo envía a la Vista cuando esta lo necesita. (Lo pongo acá para no olvidarme)
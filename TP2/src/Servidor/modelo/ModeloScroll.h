#pragma once

#include <winsock.h>  // Para usar InterlockedIncrement()
#include "../../utils/Observador/Observable.h"
#include "../../utils/Observador/Identificable.h"
#include "../../utils/Constantes/Constantes.h"
#include "ModeloEntidad.h"
#include <list>
#include <math.h>
#include <iostream>

class ModeloScroll: public Observable, public Identificable {
	private:
		int x, y, pPantallaAncho, pPantallaAlto, tEscenarioAncho, tEscenarioAlto;
		int pEscenarioAlto, pEscenarioAncho;
		int margen;
		int desplazamientoX, desplazamientoY;

		int _id;	// ID a partir del id del jugador

	public:
		ModeloScroll(int pPantallaAncho, int pPantallaAlto, int tEscenarioAncho, int tEscenarioAlto, int tMargen, int personajeX, int personajeY, int idPersonaje);
		virtual ~ModeloScroll();

		void actualizar(int mouseX, int mouseY);
		void detener();
		int getX();
		int getY();
		int getAlto();
		void setAlto(int nuevoAlto);
		void setAncho(int nuevoAncho);
		int getAncho();
		int getMargen();
		
		void cambiarEstado();
		void notificarPosicionInicial();
		int id() const;
};

// TODO: Mudar a ControladorScroll
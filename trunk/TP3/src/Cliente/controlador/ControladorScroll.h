#pragma once

#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observable.h"
#include "../../Servidor/modelo/Posicion.h"

class ControladorScroll : public Observable {
	private:
		int x, y, pPantallaAncho, pPantallaAlto, tEscenarioAncho, tEscenarioAlto;
		int pEscenarioAlto, pEscenarioAncho;
		int margen;
		int desplazamientoX, desplazamientoY;

	public:
		ControladorScroll(int pPantallaAncho, int pPantallaAlto, int tEscenarioAncho, int tEscenarioAlto, int tMargen, int personajeX, int personajeY);
		virtual ~ControladorScroll();

		void actualizar(int mouseX, int mouseY);
		void detener();
		int getX();
		int getY();
		int getAlto();
		int getAncho();
		int getMargen();
		
		void cambiarEstado();
};

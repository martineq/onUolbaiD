#pragma once

#include <winsock.h>  // Para usar InterlockedIncrement()
#include "../../utils/Observador/Observable.h"
#include "../../utils/Constantes/Constantes.h"


class ModeloScroll: public Observable{

	private:
		int x, y, ancho, alto;
		int margen, velocidad;
		void calcularPosicion(int mouseX, int mouseY);

		long id;	// ID Automático
		static long contador; // Para generar ID's Automáticos

	public:
		ModeloScroll(int tAncho, int tAlto, int tMargen, int tVelocidad, class Observable *m);
		~ModeloScroll(void);

		void refresh(class Observable *m);
		int getX();
		int getY();
		int getAlto();
		void setAlto(int nuevoAlto);
		void setAncho(int nuevoAncho);
		int getAncho();
		int getMargen();

		void cambiarEstado();
		int obtenerId(void);

};



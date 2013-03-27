#pragma once

#include "../../utils/Observador/Observador.h"
#include "../../utils/Observador/Observable.h"
#include "../../utils/Constantes/Constantes.h"

class ModeloScroll:public Observador{

	private:
		int x, y, ancho, alto;
		int margen, velocidad;
		void calcularPosicion(int mouseX, int mouseY);

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


};



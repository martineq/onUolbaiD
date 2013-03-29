#pragma once
#include "../../utils/Observador/Observable.h"
		
class ControladorEvento: public Observable{
	private:
		int posicionMouseX;
		int posicionMouseY;
		int clicMouseBotonDerecho;
		int clicMouseBotonIzquierdo;
	public:
		ControladorEvento(void);
		~ControladorEvento(void);		
		void setPosicionMouseX(int);
		void setPosicionMouseY(int);
		void setPosicionMouseXY (int,int);
		void setClicMouseBotonDerecho(int);
		void setClicMouseBotonIzquierdo(int);
		int getPosicionMouseX();
		int getPosicionMouseY();
		int getClicMouseBotonDerecho();
		int getClicMouseBotonIzquierdo();
		void cambiarEstado();

};

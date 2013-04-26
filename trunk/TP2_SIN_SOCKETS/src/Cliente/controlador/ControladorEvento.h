#pragma once
#include "../../utils/Observador/Observable.h"
		
class ControladorEvento: public Observable{
	private:
		int posicionMouseX;
		int posicionMouseY;
		int clicMouseBotonDerecho;
		int clicMouseBotonIzquierdo;	
		bool mouseDentroDePantalla;
		bool teclaAApretada;
		bool teclaSApretada;
	public:
		ControladorEvento(void);
		~ControladorEvento(void);		
		void setPosicionMouseX(int);
		void setPosicionMouseY(int);
		void setPosicionMouseXY (int,int);
		void setClicMouseBotonDerecho(int);
		void setClicMouseBotonIzquierdo(int);
		void setMouseDentroDePantalla(bool);
		void setTeclaAApretada(bool);
		void setTeclaSApretada(bool);
		int getPosicionMouseX();
		int getPosicionMouseY();
		int getClicMouseBotonDerecho();
		int getClicMouseBotonIzquierdo();
		bool getMouseDentroDePantalla();
		bool getTeclaAApretada();
		bool getTeclaSApretada();
		void cambiarEstado();

};

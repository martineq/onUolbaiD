#pragma once

#include "../../utils/Proxy/ProxyControladorEvento.h"

class ControladorEvento{
	private:
		int posicionMouseX;
		int posicionMouseY;
		int clicMouseBotonDerecho;
		int clicMouseBotonIzquierdo;	
		bool mouseDentroDePantalla;
		ProxyControladorEvento proxyEvento;

	public:
		ControladorEvento(void);
		~ControladorEvento(void);		
		void setPosicionMouseX(int);
		void setPosicionMouseY(int);
		void setPosicionMouseXY (int,int);
		void setClicMouseBotonDerecho(int);
		void setClicMouseBotonIzquierdo(int);
		void setMouseDentroDePantalla(bool);
		int getPosicionMouseX();
		int getPosicionMouseY();
		int getClicMouseBotonDerecho();
		int getClicMouseBotonIzquierdo();
		bool getMouseDentroDePantalla();
		void cambiarEstado();

};


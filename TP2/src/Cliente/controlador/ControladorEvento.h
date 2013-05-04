#pragma once

#include "../../utils/Proxy/ProxyControladorEvento.h"
#include "./ControladorScroll.h"

class ControladorEvento{

	private:
		int posicionMouseX;
		int posicionMouseY;
		int clicMouseBotonDerecho;
		int clicMouseBotonIzquierdo;	
		bool mouseDentroDePantalla;
		ControladorScroll* controladorScroll;
		ProxyControladorEvento* proxyEvento;

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
		void setControladorScroll(ControladorScroll*);
		ControladorScroll* getControladorScroll(void);
		void setProxyEvento(ProxyControladorEvento* pProxyEvento);
		ProxyControladorEvento* getProxyEvento(void);

};


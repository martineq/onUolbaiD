#pragma once

#include "../../utils/Proxy/ProxyControladorEvento.h"
#include "./ControladorScroll.h"

class ControladorEvento{

	private:
		int idJugador;
		int posicionMouseX;
		int posicionMouseY;
		int clicMouseBotonDerecho;
		int clicMouseBotonIzquierdo;	
		double altoNivelEnPixel;
		double anchoNivelEnPixel;
		bool mouseDentroDePantalla;
		ControladorScroll* controladorScroll;
		ProxyControladorEvento* pProxyEvento;
		bool finalizoElJuego;
		bool teclaAApretada;
		bool teclaSApretada;

	public:
		ControladorEvento(void);
		~ControladorEvento(void);		
		void setIdJugador(int id);
		void setPosicionMouseX(int);
		void setPosicionMouseY(int);
		void setPosicionMouseXY (int,int);
		void setClicMouseBotonDerecho(int);
		void setClicMouseBotonIzquierdo(int);
		void setMouseDentroDePantalla(bool);
		void setFinalizoElJuego(bool valor);
		void setTeclaAApretada(bool);
		void setTeclaSApretada(bool);
		void setProxyEvento(ProxyControladorEvento* pProxyEvento);
		void setControladorScroll(ControladorScroll*, double, double);
		int getPosicionMouseX();
		int getPosicionMouseY();
		int getClicMouseBotonDerecho();
		int getClicMouseBotonIzquierdo();
		bool getMouseDentroDePantalla();
		bool getFinalizoElJuego(void);
		bool getTeclaAApretada();
		bool getTeclaSApretada();
		void notificarAlProxy();		
		ControladorScroll* getControladorScroll(void);		
		ProxyControladorEvento* getProxyEvento(void);

};


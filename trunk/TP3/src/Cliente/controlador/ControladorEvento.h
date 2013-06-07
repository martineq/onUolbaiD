#pragma once

#include "../../utils/Proxy/ProxyControladorEvento.h"
#include "./ControladorScroll.h"
#include "../vista/VistaMusica.h"

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
		bool teclaDApretada;
		bool teclaFApretada;

	public:
		ControladorEvento(void);
		~ControladorEvento(void);		
		void setIdJugador(int id);
		void setPosicionMouseXY (int,int);
		void setClicMouseBotonDerecho(int);
		void setClicMouseBotonIzquierdo(int);
		void setFinalizoElJuego(bool valor);
		void setTeclaAApretada(bool);
		void setTeclaSApretada(bool);
		void setTeclaDApretada(bool);
		void setTeclaFApretada(bool);
		void setQuit();
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
		bool getTeclaDApretada();
		bool getTeclaFApretada();
		void notificarAlProxy();
		void limpiar();
		ControladorScroll* getControladorScroll(void);		
		ProxyControladorEvento* getProxyEvento(void);
		bool chequearConexion();
};


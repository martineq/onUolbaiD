#pragma once
#include <SDL.h>
#include <vector>
#include <Windows.h>

class DetectorEventos{

	private:
		int posicionMouseX;
		int posicionMouseY;
		int clicMouseBotonIzquierdo;
		int clicMouseBotonDerecho;
		bool quit;
		bool dentroDePantalla;
		bool teclaSApretada;
		bool teclaAApretada;
		bool teclaDApretada;
		bool teclaFApretada;
		bool enter;
		bool escape;
		bool retroceso;
		char caracter;

	public:
		DetectorEventos();		
		virtual ~DetectorEventos();
		void detectar();
		int getPosicionMouseX();
		int getPosicionMouseY();
		int getClicMouseBotonIzquierdo();
		int getClicMouseBotonDerecho();
		bool getQuit();
		bool getDentroDePantalla();
		bool getTeclaAApretada();
		bool getTeclaSApretada();
		bool getTeclaDApretada();
		bool getTeclaFApretada();
		bool getEnter();
		bool getEscape();
		bool getRetroceso();
		char getCaracter();
		std::vector<int> getEventos();
};

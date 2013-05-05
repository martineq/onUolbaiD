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
		int ticks;
		bool quit;
		bool dentroDePantalla;
		bool teclaSApretada;
		bool teclaAApretada;
	public:
		DetectorEventos(void);		
		~DetectorEventos(void);
		void detectar();
		int getPosicionMouseX();
		int getPosicionMouseY();
		int getClicMouseBotonIzquierdo();
		int getClicMouseBotonDerecho();
		bool getQuit();
		bool getDentroDePantalla();
		bool getTeclaAApretada();
		bool getTeclaSApretada();
		std::vector<int> getEventos();

};

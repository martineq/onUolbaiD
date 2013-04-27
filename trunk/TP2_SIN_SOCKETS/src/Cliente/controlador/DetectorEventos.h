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
		int ticks;
	public:
		DetectorEventos(void);		
		~DetectorEventos(void);
		void detectar();
		int getPosicionMouseX();
		int getPosicionMouseY();
		int getClicMouseBotonIzquierdo();
		int getClicMouseBotonDerecho();
		bool getTeclaAApretada();
		bool getTeclaSApretada();
		bool getQuit();
		bool getDentroDePantalla();
		std::vector<int> getEventos();

};

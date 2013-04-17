#pragma once
#include <SDL.h>
#include <vector>

class DetectorEventos{

	private:
		int posicionMouseX;
		int posicionMouseY;
		int clicMouseBotonIzquierdo;
		int clicMouseBotonDerecho;
		bool quit;
		bool dentroDePantalla;
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
		std::vector<int> getEventos();

};

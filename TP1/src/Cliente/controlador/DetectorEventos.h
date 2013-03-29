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
	public:
		DetectorEventos(void);		
		~DetectorEventos(void);
		void detectar();
		int getPosicionMouseX();
		int getPosicionMouseY();
		int getClicMouseBotonIzquierdo();
		int getClicMouseBotonDerecho();
		bool getQuit();
		std::vector<int> getEventos();

};

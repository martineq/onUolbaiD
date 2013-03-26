#include "ControladorJuego.h"

ControladorJuego::ControladorJuego(void){
}

ControladorJuego::~ControladorJuego(void){
}

void ControladorJuego::loop(){
	bool quit = false;	
	this->pantalla.levantar();
	while (!quit)
	{
		this->detector.detectar();
		quit = this->detector.getQuit();
		this->pantalla.dibujar();

		//poner un delay para que no se coma todo el procesador.

	}

}

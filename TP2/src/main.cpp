#include <iostream>

#include "./Administrador.h"
//#include <vld.h>

int main(int argc, char* argv[]) {

	std::string mote;
	std::string personaje;
	if( argc > 2){
		mote.assign(argv[1]);
		personaje.assign(argv[2]);
	}

	Administrador administrador; 
	administrador.correrJuego(mote,personaje);
	//administrador.correrPruebas(); // Para correr pruebas

	return 0;
}

#include <iostream>

#include "./Administrador.h"
//#include <vld.h>

int main(int argc, char* argv[]) {

	Administrador administrador; 
	administrador.correrPruebas(); // Para correr pruebas
	//administrador.setModoServidor(true); // TODO: ¿Esta decisión la toma de argv?
	//if( administrador.iniciar() == true ){
	//	administrador.loop();
	//}

	return 0;
}


#include <iostream>

#include "./Administrador.h"
//#include <vld.h>

int main(int argc, char* argv[]) {
	Administrador administrador;
	if (administrador.iniciar()) {
		administrador.loop();
	}

	//administrador.correrPruebas();
	
	return 0;
}

#include <iostream>
#include "./utils/Pruebas/Pruebas.h"
//#include <vld.h> // >> S�lo descomentar para chequeo de memoria. Habilitar DLL de depuraci�n multiproceso (/MDd).

int main(int argc, char* argv[]) {

	Pruebas p;
	//p.PruebaSdl();	// Prueba SDL + log
	p.PruebaYAML();	// Prueba YAML

	return 0;
}



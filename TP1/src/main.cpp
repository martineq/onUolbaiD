#include <iostream>
#include "./utils/Pruebas/Pruebas.h"
//#include <vld.h> // >> Sólo descomentar para chequeo de memoria. Habilitar DLL de depuración multiproceso (/MDd).

int main(int argc, char* argv[]) {

	Pruebas p;
	//p.PruebaSdl();	// Prueba SDL + log
	p.PruebaYAML();	// Prueba YAML

	return 0;
}



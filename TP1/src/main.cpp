#include <iostream>

#include "./utils/Pruebas/Pruebas.h"
#include "Servidor/modelo/ModeloEntidad.h"
#include "Cliente\controlador\ControladorJuego.h"
//#include <vld.h> // >> S�lo descomentar para chequeo de memoria. Habilitar DLL de depuraci�n multiproceso (/MDd).

using namespace std;

int main(int argc, char* argv[]) {

	Pruebas p;
	//p.PruebaSdl(); // Prueba SDL + log
	//p.PruebaYAML();	// Prueba YAML

	//char* a = new char;
	//ModeloEntidad::prueba();

	ControladorJuego controlador;
	controlador.loop();

	return 0;
}


#include "Administrador.h"

Administrador::Administrador(void){

}

Administrador::~Administrador(void){

}

void Administrador::iniciar(void){

}

void Administrador::loop(void){

}


void Administrador::correrPruebas(void){

	Pruebas p;
	//p.PruebaSdl(); // Prueba SDL + log
	//p.PruebaYAML();	// Prueba YAML
	p.PruebaModeloEntidad();
	//p.PruebaControladorJuego();
	//p.PruebaHilos();
}

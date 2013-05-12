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
	//administrador.correrPruebas(); // Para correr pruebas
	administrador.correrJuego(mote,personaje);

	/*Pruebas pruebas;
	std::string opc;
	while ( opc.compare("s") != 0 && opc.compare("c") != 0){
		std::cout << "Ingrese \"s\" para iniciar servidor o \"c\" para iniciar cliente" << std::endl;
		getline (std::cin,opc);
		std::cout << "Ingreso: "<< opc << std::endl;
	}
	
	if (opc == "s")
		pruebas.PruebaServidorChat();
	else if (opc == "c")
		pruebas.PruebaClienteChat();*/

	return 0;
}


#include <iostream>
#include "./utils/Pruebas/Pruebas.h"
//#include <vld.h> // >> S�lo descomentar para chequeo de memoria. Habilitar DLL de depuraci�n multiproceso (/MDd).

int main(int argc, char* argv[]) {

	std::cout << "Mart -> SVN... Ok!" << std::endl;
	std::cout << "Mart -> SDL... Ok!" << std::endl;
	std::cout << "Mart -> VLD... Ok!" << std::endl;
	std::cout << "Mart -> YAML... Ok!" << std::endl;

	std::cout << "Dany -> SVN... Ok!" << std::endl;
	std::cout << "Dany -> SDL... Ok!" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;

	std::cout << "Seba -> SVN... Ok!" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;

	std::cout << "Matias -> SVN... Ok!" << std::endl;
	std::cout << "Matias -> SDL... Ok!" << std::endl;
	std::cout << "Matias -> VLD... Ok!" << std::endl;
	std::cout << "" << std::endl;

	Pruebas p;
	p.PruebaSdl();	// Prueba SDL + log
	p.PruebaYAML();	// Prueba YAML

	char c;
	std::cin >> c;

	char* puntero = new char;	// Creo un puntero y nunca lo saco de memoria din�mica. Para ver si me lo detecta el VLD.

	return 0;
}

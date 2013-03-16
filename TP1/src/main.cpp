#include <iostream>
#include "./utils/Pruebas.h"

int main(int argc, char* argv[]){

	std::cout << "Mart -> SVN... Ok!" << std::endl;
	std::cout << "Dany -> SVN... Ok!" << std::endl;
	std::cout << "Dany -> SDL... Ok!" << std::endl;
	std::cout << "Seba -> SVN... Ok!" << std::endl;
	std::cout << "Matias -> SVN... Ok!" << std::endl;
	std::cout << "" << std::endl;

	//Habilitando estas líneas se puede probar la biblioteca SDL
	Pruebas p;
	p.PruebaSdl();

	char c;
	std::cin >> c;

	return 0;
}

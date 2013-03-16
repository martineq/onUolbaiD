#include <iostream>
#include "./utils/Pruebas/Pruebas.h"


int main(int argc, char* argv[]){

	std::cout << "Mart -> SVN... Ok!" << std::endl;
	std::cout << "Mart -> SDL... Ok!" << std::endl;
	std::cout << "Dany -> SVN... Ok!" << std::endl;
	std::cout << "Dany -> SDL... Ok!" << std::endl;
	std::cout << "Seba -> SVN... Ok!" << std::endl;
	std::cout << "Matias -> SVN... Ok!" << std::endl;
	std::cout << "" << std::endl;

	//Habilitando estas líneas se puede probar la biblioteca SDL + Escritura en el archivo de log
	Pruebas p;
	p.PruebaSdl();

	char c;
	std::cin >> c;

	return 0;
}

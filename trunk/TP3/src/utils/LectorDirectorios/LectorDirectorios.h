#pragma once

#include <iostream>
#include <vector>
#include <winsock.h>  // <windows.h> est� contenida <winsock.h>, la dejo as� porque se va a usar
#include "../Constantes/Constantes.h" 

class LectorDirectorios{

	private:
		bool nombreValido(std::string nombre);

	public:
		LectorDirectorios(void);
		~LectorDirectorios(void);
		std::vector<std::string> leerDirectorio(const char* rutaDirectorio);

};

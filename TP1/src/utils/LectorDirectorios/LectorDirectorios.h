#pragma once

#include <iostream>
#include <vector>
#include <winsock2.h>  // <windows.h> est� contenida <winsock2.h>, la dejo as� porque se va a usar

class LectorDirectorios{

	private:
		bool nombreValido(std::string nombre);

	public:
		LectorDirectorios(void);
		~LectorDirectorios(void);
		std::vector<std::string> leerDirectorio(const char* rutaDirectorio);

};

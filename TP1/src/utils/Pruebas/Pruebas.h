#pragma once

#include <SDL.h>
#include "../Constantes.h"
#include "../Log/log.h"
#include "../yaml/ParserYaml.h"

class Pruebas{

public:
	Pruebas(void);
	~Pruebas(void);
	void PruebaSdl(void);
	void PruebaYAML(void);

};

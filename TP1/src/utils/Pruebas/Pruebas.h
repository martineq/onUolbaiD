#pragma once

// ************************************************************************************* //
// Esta clase no pertenece al proyecto. Es sólo para correr pruebas de distintas clases. //
// Sirve para poner ese código acá en vez de dejarlo mezclado con el código del proyecto //
// ************************************************************************************* //

#include <SDL.h>
#include "../Constantes/Constantes.h"
#include "../Log/log.h"
#include "../yaml/ParserYaml.h"
#include "../../Servidor/modelo/ModeloEntidad.h"

class Pruebas{

	public:

		Pruebas(void);
		~Pruebas(void);
		void PruebaSdl(void);
		void PruebaYAML(void);
		void PruebaModeloEntidad(void);

};

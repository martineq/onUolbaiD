#pragma once

#include "./VistaFactory.h"
#include "./VistaNivel.h"
#include "./VistaLoop.h"

class VistaJuego{

	private:
		VistaFactory vistaFactory;
		VistaNivel vistaNivel;
		VistaLoop vistaLoop;

	public:
		VistaJuego(void);
		~VistaJuego(void);

};

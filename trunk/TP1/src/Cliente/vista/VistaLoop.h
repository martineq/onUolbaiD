#pragma once
#include "VistaNivel.h"
class VistaLoop{
	private:
		VistaNivel pantalla;
	public:
		VistaLoop(void);
		~VistaLoop(void);
		void levantarPantalla();
		void loop ();

};

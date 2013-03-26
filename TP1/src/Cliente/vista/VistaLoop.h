#pragma once
#include "VistaPantalla.h"
class VistaLoop{
	private:
		VistaPantalla pantalla;
	public:
		VistaLoop(void);
		~VistaLoop(void);
		void levantarPantalla();
		void loop ();

};

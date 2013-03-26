#pragma once
#include "VistaNivel.h"
#include <vector>
class VistaLoop{
	private:
		VistaNivel pantalla;
	public:
		VistaLoop(void);
		~VistaLoop(void);
		void levantarPantalla();
		void loop (std::vector<int>);

};

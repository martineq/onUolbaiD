#pragma once

#include "../../utils/Observador/Observable.h"

class ControladorScroll: public Observable{

	public:
		ControladorScroll(void);
		~ControladorScroll(void);
		
		void cambiarEstado();

};

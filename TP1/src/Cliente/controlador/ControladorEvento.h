#pragma once

#include "../../utils/Observador/Observable.h"

class ControladorEvento: public Observable{

	public:
		ControladorEvento(void);
		~ControladorEvento(void);

		void cambiarEstado();

};

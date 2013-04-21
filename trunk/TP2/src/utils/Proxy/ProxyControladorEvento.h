#pragma once

#include "../Observador/Observable.h"

class ProxyControladorEvento: public Observable{

	public:
		ProxyControladorEvento(void);
		~ProxyControladorEvento(void);
		
		void cambiarEstado();
};

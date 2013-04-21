#pragma once

#include "../Observador/Observable.h"

class ProxyModeloEntidad: public Observable{
	
	public:
		ProxyModeloEntidad(void);
		~ProxyModeloEntidad(void);
		
		void cambiarEstado();
};

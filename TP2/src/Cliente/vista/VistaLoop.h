#pragma once

#include <SDL.h>
#include "./VistaNivel.h"
#include "./ImageLoader.h"
#include "../../utils/Proxy/ProxyModeloEntidad.h"

class VistaLoop{
	private:
		SDL_Surface *pantalla;			
		ProxyModeloEntidad* pProxyEntidad;
		ProxyModeloEntidad::stEntidad entidadEnEspera;
		bool hayEntidadEnEspera;

		void actualizarEntidadesPorProxy(VistaNivel& vistaNivel);
		void actualizarEntidad(ProxyModeloEntidad::stEntidad& entidad,VistaNivel& vistaNivel);
		bool dibujarEntidades(VistaNivel& vistaNivel);			

	public:
		VistaLoop(void);
		~VistaLoop(void);
		bool loop(VistaNivel& vistaNivel);

		void setPantalla(SDL_Surface *pantalla);
		void SetProxyModeloEntidad(ProxyModeloEntidad* pProxyEntidad);
		
};

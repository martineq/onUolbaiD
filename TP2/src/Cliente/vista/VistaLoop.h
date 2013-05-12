#pragma once

#include "./VistaNivel.h"
#include "./VistaFactory.h"
#include "./ImageLoader.h"
#include "../../utils/Proxy/ProxyModeloEntidad.h"

class VistaLoop{
	private:
		SDL_Surface *pantalla;			
		ProxyModeloEntidad* pProxyEntidad;
		ProxyModeloEntidad::stEntidad entidadEnEspera;
		bool hayEntidadEnEspera;

		bool actualizarEntidadesPorProxy(VistaNivel& vistaNivel,VistaFactory& vistaFactory);
		bool actualizarEntidad(ProxyModeloEntidad::stEntidad& entidad,VistaNivel& vistaNivel,VistaFactory& vistaFactory);
		bool dibujarEntidades(VistaNivel& vistaNivel);			

	public:
		VistaLoop(void);
		~VistaLoop(void);
		bool loop(VistaNivel& vistaNivel,VistaFactory& vistaFactory);

		void setPantalla(SDL_Surface *pantalla);
		void SetProxyModeloEntidad(ProxyModeloEntidad* pProxyEntidad);
		ProxyModeloEntidad** getPunteroProxy();
		SDL_Surface** getPunteroPantalla();
		
};

#pragma once

#include "VistaChat.h"
#include "VistaNivel.h"
#include "VistaFactory.h"
#include "ImageLoader.h"
#include "../../utils/Proxy/ProxyModeloEntidad.h"

class VistaLoop{
	private:
		SDL_Surface *pantalla;			
		ProxyModeloEntidad* pProxyEntidad;
		ProxyModeloEntidad::stEntidad entidadEnEspera;
		bool hayEntidadEnEspera;

		bool actualizarEntidadesPorProxy(VistaNivel& vistaNivel,VistaFactory& vistaFactory);
		bool actualizarEntidad(ProxyModeloEntidad::stEntidad& entidad,VistaNivel& vistaNivel,VistaFactory& vistaFactory);
		bool dibujarEntidades(VistaNivel& vistaNivel, char**);			

	public:
		VistaLoop(void);
		~VistaLoop(void);
		bool loop(VistaChat* vistaChat,VistaNivel& vistaNivel,VistaFactory& vistaFactory, char**);

		void setPantalla(SDL_Surface *pantalla);
		void SetProxyModeloEntidad(ProxyModeloEntidad* pProxyEntidad);
		char visibilidadDeLaEntidad(VistaEntidad* unaEntidad, char** matriz);
		void refrescarMatriz(VistaNivel& vistaNivel, char** matriz);
		ProxyModeloEntidad** getPunteroProxy();
		SDL_Surface** getPunteroPantalla();
		
};

#pragma once

#include "VistaChat.h"
#include "VistaNivel.h"
#include "VistaFactory.h"
#include "ImageLoader.h"
#include "VistaMusica.h"
#include "../../utils/Proxy/ProxyModeloEntidad.h"
#include "../../Servidor/modelo/EstadoNivel.h"

class VistaLoop{
	private:
		SDL_Surface *pantalla;			
		ProxyModeloEntidad* pProxyEntidad;
		ProxyModeloEntidad::stEntidad entidadEnEspera;
		bool hayEntidadEnEspera;
		VistaChat* vistaChat;

		bool actualizarEntidadesPorProxy(VistaNivel& vistaNivel,VistaFactory& vistaFactory);
		bool actualizarEntidad(ProxyModeloEntidad::stEntidad& entidad,VistaNivel& vistaNivel,VistaFactory& vistaFactory);
		bool dibujarEntidades(VistaNivel& vistaNivel, EstadoNivel* estadoNivel);

	public:
		VistaLoop(void);
		~VistaLoop(void);
		
		bool loop(VistaNivel& vistaNivel,VistaFactory& vistaFactory, EstadoNivel* estadoNivel);
		void setPantalla(SDL_Surface *pantalla);
		void SetProxyModeloEntidad(ProxyModeloEntidad* pProxyEntidad);
		char visibilidadDeLaEntidad(VistaEntidad* unaEntidad, EstadoNivel* estadoNivel);
		void refrescarMatriz(VistaNivel& vistaNivel, EstadoNivel* estadoNivel);
		ProxyModeloEntidad** getPunteroProxy();
		SDL_Surface** getPunteroPantalla();
		void asignarChat(VistaChat* vistaChat);
};

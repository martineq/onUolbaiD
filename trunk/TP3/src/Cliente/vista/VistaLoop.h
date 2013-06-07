#pragma once

#include "VistaChat.h"
#include "VistaNivel.h"
#include "VistaFactory.h"
#include "ImageLoader.h"
#include "VistaMusica.h"
#include "../../utils/SDLgfx/SDL_gfxPrimitives.h"
#include "../../utils/Proxy/ProxyModeloEntidad.h"
#include "../../Servidor/modelo/EstadoNivel.h"


class VistaLoop{
	private:
		SDL_Surface *pantalla;			
		ProxyModeloEntidad* pProxyEntidad;
		ProxyModeloEntidad::stEntidad entidadEnEspera;
		bool hayEntidadEnEspera;
		bool reproduciAtacar;
		VistaChat* vistaChat;

		bool actualizarEntidadesPorProxy(VistaNivel& vistaNivel,VistaFactory& vistaFactory);
		bool actualizarEntidad(ProxyModeloEntidad::stEntidad& entidad,VistaNivel& vistaNivel,VistaFactory& vistaFactory);
		bool dibujarEntidades(VistaNivel& vistaNivel, EstadoNivel* estadoNivel);
		bool dibujarStats(VistaNivel& vistaNivel);

		TTF_Font *fuente;
		SDL_Surface* textoVida;
		SDL_Surface* textoMagia;
		SDL_Surface* textoEscudo;
		SDL_Surface* textoCantidadMagia;
		SDL_Surface* textoCantidadBombas;

	public:
		VistaLoop(void);
		~VistaLoop(void);
		
		char visibilidadDeLaEntidad(VistaEntidad* unaEntidad, EstadoNivel* estadoNivel);
		bool loop(VistaNivel& vistaNivel,VistaFactory& vistaFactory, EstadoNivel* estadoNivel);
		void setPantalla(SDL_Surface *pantalla);
		void SetProxyModeloEntidad(ProxyModeloEntidad* pProxyEntidad);
		void reproducirSonidos(VistaNivel&);
		void asignarChat(VistaChat* vistaChat);		
		void refrescarMatriz(VistaNivel& vistaNivel, EstadoNivel* estadoNivel);
		ProxyModeloEntidad** getPunteroProxy();
		SDL_Surface** getPunteroPantalla();		
};

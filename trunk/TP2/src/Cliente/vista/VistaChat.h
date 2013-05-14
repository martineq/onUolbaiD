#pragma once

#include <iostream>
#include <string>
#include <list>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "VistaEntidad.h"
#include "../../utils/Posicion/Posicion.h"
#include "../../utils/Proxy/ProxyControladorEvento.h"
#include "../../utils/Serializacion/Serializadora.h"

class VistaChat {
	private:
		Posicion _posicion;
		bool _visible;
		std::list<std::string> _mensajes;
		std::string _textoIngresado;
		TTF_Font* _fuente;
		SDL_Surface* _ventana;
		int _altoOcupadoTextoMensajes;
		VistaEntidad* _remitente;
		VistaEntidad* _destinatario;
		ProxyControladorEvento* _proxyControladorEvento;
		
		void agregarMensaje(std::string remitente, std::string mensaje);

	public:
		VistaChat(Posicion posicion, VistaEntidad* remitente, ProxyControladorEvento* proxyControladorEvento);

		virtual ~VistaChat();

		void agregarMensaje(VistaEntidad* remitente, std::string mensaje);

		void asignarDestinatario(VistaEntidad* destinatario);

		void borrarCaracter();

		bool enviarMensaje();

		bool graficar(SDL_Surface* pantalla);

		void agregarCaracter(char caracter);

		bool visible() const;

		void visible(bool visible);
};

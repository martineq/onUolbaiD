#pragma once

#include <iostream>
#include <string>
#include <list>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../../utils/Posicion/Posicion.h"
#include "../../utils/Sockets/SocketCliente.h"
#include "../../utils/Serializacion/Serializadora.h"

class VistaChat {
	private:
		Posicion _posicion;
		std::string _remitente;
		std::string _destinatario;
		bool _visible;
		std::list<std::string> _mensajes;
		std::string _textoIngresado;
		TTF_Font* _fuente;
		SDL_Surface* _ventana;
		int _altoOcupadoTextoMensajes;
		SocketCliente* _socketCliente;
	
	public:
		VistaChat(Posicion posicion, std::string remitente, SocketCliente* socketCliente);

		virtual ~VistaChat();

		void agregarMensaje(std::string remitente, std::string mensaje);

		void asignarDestinatario(std::string destinatario);

		void borrarCaracter();

		bool enviarMensaje();

		bool graficar(SDL_Surface* pantalla);

		void agregarCaracter(char caracter);

		bool visible() const;

		void visible(bool visible);
};

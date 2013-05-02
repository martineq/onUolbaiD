#pragma once

#include <iostream>
#include <string>
#include <list>
#include <SDL.h>
#include <SDL_ttf.h>

#include "../../utils/Posicion/Posicion.h"

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
		SDL_Surface* _cajaTextoMensajes;
		SDL_Surface* _cajaTextoIngresado;

	public:
		VistaChat(Posicion posicion, std::string remitente);

		virtual ~VistaChat();

		void agregarMensaje(std::string remitente, std::string mensaje);

		void asignarDestinatario(std::string destinatario);

		bool graficar(SDL_Surface* pantalla);

		void teclaPresionada(Uint16 tecla);

		bool visible() const;

		void visible(bool visible);
};

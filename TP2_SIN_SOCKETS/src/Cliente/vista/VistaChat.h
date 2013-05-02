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
		bool _visible;
		std::list<std::string> _mensajes;
		std::string _textoIngresado;
		TTF_Font* _fuente;
		SDL_Surface* _ventana;
		SDL_Surface* _cajaTextoChat;
		SDL_Surface* _cajaTextoIngresado;

	public:
		VistaChat(Posicion posicion);

		virtual ~VistaChat();

		void agregarMensaje(std::string usuario, std::string mensaje);

		bool graficar(SDL_Surface* pantalla);

		void teclaPresionada(Uint16 tecla);

		bool visible() const;

		void visible(bool visible);
};

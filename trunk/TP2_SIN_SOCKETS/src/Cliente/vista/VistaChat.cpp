#include "VistaChat.h"

#define ALTO_MENSAJE 14
#define ANCHO_MENSAJE 220
#define CANTIDAD_MAXIMA_CARACTERES 20
#define CANTIDAD_MAXIMA_MENSAJES 10
#define SEPARACION 5

using namespace std;

VistaChat::VistaChat(Posicion posicion) {
	this->_posicion = posicion;
	this->_visible = false;
	this->_fuente = TTF_OpenFont("verdana.ttf", 10);
	this->_ventana = SDL_CreateRGBSurface(SDL_SWSURFACE, ANCHO_MENSAJE + (2 * SEPARACION), ((CANTIDAD_MAXIMA_MENSAJES + 1) * ALTO_MENSAJE) + (3 * SEPARACION), 32, 0, 0, 0, 0);
	this->_cajaTextoChat = SDL_CreateRGBSurface(SDL_SWSURFACE, ANCHO_MENSAJE, CANTIDAD_MAXIMA_MENSAJES * ALTO_MENSAJE, 32, 0, 0, 0, 0);
	this->_cajaTextoIngresado = SDL_CreateRGBSurface(SDL_SWSURFACE, ANCHO_MENSAJE, ALTO_MENSAJE, 32, 0, 0, 0, 0);
}

VistaChat::~VistaChat() {
	if (this->_fuente != NULL)
		TTF_CloseFont(this->_fuente);
	if (this->_ventana != NULL)
		SDL_FreeSurface(this->_ventana);
	if (this->_cajaTextoChat != NULL)
		SDL_FreeSurface(this->_cajaTextoChat);
	if (this->_cajaTextoIngresado != NULL)
		SDL_FreeSurface(this->_cajaTextoIngresado);
}

void VistaChat::agregarMensaje(std::string usuario, std::string mensaje) {
	if (this->_mensajes.size() == 10)
		this->_mensajes.pop_front();
	string cadena = usuario + ": " + mensaje;
	this->_mensajes.push_back(cadena.substr(0, CANTIDAD_MAXIMA_CARACTERES));
}

bool VistaChat::graficar(SDL_Surface* pantalla) {
	if (!this->_visible)
		return true;

	if ((this->_fuente == NULL) || (this->_ventana == NULL) || (this->_cajaTextoChat == NULL) || (this->_cajaTextoIngresado == NULL))
		return false;
	
	SDL_Rect posicionDestino;
	SDL_Color colorTexto = { 0, 0, 0 };
	SDL_Color colorFondo = { 255, 255, 255 };
	SDL_Surface* textoIngresado = TTF_RenderText_Shaded(this->_fuente, this->_textoIngresado.c_str(), colorTexto, colorFondo);
	int contadorMensajes = 0;
	
	posicionDestino.h = this->_ventana->h;
	posicionDestino.w = this->_ventana->w;
	posicionDestino.x = this->_posicion.x;
	posicionDestino.y = this->_posicion.y;

	SDL_FillRect(this->_ventana, NULL, SDL_MapRGB(this->_cajaTextoIngresado->format, 255, 0, 0));
	SDL_BlitSurface(this->_ventana, NULL, pantalla, &posicionDestino);

	posicionDestino.h = this->_cajaTextoChat->h;
	posicionDestino.w = this->_cajaTextoChat->w;
	posicionDestino.x = this->_posicion.x + SEPARACION;
	posicionDestino.y = this->_posicion.y + SEPARACION;

	SDL_FillRect(this->_cajaTextoChat, NULL, SDL_MapRGB(this->_cajaTextoIngresado->format, 255, 255, 255));
	SDL_BlitSurface(this->_cajaTextoChat, NULL, pantalla, &posicionDestino);

	for (list<string>::iterator mensaje = this->_mensajes.begin(); mensaje != this->_mensajes.end(); mensaje++) {
		SDL_Surface* textoMensaje = TTF_RenderText_Shaded(this->_fuente, (*mensaje).c_str(), colorTexto, colorFondo);
		if (textoMensaje != NULL) {
			posicionDestino.h = textoMensaje->h;
			posicionDestino.w = textoMensaje->w;
			posicionDestino.y = this->_posicion.y + SEPARACION + (contadorMensajes++ * 14);

			SDL_BlitSurface(textoMensaje, NULL, pantalla, &posicionDestino);
			SDL_FreeSurface(textoMensaje);
		}
	}

	posicionDestino.h = this->_cajaTextoIngresado->h;
	posicionDestino.w = this->_cajaTextoIngresado->w;
	posicionDestino.x = this->_posicion.x + SEPARACION;
	posicionDestino.y = this->_posicion.y + this->_cajaTextoChat->h + (2 * SEPARACION);

	SDL_FillRect(this->_cajaTextoIngresado, NULL, SDL_MapRGB(this->_cajaTextoIngresado->format, 255, 255, 255));
	SDL_BlitSurface(this->_cajaTextoIngresado, NULL, pantalla, &posicionDestino);

	if (textoIngresado == NULL)
		return true;

	posicionDestino.h = textoIngresado->h;
	posicionDestino.w = textoIngresado->w;

	SDL_BlitSurface(textoIngresado, NULL, pantalla, &posicionDestino);
	SDL_FreeSurface(textoIngresado);
	
	return true;
}

void VistaChat::teclaPresionada(Uint16 tecla) {
	// Si presiono enter agrego el mensaje a la lista
	if ((tecla == SDLK_RETURN) && (this->_textoIngresado.length() > 0)) {
		this->agregarMensaje("yo", this->_textoIngresado);
		this->_textoIngresado.clear();
		return;
	}
	
	// Si presiono backspace y el texto no esta vacio borro el ultimo caracter ingresado
	if ((tecla == SDLK_BACKSPACE) && (this->_textoIngresado.length() > 0)) {
		this->_textoIngresado.erase(this->_textoIngresado.length() - 1);
		return;
	}

	// Si alcanzo la cantidad maxima de caracteres salgo
	if (this->_textoIngresado.length() >= CANTIDAD_MAXIMA_CARACTERES)
		return;
	
	// Si presiono un caracter valido lo agrego a la cadena
	if ((tecla == (Uint16)' ') ||
		((tecla >= (Uint16)'0') && (tecla <= (Uint16)'9')) ||
		((tecla >= (Uint16)'A') && (tecla <= (Uint16)'Z')) ||
		((tecla >= (Uint16)'a') && (tecla <= (Uint16)'z')))
		this->_textoIngresado += (char)tecla;
}

bool VistaChat::visible() const {
	return this->_visible;
}

void VistaChat::visible(bool visible) {
	this->_visible = visible;
	this->_textoIngresado.clear();
}

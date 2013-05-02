#include "VistaChat.h"

//TODO: Ver de usar esta funcion para mejorar el tema de los tamaños
//TTF_SizeText

#define MARGEN 5
#define ALTO_LETRA 14
#define ANCHO_LETRA 11
#define CANTIDAD_MAXIMA_CARACTERES_DESTINATARIO 10
#define CANTIDAD_MAXIMA_CARACTERES_MENSAJE 55
#define CANTIDAD_MAXIMA_MENSAJES 10

#define ALTO_TEXTO_MENSAJES (ALTO_LETRA * CANTIDAD_MAXIMA_MENSAJES)
#define ANCHO_TEXTO_MENSAJES (ANCHO_LETRA * (CANTIDAD_MAXIMA_CARACTERES_DESTINATARIO + MARGEN + CANTIDAD_MAXIMA_CARACTERES_MENSAJE))

#define ALTO_TEXTO_INGRESADO (ALTO_LETRA)
#define ANCHO_TEXTO_INGRESADO (ANCHO_LETRA * CANTIDAD_MAXIMA_CARACTERES_MENSAJE)

#define ALTO_VENTANA (ALTO_TEXTO_MENSAJES + ALTO_TEXTO_INGRESADO + (3 * MARGEN))
#define ANCHO_VENTANA (ANCHO_TEXTO_MENSAJES + (2 * MARGEN))

using namespace std;

VistaChat::VistaChat(Posicion posicion, string remitente) {
	this->_posicion = posicion;
	this->_remitente = remitente;
	this->_visible = false;
	this->_fuente = TTF_OpenFont("verdana.ttf", 10);
	this->_ventana = SDL_CreateRGBSurface(SDL_SWSURFACE, ANCHO_VENTANA, ALTO_VENTANA, 32, 0, 0, 0, 0);
	this->_cajaTextoMensajes = SDL_CreateRGBSurface(SDL_SWSURFACE, ANCHO_TEXTO_MENSAJES, ALTO_TEXTO_MENSAJES, 32, 0, 0, 0, 0);
	this->_cajaTextoIngresado = SDL_CreateRGBSurface(SDL_SWSURFACE, ANCHO_TEXTO_INGRESADO, ALTO_TEXTO_INGRESADO, 32, 0, 0, 0, 0);
}

VistaChat::~VistaChat() {
	if (this->_fuente != NULL)
		TTF_CloseFont(this->_fuente);
	if (this->_ventana != NULL)
		SDL_FreeSurface(this->_ventana);
	if (this->_cajaTextoMensajes != NULL)
		SDL_FreeSurface(this->_cajaTextoMensajes);
	if (this->_cajaTextoIngresado != NULL)
		SDL_FreeSurface(this->_cajaTextoIngresado);
}

void VistaChat::agregarMensaje(string remitente, string mensaje) {
	if (this->_mensajes.size() == 10)
		this->_mensajes.pop_front();
	string cadena = remitente + ": " + mensaje;
	this->_mensajes.push_back(cadena.substr(0, CANTIDAD_MAXIMA_CARACTERES_MENSAJE));
}

void VistaChat::asignarDestinatario(std::string destinatario) {
	this->_destinatario = destinatario;
}

bool VistaChat::graficar(SDL_Surface* pantalla) {
	if (!this->_visible)
		return true;

	if ((this->_fuente == NULL) || (this->_ventana == NULL) || (this->_cajaTextoMensajes == NULL) || (this->_cajaTextoIngresado == NULL))
		return false;
	
	SDL_Rect posicionDestino;
	SDL_Color colorTexto = { 0, 0, 0 };
	SDL_Color colorFondo = { 255, 255, 255 };
	SDL_Surface* textoIngresado = TTF_RenderText_Shaded(this->_fuente, this->_textoIngresado.c_str(), colorTexto, colorFondo);
	SDL_Surface* textoDestinatario = TTF_RenderText_Blended(this->_fuente, (this->_destinatario.substr(0, CANTIDAD_MAXIMA_CARACTERES_DESTINATARIO) + ":").c_str(), colorTexto);
	int contadorMensajes = 0;
	
	// Muestra la ventana completa
	posicionDestino.h = this->_ventana->h;
	posicionDestino.w = this->_ventana->w;
	posicionDestino.x = this->_posicion.x;
	posicionDestino.y = this->_posicion.y;

	SDL_FillRect(this->_ventana, NULL, SDL_MapRGB(this->_cajaTextoIngresado->format, 255, 0, 0));
	SDL_BlitSurface(this->_ventana, NULL, pantalla, &posicionDestino);

	posicionDestino.h = this->_cajaTextoMensajes->h;
	posicionDestino.w = this->_cajaTextoMensajes->w;
	posicionDestino.x = this->_posicion.x + MARGEN;
	posicionDestino.y = this->_posicion.y + MARGEN;

	// Muestra los mensajes
	SDL_FillRect(this->_cajaTextoMensajes, NULL, SDL_MapRGB(this->_cajaTextoIngresado->format, 255, 255, 255));
	SDL_BlitSurface(this->_cajaTextoMensajes, NULL, pantalla, &posicionDestino);

	for (list<string>::iterator mensaje = this->_mensajes.begin(); mensaje != this->_mensajes.end(); mensaje++) {
		SDL_Surface* textoMensaje = TTF_RenderText_Shaded(this->_fuente, (*mensaje).c_str(), colorTexto, colorFondo);
		if (textoMensaje != NULL) {
			posicionDestino.h = textoMensaje->h;
			posicionDestino.w = textoMensaje->w;
			posicionDestino.y = this->_posicion.y + MARGEN + (contadorMensajes++ * 14);

			SDL_BlitSurface(textoMensaje, NULL, pantalla, &posicionDestino);
			SDL_FreeSurface(textoMensaje);
		}
	}

	// Muestro destinatario
	if (textoDestinatario != NULL) {
		posicionDestino.h = textoDestinatario->h;
		posicionDestino.w = textoDestinatario->w;
		posicionDestino.x = this->_posicion.x + MARGEN;
		posicionDestino.y = this->_posicion.y + this->_cajaTextoMensajes->h + (2 * MARGEN);
		SDL_BlitSurface(textoDestinatario, NULL, pantalla, &posicionDestino);
		SDL_FreeSurface(textoDestinatario);
	}
	
	// Muestro el mensaje ingresado
	posicionDestino.h = this->_cajaTextoIngresado->h;
	posicionDestino.w = this->_cajaTextoIngresado->w;
	posicionDestino.x = this->_posicion.x + this->_ventana->w - MARGEN - this->_cajaTextoIngresado->w;
	posicionDestino.y = this->_posicion.y + this->_cajaTextoMensajes->h + (2 * MARGEN);

	SDL_FillRect(this->_cajaTextoIngresado, NULL, SDL_MapRGB(this->_cajaTextoIngresado->format, 255, 255, 255));
	SDL_BlitSurface(this->_cajaTextoIngresado, NULL, pantalla, &posicionDestino);

	if (textoIngresado != NULL) {
		posicionDestino.h = textoIngresado->h;
		posicionDestino.w = textoIngresado->w;
		SDL_BlitSurface(textoIngresado, NULL, pantalla, &posicionDestino);
		SDL_FreeSurface(textoIngresado);
	}
	
	return true;
}

void VistaChat::teclaPresionada(Uint16 tecla) {
	// Si presiono enter agrego el mensaje a la lista
	if ((tecla == SDLK_RETURN) && (this->_textoIngresado.length() > 0)) {
		this->agregarMensaje(this->_remitente, this->_textoIngresado);
		this->_textoIngresado.clear();
		return;
	}
	
	// Si presiono backspace y el texto no esta vacio borro el ultimo caracter ingresado
	if ((tecla == SDLK_BACKSPACE) && (this->_textoIngresado.length() > 0)) {
		this->_textoIngresado.erase(this->_textoIngresado.length() - 1);
		return;
	}

	// Si alcanzo la cantidad maxima de caracteres salgo
	if (this->_textoIngresado.length() >= CANTIDAD_MAXIMA_CARACTERES_MENSAJE)
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

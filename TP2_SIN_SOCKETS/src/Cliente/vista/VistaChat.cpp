#include "VistaChat.h"

#define MARGEN 20
#define ALTO_TEXTO_MENSAJES 100
#define ANCHO_TEXTO_MENSAJES 190
#define ALTO_TEXTO_INGRESADO 14
#define ANCHO_TEXTO_INGRESADO 190
#define ALTO_VENTANA 184
#define ANCHO_VENTANA 237

using namespace std;

SDL_Surface* crearVentana() {
	SDL_Surface* ventana = SDL_CreateRGBSurface(SDL_SWSURFACE, ANCHO_VENTANA, ALTO_VENTANA, 32, 0, 0, 0, 0);
	SDL_Surface* cajaTextoMensajes = SDL_CreateRGBSurface(SDL_SWSURFACE, ANCHO_TEXTO_MENSAJES, ALTO_TEXTO_MENSAJES, 32, 0, 0, 0, 0);
	SDL_Surface* cajaTextoIngresado = SDL_CreateRGBSurface(SDL_SWSURFACE, ANCHO_TEXTO_INGRESADO, ALTO_TEXTO_INGRESADO, 32, 0, 0, 0, 0);
	SDL_Rect rectanguloDestino;

	SDL_FillRect(ventana, NULL, SDL_MapRGB(ventana->format, 255, 0, 0));
	
	rectanguloDestino.h = cajaTextoMensajes->h;
	rectanguloDestino.w = cajaTextoMensajes->w;
	rectanguloDestino.x = MARGEN;
	rectanguloDestino.y = MARGEN;

	SDL_FillRect(cajaTextoMensajes, NULL, SDL_MapRGB(ventana->format, 255, 255, 255));
	SDL_BlitSurface(cajaTextoMensajes, NULL, ventana, &rectanguloDestino);
	
	rectanguloDestino.h = cajaTextoIngresado->h;
	rectanguloDestino.w = cajaTextoIngresado->w;
	rectanguloDestino.x = MARGEN;
	rectanguloDestino.y = cajaTextoMensajes->h + (2 * MARGEN);

	SDL_FillRect(cajaTextoIngresado, NULL, SDL_MapRGB(ventana->format, 255, 255, 255));
	SDL_BlitSurface(cajaTextoIngresado, NULL, ventana, &rectanguloDestino);

	return ventana;
}

VistaChat::VistaChat(Posicion posicion, string remitente) {
	this->_posicion = posicion;
	this->_remitente = remitente;
	this->_visible = false;
	this->_fuente = TTF_OpenFont("verdana.ttf", 10);
	this->_ventana = IMG_Load("img/chat.png");
	this->_altoOcupadoTextoMensajes = 0;
}

VistaChat::~VistaChat() {
	if (this->_fuente != NULL)
		TTF_CloseFont(this->_fuente);
	if (this->_ventana != NULL)
		SDL_FreeSurface(this->_ventana);
}

void VistaChat::agregarMensaje(string remitente, string mensaje) {
	// Calculo el tamaño que tendria el texto mostrado en pantalla
	int ancho = 0, alto = 0;
	TTF_SizeText(this->_fuente, (remitente + ": " + mensaje).c_str(), &ancho, &alto);

	// Si alcanzo el alto del texto quito el primer mensaje
	if (this->_altoOcupadoTextoMensajes + alto >= ALTO_TEXTO_MENSAJES)
		this->_mensajes.pop_front();
	else
		this->_altoOcupadoTextoMensajes += alto;
	this->_mensajes.push_back(remitente + ": " + mensaje);
}

void VistaChat::asignarDestinatario(std::string destinatario) {
	this->_destinatario = destinatario;
}

bool VistaChat::graficar(SDL_Surface* pantalla) {
	if (!this->_visible)
		return true;

	if ((this->_fuente == NULL) || (this->_ventana == NULL))
		return false;
	
	SDL_Rect rectanguloOrigen, rectanguloDestino;
	SDL_Color colorTexto = { 0, 0, 0 };
	SDL_Surface* textoIngresado = TTF_RenderText_Blended(this->_fuente, (this->_destinatario + ": " + this->_textoIngresado).c_str(), colorTexto);
	int contadorMensajes = 0;
	
	// Muestra la ventana completa
	rectanguloDestino.h = this->_ventana->h;
	rectanguloDestino.w = this->_ventana->w;
	rectanguloDestino.x = this->_posicion.x;
	rectanguloDestino.y = this->_posicion.y;

	SDL_BlitSurface(this->_ventana, NULL, pantalla, &rectanguloDestino);

	// Muestra los mensajes
	for (list<string>::iterator mensaje = this->_mensajes.begin(); mensaje != this->_mensajes.end(); mensaje++) {
		SDL_Surface* textoMensaje = TTF_RenderText_Blended(this->_fuente, (*mensaje).c_str(), colorTexto);
		if (textoMensaje != NULL) {
			rectanguloOrigen.h = textoMensaje->h;
			rectanguloOrigen.w = ANCHO_TEXTO_MENSAJES;
			rectanguloOrigen.x = 0;
			rectanguloOrigen.y = 0;

			rectanguloDestino.h = textoMensaje->h;
			rectanguloDestino.w = textoMensaje->w;
			rectanguloDestino.x = this->_posicion.x + MARGEN + 5;
			rectanguloDestino.y = this->_posicion.y + MARGEN + (contadorMensajes++ * 14) + 5;

			SDL_BlitSurface(textoMensaje, &rectanguloOrigen, pantalla, &rectanguloDestino);
			SDL_FreeSurface(textoMensaje);
		}
	}

	// Muestro el mensaje ingresado
	if (textoIngresado != NULL) {
		rectanguloOrigen.h = textoIngresado->h;
		rectanguloOrigen.w = ANCHO_TEXTO_INGRESADO;
		rectanguloOrigen.x = 0;
		rectanguloOrigen.y = 0;

		rectanguloDestino.h = textoIngresado->h;
		rectanguloDestino.w = textoIngresado->w;
		rectanguloDestino.x = this->_posicion.x + MARGEN;
		rectanguloDestino.y = this->_posicion.y + (2 * MARGEN) + ALTO_TEXTO_MENSAJES + 8;

		SDL_BlitSurface(textoIngresado, &rectanguloOrigen, pantalla, &rectanguloDestino);
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

	// Calculo el tamaño que tendria el texto mostrado en pantalla
	int ancho = 0, alto = 0;
	TTF_SizeText(this->_fuente, (this->_destinatario + ": " + this->_textoIngresado + (char)tecla).c_str(), &ancho, &alto);

	// Si alcanzo el ancho del texto salgo
	if (ancho >= ANCHO_TEXTO_INGRESADO)
		return;
	
	// Si presiono un caracter valido lo agrego a la cadena
	if ((tecla >= 32) && (tecla <= 126))
		this->_textoIngresado += (char)tecla;
}

bool VistaChat::visible() const {
	return this->_visible;
}

void VistaChat::visible(bool visible) {
	this->_visible = visible;
	this->_textoIngresado.clear();
}

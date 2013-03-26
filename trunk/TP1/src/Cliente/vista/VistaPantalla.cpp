#include "VistaPantalla.h"


VistaPantalla::VistaPantalla(){}

void VistaPantalla::levantar() {
	// Estructura para la superficie gráfica, donde se va a dibujar
	SDL_Surface *temp;

	// Inicio SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Seteo el nombre en la barra
	SDL_WM_SetCaption("..::TP Taller papá!!!::..", "");

	// Creo la ventana
	this->pantalla = SDL_SetVideoMode(PANTALLA_ANCHO, PANTALLA_ALTO, 0, SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_ANYFORMAT);

	// Creo el fondo
	temp  = SDL_LoadBMP(SDL_RUTA_FONDO);
	this->fondo = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
}

void VistaPantalla::dibujar(std::vector<int> eventos){
	// Cargo el fondo
	SDL_Rect rcFondo;
	rcFondo.x = 0;
	rcFondo.y = 0;	
	SDL_BlitSurface(this->fondo, NULL, this->pantalla, &rcFondo);

	// Dibujo el Mouse
	SDL_Rect r;	
	r.x = eventos.at(0) - 32;
	r.y = eventos.at(1) - 24;
	r.w = 64;
	r.h = 48;	
	//SDL_FillRect(this->pantalla, &r, 0xff << (eventos.at(2) * 8));
	SDL_FillRect(this->pantalla, &r, 0xff << (eventos.at(3) * 8));

	// Dibujo una etiqueta
	font = TTF_OpenFont(DEFAULT_FONT, 36);
	std::string texto;
	texto.assign("hola");						
	SDL_Color textColor;
	textColor.b = 0xFB;
	textColor.g = 0xEF;
	textColor.r = 0xEF;
	textSurface = TTF_RenderText_Solid(font, texto.c_str(), textColor);
	SDL_Rect offset;
	offset.x = 100;
	offset.y = 100;
	SDL_BlitSurface(textSurface, NULL, pantalla, NULL);
	
	// actualiza la pantalla
	SDL_UpdateRect(pantalla, 0, 0, 0, 0);	
}

VistaPantalla::~VistaPantalla(){
	SDL_FreeSurface(pantalla);
	SDL_FreeSurface(fondo);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}


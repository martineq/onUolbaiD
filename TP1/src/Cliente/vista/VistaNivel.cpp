#include "./VistaNivel.h"


VistaNivel::VistaNivel(){

}

VistaNivel::~VistaNivel(){
	/*SDL_FreeSurface(pantalla);
	SDL_FreeSurface(fondo);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();	*/
}

Observador* VistaNivel::obtenerObservadorScroll(void){
	return (Observador*)this->scroll;
}

std::list<Observador*> VistaNivel::obtenerObservadoresEntidad(void){

	std::list<Observador*> listaObservadoresEntidad;

	// Agrego las demás entidades
	for (std::list<VistaEntidad*>::iterator it=this->listaEntidades.begin() ; it != this->listaEntidades.end(); it++ ){
		listaObservadoresEntidad.push_back( ((Observador*)*it) );
	}

	return listaObservadoresEntidad;

}

void VistaNivel::agregarJugador(double x, double y, double alto, double ancho){
	VistaEntidad* pJugador = NULL; // TODO: hacer el new() y llenar con los datos cuando reciban double
	this->listaEntidades.push_back(pJugador);
	return void();
}

void VistaNivel::agregarEntidad(double x, double y, double alto, double ancho){
	VistaEntidad* pEntidad = NULL; // TODO: hacer el new() y llenar con los datos cuando reciban double
	this->listaEntidades.push_back(pEntidad);
	return void();
}

void VistaNivel::agregarScroll(double x, double y, double alto, double ancho){
	VistaScroll* pScroll = NULL; // TODO: hacer el new() y llenar con los datos cuando reciban double
	this->scroll = pScroll;
	return void();
}







bool VistaNivel::levantarPantalla(){
	// Estructura para la superficie gráfica, donde se va a dibujar
	SDL_Surface *temp;

	// Inicio SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Seteo el nombre en la barra
	SDL_WM_SetCaption("..:: Diablo I ::..", "");

	// Creo la ventana
	this->pantalla = SDL_SetVideoMode(PANTALLA_ANCHO, PANTALLA_ALTO, 0, SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_ANYFORMAT);

	// Creo el fondo
	temp  = SDL_LoadBMP(SDL_RUTA_FONDO);
	this->fondo = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	this->font = TTF_OpenFont(DEFAULT_FONT, 36);

	return false; // TODO: Implementar el return del método
}

SDL_Surface* VistaNivel::getPantalla(){
	return this->pantalla;
}

SDL_Surface* VistaNivel::getFondo(){
	return this->fondo;
}

TTF_Font* VistaNivel::getFont(){
	return this->font;
}

SDL_Surface* VistaNivel::getTextSurface(){
	std::string texto;
	texto.assign("hola");						
	SDL_Color textColor;
	textColor.b = 0xFB;
	textColor.g = 0xEF;
	textColor.r = 0xEF;	
	this->textSurface = TTF_RenderText_Solid(font, texto.c_str(), textColor);
	SDL_Rect offset;
	offset.x = 100;
	offset.y = 100;
	return this->textSurface;
}
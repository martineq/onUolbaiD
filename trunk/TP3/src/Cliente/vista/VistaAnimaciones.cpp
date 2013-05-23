#include "VistaAnimaciones.h"

VistaAnimaciones::VistaAnimaciones() {
	this->animacionesAutomaticas = false;
}

/**
 * Devuelve una animacion en base a su nombre de animacion
 * */
VistaAnimacion* VistaAnimaciones::get(std::string nombreAnimacion) {
	VistaAnimacion * animacionEncontrada = NULL;
	map<std::string, VistaAnimacion* >::iterator it = this->animaciones.find(nombreAnimacion);
	if (it != this->animaciones.end()) {
		animacionEncontrada = (*it).second;
	}
	return animacionEncontrada;
}

void  VistaAnimaciones::agregar(std::string nombreAnimacion, list<std::string> sprites, int periodo, double ancho, double alto, int fps) {

	VistaAnimacion* animacion = NULL;
	animacion = VistaAnimacionRepository::getInstance().agregarAnimacion(nombreAnimacion,sprites,periodo,ancho,alto,fps,this->animacionesAutomaticas);
	this->animaciones.insert(std::make_pair(nombreAnimacion, animacion));
	this->vAnimaciones.push_back(animacion);
}


VistaAnimacion* VistaAnimaciones::get(unsigned int indice) {
	VistaAnimacion * animacionEncontrada = NULL;
	if (indice < this->vAnimaciones.size()) {
		animacionEncontrada = this->vAnimaciones.at(indice);
	}
	return animacionEncontrada;
}

int VistaAnimaciones::getTamanio(){ 
	return this->animaciones.size();
}

void VistaAnimaciones::setAnimacionesAutomaticas(){
	this->animacionesAutomaticas = true;
}

void VistaAnimaciones::setPantalla(SDL_Surface* screen){
	map<std::string, VistaAnimacion* >::iterator it;
	for (it=this->animaciones.begin();it!=this->animaciones.end();it++){
		VistaAnimacion* animacion = (*it).second;
		animacion->setPantalla(screen);
	}
}

VistaAnimaciones::~VistaAnimaciones() {
	map<std::string, VistaAnimacion* >::iterator it;
	for (it=this->animaciones.begin();it!=this->animaciones.end();it++) {
		//VistaAnimacion* animacion = (*it).second;  // ¿ Porqué ìncha cuando se hacen el delete? (Parece que alguien ya lo está borrando porque no salta como un memory leak)
		//delete animacion;
		(*it).second = NULL;
	}
}

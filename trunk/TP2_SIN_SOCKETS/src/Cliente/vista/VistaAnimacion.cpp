#include "VistaAnimacion.h"

VistaAnimacion::VistaAnimacion(list<string> & sprites, int periodo, double ancho, double alto, bool automatica, int fps) {
	list<string>::iterator it;
	this->ancho = ancho;
	this->alto = alto;
	this->indice = 0;
	this->indiceAnterior = 0;
	this->x = 0;
	this->y = 0;
	this->tiempoEspera = 0;
	this->automatica = automatica;
	for (it = sprites.begin(); it != sprites.end();it++){
		std::string ruta = *it;
		SDLutil* util = new SDLutil(0,0,ancho,alto,ruta);
		this->superficies.push_back(util);
	}
	this->periodo = periodo;
	this->intervaloActualizacion = 1000 / fps;
	this->tiempoEspera = 0;
	this->tiempoSprite = 0;
}


SDLutil* VistaAnimacion::get(int index){ 
	return this->superficies.at(index);
}

int VistaAnimacion::getTamanio(){
	return this->superficies.size(); 
}

int VistaAnimacion::getPeriodo(){ 
	return this->periodo; 
}


void VistaAnimacion::setPantalla(SDL_Surface* pantalla){	
	for (int i = 0;i<this->superficies.size();i++){
		superficies.at(i)->setPantalla(pantalla);
	}	
}

bool VistaAnimacion::graficar(int index,double x,double y){
	bool ok = false;
	this->x = x;
	this->y = y;
	if (this->superficies.size() > index){
		//ok = this->superficies.at(index)->graficar(x,y);
	}
	return ok;
}

bool VistaAnimacion::graficar(double x, double y, char visibilidad){
	bool ok = false;
	this->x = x;
	this->y = y;
	ok = this->superficies.at(indice)->graficar(x,y,visibilidad);
	this->incrementarIndice();
	return ok;
}

bool VistaAnimacion::graficar(){
	bool ok = false;
	ok = this->superficies.front()->graficar(this->x, this->y,2);
	return ok;
}

void VistaAnimacion::incrementarIndice(){
	this->indiceAnterior = this->indice;
	//Devuelve true si debe esperar el período
	double tiempoActual = SDL_GetTicks();
	if ( esperarTiempo() == false ){
		if (tiempoActual - this->tiempoSprite > this->intervaloActualizacion){
			this->tiempoSprite = tiempoActual;
			if (this->indice < this->superficies.size()-1){
				this->indice++;				
			}
			else{
				this->indice = 0;
				this->tiempoEspera = 0;
			}
		}
	}else{
		this->tiempoEspera = tiempoActual - this->tiempoSprite;
	}
	
}

bool VistaAnimacion::esperarTiempo(){
	if (!this->automatica){
		return false;
	}
	
	if (this->tiempoEspera >= this->periodo){		
		return false;
	}
	return true;	
}

VistaAnimacion::~VistaAnimacion() {
	while (!this->superficies.empty()){
		SDLutil* pUtil = this->superficies.back();
		delete pUtil;
		this->superficies.pop_back();
	}
}

void VistaAnimacion::setX(double x) {
	this->x = x;
}

void VistaAnimacion::setY(double y)  {
	this->y = y;
}

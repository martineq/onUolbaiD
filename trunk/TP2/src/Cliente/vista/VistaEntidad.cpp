#include "VistaEntidad.h"

VistaEntidad::VistaEntidad(double x,double y,double alto,double ancho,double posicionReferenciaX,double posicionReferenciaY,double fps,double delay,std::list<std::list<std::string>> listaAnimaciones,bool esJugador,int altoNivel,int anchoNivel,int id){
	this->_id = id;

	int xAux, yAux;

	Posicion::convertirTileAPixel(altoNivel, x, y, xAux, yAux);
	
	this->posicionReferenciaX = posicionReferenciaX;
	this->posicionReferenciaY = posicionReferenciaY;
	this->x = xAux;
	this->y = yAux;

	if (esJugador) {
		if ((alto != 1) || (ancho != 1))
			Log::getInstance().log(1,__FILE__,__LINE__,"El jugador no puede ocupar mas de un tile. Se setea tamanio apropiado por defecto.");
		alto = 1;
		ancho = 1;	
	}

	this->alto = alto * ALTO_TILE; 
	this->ancho = ancho * ANCHO_TILE;

	this->fps = fps;
	this->delay = delay;
	this->esJugador = esJugador;
	this->animaciones = new VistaAnimaciones();
	std::list<std::list<std::string>>::iterator it = listaAnimaciones.begin();
	this->animacionActual = NULL;
	this->estados.push_back(ACCION_NORTE);
	this->estados.push_back(ACCION_NORESTE);
	this->estados.push_back(ACCION_ESTE);
	this->estados.push_back(ACCION_SUDESTE);
	this->estados.push_back(ACCION_SUR);
	this->estados.push_back(ACCION_SUDOESTE);
	this->estados.push_back(ACCION_OESTE);	
	this->estados.push_back(ACCION_NOROESTE);
	int i = 0;
	if (this->esJugador == false){
		this->animaciones->setAnimacionesAutomaticas();	
	}
	for (it=listaAnimaciones.begin();it!=listaAnimaciones.end();it++){
		this->animaciones->agregar(this->estados.at(i),*it,delay*1000,this->ancho,this->alto,fps);
		if (this->animacionActual == NULL){
			this->animacionActual = this->animaciones->get(this->estados.at(i));
		}
		i++;
	}
	if (this->esJugador)
		this->animacionActual = this->animaciones->get(this->estados.at(4));
	this->esNecesarioRefrescar = false;
	this->codigoAnimacion = 0;
	this->entraEnPantalla = false;
	//typedef enum Direccion { NORTE, SUR, ESTE, OESTE, NORESTE, NOROESTE, SUDESTE, SUDOESTE, CENTRO };
}

VistaEntidad::~VistaEntidad(void){
	if (this->animaciones != NULL) delete this->animaciones;
	this->animaciones = NULL;
}

void VistaEntidad::setXEnPantalla(double scrollX){
	this->xEnPantalla = this->x - scrollX;	
}

void VistaEntidad::setYEnPantalla(double scrollY){
	this->yEnPantalla = this->y - scrollY;
}

// Este método será usado ahora por el ProxyModeloEntidad
void VistaEntidad::actualizar(ProxyModeloEntidad::stEntidad& entidad){

	this->x = entidad.pixelSiguienteX;
	this->y = entidad.pixelSiguienteY;

	int codigo = entidad.direccion;
	if( (this->esJugador) && (codigo != this->codigoAnimacion)){
		this->codigoAnimacion = codigo;
		this->animacionActual = this->animaciones->get(this->estados.at(codigo));
	}
	
	this->esNecesarioRefrescar = !(entidad.esUltimoMovimiento);
}

void VistaEntidad::verificarBordePantalla(VistaScroll* scroll) {
	int xReal = this->x - this->posicionReferenciaX;
	int yReal = this->y  - this->posicionReferenciaY;
	bool entraEnX = false;
	bool entraEnY = false;
	
	if ((xReal > scroll->getX()) && (xReal < (scroll->getX() + scroll->getAncho())) ||
		(((xReal + this->ancho) > scroll->getX()) && (xReal + this->ancho) < (scroll->getX() + scroll->getAncho()))) {
		entraEnX = true;
	}
	
	this->entraEnPantalla = false;
	if (((yReal > scroll->getY()) && (yReal < (scroll->getY() + scroll->getAlto())) ||
		(((yReal + this->alto) > scroll->getY()) && ((yReal + this->alto) < (scroll->getY() + scroll->getAlto()))))) {
		entraEnY = true;
	}

	this->entraEnPantalla = false;
	if (entraEnX && entraEnY) {
		this->entraEnPantalla = true;
		this->setXEnPantalla(scroll->getX());
		this->setYEnPantalla(scroll->getY());
	}
}

int VistaEntidad::id() const {
    return this->_id;
}

bool VistaEntidad::getEsJugador(void){
	return (this->esJugador);
}

double VistaEntidad::getX(void){
	return (this->x);
}

double VistaEntidad::getY(void){
	return (this->y);
}

double VistaEntidad::getAlto(void){
	return (this->alto);
}

double VistaEntidad::getAncho(void){
	return (this->ancho);
}

double VistaEntidad::getPosRefX(void){
	return (this->posicionReferenciaX);
}

double VistaEntidad::getPosRefY(void){
	return (this->posicionReferenciaY);
}

double VistaEntidad::getFps(void){
	return (this->fps);
}

double VistaEntidad::getDelay(void){
	return (this->delay);
}

int VistaEntidad::getCodigoAnimacion(void){
	return this->codigoAnimacion;
}

std::list<std::list<std::string>> VistaEntidad::getListaAnimaciones(void){
	return (this->listaAnimaciones);
}

bool VistaEntidad::getEsNecesarioRefrescar(void){
	return this->esNecesarioRefrescar;
}

void VistaEntidad::setEsNecesarioRefrescar(bool boolRefrescar){
	this->esNecesarioRefrescar = boolRefrescar;
}

void VistaEntidad::setAnimacion(std::string estado){
	this->animacionActual = this->animaciones->get(estado);
}

bool VistaEntidad::graficar(){
	bool ok = true;	
	if (this->entraEnPantalla)  {
		if ((this->esNecesarioRefrescar) || (this->esJugador == false)){
			if( this->animacionActual->graficar(this->xEnPantalla - this->posicionReferenciaX,this->yEnPantalla - this->posicionReferenciaY) == false ) ok = false;
			//this->esNecesarioRefrescar = false;
		}else{			
			this->animacionActual->setX(this->xEnPantalla - this->posicionReferenciaX);
			this->animacionActual->setY(this->yEnPantalla - this->posicionReferenciaY);
			if( this->animacionActual->graficar() == false ) ok = false;
		}
	}
	return ok;
}

void VistaEntidad::setPantalla(SDL_Surface* fondo){
	this->animaciones->setPantalla(fondo);
}


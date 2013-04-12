#include "VistaEntidad.h"

long VistaEntidad::contador = 0; // Para el ID

/*VistaEntidad::VistaEntidad(double x,double y,double alto,double ancho,double posicionReferenciaX,double posicionReferenciaY,double fps,double delay,std::list<std::list<std::string>> listaAnimaciones,bool esJugador){
	this->id = (int)InterlockedIncrement(&(this->contador));  // Genera un ID
	this->x = x;
	this->y = y;
	this->alto = alto;
	this->ancho = ancho;
	this->posicionReferenciaX = posicionReferenciaX;
	this->posicionReferenciaY = posicionReferenciaY;
	this->fps = fps;
	this->delay = delay;
	this->esJugador = esJugador;
	this->listaAnimaciones = listaAnimaciones;
	this->esNecesarioRefrescar = true;
	this->codigoAnimacion = 0;

	area.x = ancho	* 0;
	area.y = alto	* 0;
	area.w = ancho;
	area.h = alto;

	this->figuraActual = &this->area;
}
*/
VistaEntidad::VistaEntidad(double x,double y,double alto,double ancho,double posicionReferenciaX,double posicionReferenciaY,double fps,double delay,std::list<std::list<std::string>> listaAnimaciones,bool esJugador){
	this->_id = (int)InterlockedIncrement(&(this->contador));  // Genera un ID
	this->x = x;
	this->y = y;
	this->alto = alto;
	this->ancho = ancho;
	this->posicionReferenciaX = posicionReferenciaX;
	this->posicionReferenciaY = posicionReferenciaY;
	this->fps = fps;
	this->delay = delay;
	this->esJugador = esJugador;
	this->animaciones = new VistaAnimaciones();
	std::list<std::list<std::string>>::iterator it = listaAnimaciones.begin();
	this->animacionActual = NULL;
	for (it=listaAnimaciones.begin();it!=listaAnimaciones.end();it++){
		this->animaciones->agregar(it->front(),*it,delay,ancho,alto,fps);
		if (this->animacionActual == NULL){
			this->animacionActual = this->animaciones->get(it->front());
		}
	}
	this->esNecesarioRefrescar = true;
	this->codigoAnimacion = 0;
}



VistaEntidad::~VistaEntidad(void){

}

void VistaEntidad::actualizar(class Observable* s){

	// En este punto ya se que el parámetro <s> se puede castear a ((ModeloEntidad*)s)
	
    // TODO: Completar con los métodos brindados por ModeloEntidad
	this->x = ((ModeloEntidad*)s)->pixelSiguiente().x;
	this->x = ((ModeloEntidad*)s)->pixelSiguiente().y;
//	this->x = ((ModeloEntidad*)s)->getX();
//	this->y = ((ModeloEntidad*)s)->getY();
//	this->codigoAnimacion = ((ModeloEntidad*)s)->getCodigoAnimacion();
	int codigo = ((ModeloEntidad*)s)->direccion();
	if ((this->esJugador) && (codigo != this->codigoAnimacion)){
		this->codigoAnimacion = codigo;
		switch (codigo){
			case NORTE:
				this->animacionActual = this->animaciones->get("NORTE");
				break;
			case SUR:
				this->animacionActual = this->animaciones->get("SUR");
				break;
			case ESTE:
				this->animacionActual = this->animaciones->get("ESTE");
				break;
			case OESTE:
				this->animacionActual = this->animaciones->get("OESTE");
				break;
			case NORESTE:
				this->animacionActual = this->animaciones->get("NORESTE");
				break;
			case NOROESTE:
				this->animacionActual = this->animaciones->get("NOROESTE");
				break;
			case SUDESTE:
				this->animacionActual = this->animaciones->get("SUDESTE");
				break;
			case SUDOESTE:
				this->animacionActual = this->animaciones->get("SUDOESTE");
				break;
		}
	}
	this->esNecesarioRefrescar = true;

}

int VistaEntidad::id() const {
    return this->_id;
}


bool VistaEntidad::getEsJugador(void){
	return (this->esJugador);
}

/*int VistaEntidad::getId(void){	// Para el ID
    return (this->id);
}*/

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

void VistaEntidad::graficar(){
	if (this->esNecesarioRefrescar){
		this->animacionActual->graficar(this->x,this->y);
	}else{
		this->animacionActual->graficar();
	}
}

void VistaEntidad::setPantalla(SDL_Surface* screen){
	this->animaciones->setPantalla(screen);
}
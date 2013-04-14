#include "VistaEntidad.h"

long VistaEntidad::contador = 0; // Para el ID

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
	this->estados.push_back(ACCION_NORTE);
	this->estados.push_back(ACCION_NORESTE);
	this->estados.push_back(ACCION_ESTE);
	this->estados.push_back(ACCION_SUDESTE);
	this->estados.push_back(ACCION_SUR);
	this->estados.push_back(ACCION_SUDOESTE);
	this->estados.push_back(ACCION_OESTE);	
	this->estados.push_back(ACCION_NOROESTE);
	int i = 0;
	for (it=listaAnimaciones.begin();it!=listaAnimaciones.end();it++){
		this->animaciones->agregar(this->estados.at(i),*it,delay,ancho,alto,fps);
		if (this->animacionActual == NULL){
			this->animacionActual = this->animaciones->get(this->estados.at(i));
		}
		i++;
	}
	if (this->esJugador == false){
		this->animaciones->setAnimacionesAutomaticas();
	}
	this->esNecesarioRefrescar = true;
	this->codigoAnimacion = 0;
	//typedef enum Direccion { NORTE, SUR, ESTE, OESTE, NORESTE, NOROESTE, SUDESTE, SUDOESTE, CENTRO };
}



VistaEntidad::~VistaEntidad(void){

}

/*void VistaEntidad::setXEnPantalla(double scrollX){
	this->xEnPantalla = this->x - scrollX;	
}*/

/*void VistaEntidad::setYEnPantalla(double scrollY){
	this->yEnPantalla = this->y - scrollY;
}*/

void VistaEntidad::actualizar(class Observable* s){
	// En este punto ya se que el parámetro <s> se puede castear a ((ModeloEntidad*)s)
	this->x = ((ModeloEntidad*)s)->pixelSiguiente().x - (this->ancho / 2);
	this->y = ((ModeloEntidad*)s)->pixelSiguiente().y - (this->alto / 2);

	int codigo = ((ModeloEntidad*)s)->direccion();
	if ((this->esJugador) && (codigo != this->codigoAnimacion)){
		this->animacionActual->limpiar();
		this->codigoAnimacion = codigo;
		this->animacionActual = this->animaciones->get(this->estados.at(codigo));
	}
	this->esNecesarioRefrescar = true;

}

void VistaEntidad::verificarBordePantalla(VistaScroll* scroll){
       bool entraEnX = false;
       bool entraEnY = false;
       

       if ((this->x > scroll->getX()) && (this->x < (scroll->getX()+scroll->getAncho()))
               || ( ( (this->x + this->ancho) > scroll->getX()) && 
                        ((this->x + this->ancho) <  scroll->getX()+scroll->getAncho()))) {
                       entraEnX = true;
       }

       if ( ((this->y > scroll->getY()) && (this->y < (scroll->getY()+scroll->getAlto()))
               || ( ( (this->y + this->alto) > scroll->getY()) && 
                        ((this->y + this->alto) <  scroll->getY()+scroll->getAlto())))) {
                       entraEnY = true;
       }
       if (entraEnX && entraEnY){
               this->entraEnPantalla = true;
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
	if ((this->esNecesarioRefrescar) || (this->esJugador == false)){
		if( this->animacionActual->graficar(this->x,this->y) == false ) ok = false;
		this->esNecesarioRefrescar = false;
	}else{
		if( this->animacionActual->graficar() == false ) ok = false;
	}
	return ok;
}

void VistaEntidad::setPantalla(SDL_Surface* fondo){
	this->animaciones->setPantalla(fondo);
}

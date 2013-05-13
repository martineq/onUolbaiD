#include "VistaEntidad.h"

VistaEntidad::VistaEntidad(double x,double y,double alto,double ancho,double posicionReferenciaX,double posicionReferenciaY,double fps,double delay,std::list<std::list<std::string>> listaAnimaciones,bool esJugador,int altoNivel,int anchoNivel,int id, std::string nombreEntidad,bool estaCongelado,int estado){
	this->_id = id;
	this->estaCongelado = estaCongelado;

	int xAux, yAux;

	Posicion::convertirTileAPixel(altoNivel, x, y, xAux, yAux);

	this->posicionReferenciaX = posicionReferenciaX;
	this->posicionReferenciaY = posicionReferenciaY;
	this->x = xAux;
	this->y = yAux;
	this->estaCongelado = false;
	//this->x = x;
	//this->y = y;


	this->animaciones = new VistaAnimaciones();

	if (esJugador) {
		if ((alto != 1) || (ancho != 1))
			Log::getInstance().log(1,__FILE__,__LINE__,"El jugador no puede ocupar mas de un tile. Se setea tamanio apropiado por defecto.");
		alto = 1;
		ancho = 1;	

		this->estados.push_back(nombreEntidad+ACCION_CAMINAR+ACCION_NOROESTE);
		this->estados.push_back(nombreEntidad+ACCION_CAMINAR+ACCION_NORTE);
		this->estados.push_back(nombreEntidad+ACCION_CAMINAR+ACCION_NORESTE);
		this->estados.push_back(nombreEntidad+ACCION_CAMINAR+ACCION_ESTE);
		this->estados.push_back(nombreEntidad+ACCION_CAMINAR+ACCION_SUDESTE);
		this->estados.push_back(nombreEntidad+ACCION_CAMINAR+ACCION_SUR);
		this->estados.push_back(nombreEntidad+ACCION_CAMINAR+ACCION_SUDOESTE);
		this->estados.push_back(nombreEntidad+ACCION_CAMINAR+ACCION_OESTE);			

		this->estados.push_back(nombreEntidad+ACCION_ATACAR+ACCION_NOROESTE);
		this->estados.push_back(nombreEntidad+ACCION_ATACAR+ACCION_NORTE);
		this->estados.push_back(nombreEntidad+ACCION_ATACAR+ACCION_NORESTE);
		this->estados.push_back(nombreEntidad+ACCION_ATACAR+ACCION_ESTE);
		this->estados.push_back(nombreEntidad+ACCION_ATACAR+ACCION_SUDESTE);
		this->estados.push_back(nombreEntidad+ACCION_ATACAR+ACCION_SUR);
		this->estados.push_back(nombreEntidad+ACCION_ATACAR+ACCION_SUDOESTE);
		this->estados.push_back(nombreEntidad+ACCION_ATACAR+ACCION_OESTE);			

		this->estados.push_back(nombreEntidad+ACCION_DEFENDER+ACCION_NOROESTE);
		this->estados.push_back(nombreEntidad+ACCION_DEFENDER+ACCION_NORTE);
		this->estados.push_back(nombreEntidad+ACCION_DEFENDER+ACCION_NORESTE);
		this->estados.push_back(nombreEntidad+ACCION_DEFENDER+ACCION_ESTE);
		this->estados.push_back(nombreEntidad+ACCION_DEFENDER+ACCION_SUDESTE);
		this->estados.push_back(nombreEntidad+ACCION_DEFENDER+ACCION_SUR);
		this->estados.push_back(nombreEntidad+ACCION_DEFENDER+ACCION_SUDOESTE);
		this->estados.push_back(nombreEntidad+ACCION_DEFENDER+ACCION_OESTE);
	}else{
		this->animaciones->setAnimacionesAutomaticas();	
		this->estados.push_back(nombreEntidad);
	}

	this->alto = alto * ALTO_TILE; 
	this->ancho = ancho * ANCHO_TILE;

	this->fps = fps;
	this->delay = delay;
	this->esJugador = esJugador;	
	std::list<std::list<std::string>>::iterator it = listaAnimaciones.begin();
	this->animacionActual = NULL;

	int i = 0;
	for (it=listaAnimaciones.begin();it!=listaAnimaciones.end();it++){
		this->animaciones->agregar(this->estados.at(i),*it,delay*1000,this->ancho,this->alto,fps);
		if (this->animacionActual == NULL){
			this->animacionActual = this->animaciones->get(this->estados.at(i));
		}
		i++;
	}
	if (this->esJugador)
		this->animacionActual = this->animaciones->get(this->estados.at(estado));
	this->esNecesarioRefrescar = false;
	this->codigoAnimacion = 0;
	this->tileX = x;
	this->tileY = y;
	this->tileXAnterior = x;
	this->tileYAnterior = y;
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

void VistaEntidad::setPosicionAnteriorEnTiles(){
	this->tileXAnterior = this->tileX;
	this->tileYAnterior = this->tileY;
}

// Este método será usado ahora por el ProxyModeloEntidad
void VistaEntidad::actualizar(ProxyModeloEntidad::stEntidad& entidad){

	// TODO: Agregar todas las actualizaciondes de los nuevos atributos (Hay que asignarlos):
	//entidad.actualizacionMapa;
	//entidad.entidadCongelada;
	//entidad.errorEnSocket;
	this->setPosicionAnteriorEnTiles();
	this->x = entidad.pixelSiguienteX;
	this->y = entidad.pixelSiguienteY;
	this->tileX = entidad.posicionSiguienteX;
	this->tileY = entidad.posicionSiguienteY;
	this->estaCongelado = entidad.entidadCongelada;
	this->nombreEntidad = entidad.nombreEntidad;

	int accion = entidad.accion;
	if (accion == 3)
		accion = 0;

	int codigo = (accion*8) + entidad.direccion;
	if( (this->esJugador) && (codigo != this->codigoAnimacion)){
		this->codigoAnimacion = codigo;
		this->animacionActual = this->animaciones->get(this->estados.at(codigo));
	}
	
	this->esNecesarioRefrescar = ( !(entidad.esUltimoMovimiento) || (codigo >= 8) );
}

bool VistaEntidad::verificarBordePantalla(VistaScroll* scroll) {
	int xReal = this->x - this->posicionReferenciaX;
	int yReal = this->y  - this->posicionReferenciaY;
	bool entraEnX = false;
	bool entraEnY = false;
	
	if ((xReal > scroll->getX()) && (xReal < (scroll->getX() + scroll->getAncho())) ||
		(((xReal + this->ancho) > scroll->getX()) && (xReal + this->ancho) < (scroll->getX() + scroll->getAncho()))) {
		entraEnX = true;
	}
	
	if (((yReal > scroll->getY()) && (yReal < (scroll->getY() + scroll->getAlto())) ||
		(((yReal + this->alto) > scroll->getY()) && ((yReal + this->alto) < (scroll->getY() + scroll->getAlto()))))) {
		entraEnY = true;
	}

	if (entraEnX && entraEnY) {
		this->setXEnPantalla(scroll->getX());
		this->setYEnPantalla(scroll->getY());
		return true;
	}
	return false;
}

int VistaEntidad::id() {
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

int VistaEntidad::getTileX(){
	return (this->tileX);
}

int VistaEntidad::getTileY(){
	return (this->tileY);
}

int VistaEntidad::getTileXAnterior(){
	return (this->tileXAnterior);
}

int VistaEntidad::getTileYAnterior(){
	return (this->tileYAnterior);
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

std::string VistaEntidad::getNombreEntidad() {
	return this->nombreEntidad;
}

void VistaEntidad::setEsNecesarioRefrescar(bool boolRefrescar){
	this->esNecesarioRefrescar = boolRefrescar;
}

void VistaEntidad::setAnimacion(std::string estado){
	this->animacionActual = this->animaciones->get(estado);
}

bool VistaEntidad::graficar(char visibilidad){
	if (this->estaCongelado && (visibilidad != NO_CONOCIDO))
		visibilidad = CONGELADO;
	bool ok = true;
	if ((this->esNecesarioRefrescar) || (this->esJugador == false)){
		if( this->animacionActual->graficar(this->xEnPantalla - this->posicionReferenciaX,this->yEnPantalla - this->posicionReferenciaY, visibilidad) == false ) ok = false;
		if (this->animacionActual->animacionFinalizada()) this->esNecesarioRefrescar = false;
	}
	else {
		this->animacionActual->setX(this->xEnPantalla - this->posicionReferenciaX);
		this->animacionActual->setY(this->yEnPantalla - this->posicionReferenciaY);
		if( this->animacionActual->graficar(visibilidad) == false ) ok = false;
	}
	return ok;
}

void VistaEntidad::setPantalla(SDL_Surface* fondo){
	this->animaciones->setPantalla(fondo);
}

void VistaEntidad::setEstaCongelado(bool estado){
	this->estaCongelado = estado;
}

bool VistaEntidad::getEstaCongelado(){
	return this->estaCongelado;
}
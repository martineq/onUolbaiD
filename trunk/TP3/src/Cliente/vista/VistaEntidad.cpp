#include "VistaEntidad.h"

VistaEntidad::VistaEntidad(double x,double y,double alto,double ancho,double posicionReferenciaX,double posicionReferenciaY,int rangoVisible,double fps,double delay,list<list<string>> listaAnimaciones,bool esJugador,int altoNivel,int anchoNivel,int id,string nombreEntidad,bool estaCongelado,int estado,string nombreJugador,int vida, int tipoEntidad, int magia, int escudo, bool tieneGolem, bool tieneHechizo, int bombas){
	this->_id = id;
	this->_tipoEntidad = tipoEntidad;
	this->estaCongelado = estaCongelado;
	this->maximoVida = vida;
	this->maximoMagia = magia;
	this->magia = magia;
	this->vida = vida;
	this->escudo = escudo;
	
	this->tieneGolem = tieneGolem;
	this->tieneHechizoHielo = tieneHechizo;
	this->tieneMapa = false;

	int xAux, yAux;

	Posicion::convertirTileAPixel(altoNivel, x, y, xAux, yAux);

	this->posicionReferenciaX = posicionReferenciaX;
	this->posicionReferenciaY = posicionReferenciaY;
	this->rangoVision = rangoVisible;
	this->x = xAux;
	this->y = yAux;	
	this->nombreEntidad = nombreEntidad;
	this->nombreJugador = nombreJugador;
	this->nombreDelJugadorGanador = "1";

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

	if (tipoEntidad == TIPO_ITEM_BOMBA){
		this->animaciones->setAnimacionesAutomaticas();
	}

	this->alto = alto * ALTO_TILE; 
	this->ancho = ancho * ANCHO_TILE;

	this->fps = fps;
	this->delay = delay;
	this->esJugador = esJugador;	
	this->_esMiJugador = false;
	this->sufrioDanio = false;
	this->gastoEscudo = false;
	this->gastoMagia = false;
	this->yaMurio = false;
	this->terminoJuego = false;
	this->cantidadBombas = bombas;
	std::list<std::list<std::string>>::iterator it = listaAnimaciones.begin();
	this->animacionActual = NULL;
	this->sonidoExtra = true;

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
	this->codigoAnimacion = estado;
	this->tileX = x;
	this->tileY = y;
	this->tileXAnterior = x;
	this->tileYAnterior = y;
}

VistaEntidad::~VistaEntidad(void){
	if (this->animaciones != NULL) delete this->animaciones;
	this->animaciones = NULL;
	this->estados.clear();
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

	// Con estas nuevas variables se chequea si disminuyó la energia. 
	this->sufrioDanio = ( this->vida > entidad.vida );
	this->gastoEscudo = ( this->escudo > entidad.escudo );
	this->gastoMagia = ( this->magia > entidad.magia );
	this->gastoBomba = ( this->cantidadBombas > entidad.cantidadBombas );
	bool murio = (entidad.vida == 0);	
	if( (this->vida == 0) && (entidad.vida>0) ) this->yaMurio = false;  // Si revivó reseteo esta variable
	this->actualizarEventosSonido(entidad.nombreEntidad, sufrioDanio, murio, entidad.atacando);

	// Actualizo los datos
	this->setPosicionAnteriorEnTiles();
	this->x = entidad.pixelX;
	this->y = entidad.pixelY;
	this->rangoVision = entidad.rangoVision;
	this->tieneMapa = entidad.tieneMapa;
	this->tileX = entidad.posicionX;
	this->tileY = entidad.posicionY;
	this->estaCongelado = entidad.estaCongelado;
	this->nombreEntidad = entidad.nombreEntidad;
	this->nombreDelJugadorGanador = entidad.nombreDelJugadorGanador;
	this->nombreJugador = entidad.nombreJugador;
	this->vida = entidad.vida;		
	this->magia = entidad.magia;
	this->escudo = entidad.escudo;	
	this->tieneHechizoHielo = entidad.tieneHechizoHielo;
	this->tieneGolem = entidad.tieneGolem;
	this->cantidadBombas = entidad.cantidadBombas;
	this->esPrimerMovimiento = entidad.esPrimerMovimiento;
	this->terminoJuego = entidad.terminoJuego;

	int codigo = entidad.accion;
	if( (this->esJugador) && (codigo != this->codigoAnimacion)){
		this->codigoAnimacion = codigo;
		this->animacionActual = this->animaciones->get(this->estados.at(codigo));		
	}

	this->esNecesarioRefrescar = ( !(entidad.esUltimoMovimiento) || (codigo >= 8) || (entidad.tipoEntidad == TIPO_ITEM_BOMBA));	
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

int VistaEntidad::getRangoVision() {
	return this->rangoVision;
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

std::string VistaEntidad::getNombreJugador() {
	return this->nombreJugador;
}

void VistaEntidad::setEsNecesarioRefrescar(bool boolRefrescar){
	this->esNecesarioRefrescar = boolRefrescar;
}

void VistaEntidad::setAnimacion(std::string estado){
	this->animacionActual = this->animaciones->get(estado);
}

bool VistaEntidad::graficar(char visibilidad){
	if( this->getEstaVivo() == false ){
		return true;	// Si está muerto no dibujo nada
	}
	if (this->estaCongelado && (visibilidad != NO_CONOCIDO))
		visibilidad = CONGELADO;
	bool ok = true;
	if ((this->esNecesarioRefrescar) || (this->esJugador == false) || ( this->tipoEntidad() == TIPO_ITEM_BOMBA)){
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

bool VistaEntidad::getEstaVivo(){
	return (this->vida > 0);
}

bool VistaEntidad::getEstaCongelado(){
	return this->estaCongelado;
}

bool VistaEntidad::getTieneMapa(){
	return this->tieneMapa;
}

bool VistaEntidad::getSufrioDanio(){
	return this->sufrioDanio;
}

bool VistaEntidad::getEsUltimoMovimiento(){
	return this->esUltimoMovimiento;
}

bool VistaEntidad::getEsPrimerMovimiento(){
	return this->esPrimerMovimiento;
	SDL_Delay(100);
}

void VistaEntidad::esMiJugador(bool valor){
	this->_esMiJugador = valor;
	return void();
}

void VistaEntidad::actualizarEventosSonido(std::string entidad, bool sufrioDanio, bool murio, bool ataco){

	// True solo si es el el jugador de este cliente
	bool esMiJugador = this->esMiJugador();

	// True solo si es otro jugador que no sea el mio, incluye los automáticos, los golems y el carnicero
	bool esOtroJugador = ( (this->_tipoEntidad == TIPO_ENTIDAD_JUGADOR  && !esMiJugador ) || (this->_tipoEntidad == TIPO_ENTIDAD_AUTOMATICO)  || (this->_tipoEntidad == TIPO_ENTIDAD_GOLEM) || (this->_tipoEntidad == TIPO_ENTIDAD_CARNICERO) );
								
	// True solo si es un item.
	bool esItem = (this->_tipoEntidad == TIPO_ITEM_BOTELLA) || (this->_tipoEntidad == TIPO_ITEM_CORAZON) ||
		(this->_tipoEntidad == TIPO_ITEM_ESCUDO) || (this->_tipoEntidad == TIPO_ITEM_LAMPARA) ||
		(this->_tipoEntidad == TIPO_ITEM_MAPA) || (this->_tipoEntidad == TIPO_ITEM_ZAPATO) ||
		(this->_tipoEntidad == TIPO_ITEM_ESPADA) || (this->_tipoEntidad == TIPO_ITEM_HECHIZO_HIELO) ||
		(this->_tipoEntidad == TIPO_ITEM_BOMBA) || (this->_tipoEntidad == TIPO_ITEM_GOLEM);

	// Se murio mi jugador
	if( esMiJugador == true && murio == true ) {
		VistaMusica::getInstance().murioJugador(this->nombreEntidad);
	}

	// Se murio un enemigo
	if( esOtroJugador == true && murio == true && !esItem && !this->yaMurio) {
		this->yaMurio = true;
		VistaMusica::getInstance().murioEnemigo(this->nombreEntidad);
	}

	// Se tomo item
	if ( esItem == true && murio == true && !this->yaMurio && ataco == false ) { 
		this->yaMurio = true;
		VistaMusica::getInstance().itemTomado(this->nombreEntidad);
	} 	

	// Si la entidad ataca.
	if ( ataco == true ){
		VistaMusica::getInstance().atacar(this->nombreEntidad);			
	}

	//Sonido siendo atacado o sea sufrio danio.
	if (this->sufrioDanio==true) {
		VistaMusica::getInstance().recibioUnGolpe(this->nombreEntidad);
		this->setSufrioDanio(false);
	}

	//Sonido recibio golpe pero tenia escudo
	if (this->gastoEscudo==true){
		VistaMusica::getInstance().conEscudo();
		this->setGastoEscudo(false);
	}

	//Sonido gasta barra de magia
	if (this->gastoMagia==true) {
		VistaMusica::getInstance().gastoMagia();
		this->setGastoMagia(false);
	}

	//Sonido gasto bomba
	if (this->gastoBomba==true) {
		VistaMusica::getInstance().gastoBomba();
		this->setGastoBomba(false);
	}

	//Sonidos extra
	if (this->sonidoExtra == true) {
		VistaMusica::getInstance().sonidoExtra(this->nombreEntidad);
		this->sonidoExtra = false;
	}

	return void();
}

int VistaEntidad::tipoEntidad(void){
	return this->_tipoEntidad;
}

bool VistaEntidad::esMiJugador(void){
	return this->_esMiJugador;
}

int VistaEntidad::getVida(){
	return this->vida;
}

int VistaEntidad::getMaximoVida(){
	return this->maximoVida;
}

int VistaEntidad::getMaximoMagia(){
	return this->maximoMagia;
}

int VistaEntidad::getMagia(){
	return this->magia;
}

int VistaEntidad::getCantidadBombas(){
	return this->cantidadBombas;
}

int VistaEntidad::getEscudo(){
	return this->escudo;
}

bool VistaEntidad::getGastoEscudo(){
	return this->gastoEscudo;
}

bool VistaEntidad::getGastoMagia(){
	return this->gastoMagia;
}

void VistaEntidad::setGastoMagia(bool gasto){
	this->gastoMagia = gasto;
}

void VistaEntidad::setGastoEscudo(bool gasto){
	this->gastoEscudo = gasto;
}

void VistaEntidad::setGastoBomba(bool gasto){
	this->gastoBomba = gasto;
}

bool VistaEntidad::getGastoBomba(){
	return this->gastoBomba;
}

void VistaEntidad::setSufrioDanio(bool sufrio){
	this->sufrioDanio= sufrio;
}

bool VistaEntidad::getTieneHechizoHielo(){
	return this->tieneHechizoHielo;
}

bool VistaEntidad::getTieneGolem(){
	return this->tieneGolem;
}

bool VistaEntidad::getTerminoJuego(){
	return this->terminoJuego;
}

std::string VistaEntidad::getNombreDelJugadorGanador(){
	return this->nombreDelJugadorGanador;
}
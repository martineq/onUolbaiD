#include "./VistaLoop.h"

VistaLoop::VistaLoop(void){
	this->pantalla = NULL;
	this->pProxyEntidad = NULL;
	this->hayEntidadEnEspera = false;
	this->entidadEnEspera.id = -1;
	this->vistaChat = NULL;
}

VistaLoop::~VistaLoop(void){
	if( this->pProxyEntidad != NULL ) delete this->pProxyEntidad;	
	if( this->pantalla != NULL ) SDL_FreeSurface(this->pantalla);
	ImageLoader::getInstance().cerrarSDL();	
}

void VistaLoop::setPantalla(SDL_Surface *pantalla){
	this->pantalla = pantalla;
}

char VistaLoop::visibilidadDeLaEntidad(VistaEntidad* unaEntidad, EstadoNivel* estadoNivel){
	int x1 = unaEntidad->getTileX();
	int x2 = unaEntidad->getTileX() + (unaEntidad->getAncho() / ANCHO_TILE) - 1;
	int y1 = unaEntidad->getTileY();
	int y2 = unaEntidad->getTileY() + (unaEntidad->getAlto() / ALTO_TILE) - 1;

	if ((estadoNivel->visibilidad(x1,y1) == VISIBLE) || (estadoNivel->visibilidad(x1,y2) == VISIBLE) || (estadoNivel->visibilidad(x2,y1) == VISIBLE) || (estadoNivel->visibilidad(x2,y2) == VISIBLE))
		return VISIBLE;
	else if (unaEntidad->getEstaCongelado() || (estadoNivel->visibilidad(x1,y1) == CONOCIDO_NO_VISIBLE) || (estadoNivel->visibilidad(x1,y2) == CONOCIDO_NO_VISIBLE) || (estadoNivel->visibilidad(x2,y1) == CONOCIDO_NO_VISIBLE) || (estadoNivel->visibilidad(x2,y2) == CONOCIDO_NO_VISIBLE))
		return CONOCIDO_NO_VISIBLE;
	else
		return NO_CONOCIDO;
}

void VistaLoop::refrescarMatriz(VistaNivel& vistaNivel, EstadoNivel* estadoNivel){
	estadoNivel->visitar(vistaNivel.getJugador()->getTileX(), vistaNivel.getJugador()->getTileY());
}

bool VistaLoop::loop(VistaNivel& vistaNivel,VistaFactory& vistaFactory,EstadoNivel* estadoNivel){
	if( this->actualizarEntidadesPorProxy(vistaNivel,vistaFactory) == false) return false;	// Nuevo: Actuliza lo que vino por el proxy

	if ( (vistaNivel.getJugador()->getTileXAnterior() != vistaNivel.getJugador()->getTileX())
		|| (vistaNivel.getJugador()->getTileYAnterior() != vistaNivel.getJugador()->getTileY()) ) {
			this->refrescarMatriz(vistaNivel,estadoNivel);
	}

	if( this->dibujarEntidades(vistaNivel, estadoNivel) == false) return false;
	if (!this->vistaChat->graficar(this->pantalla)) return false;
	ImageLoader::getInstance().refrescarPantalla(this->pantalla);
	return true;
}

bool VistaLoop::dibujarEntidades(VistaNivel& vistaNivel, EstadoNivel* estadoNivel){
	list<VistaEntidad*> listaJugadores = vistaNivel.getListaOtrosJugadores();
	list<VistaEntidad*> listaEntidades = vistaNivel.getListaEntidades();
	list<VistaEntidad*>::iterator jugador = listaJugadores.begin();
	list<VistaEntidad*>::iterator entidad = listaEntidades.begin();

	//grafica los tiles
	vistaNivel.getScroll()->graficar(this->pantalla,estadoNivel);

	//Dibujo las entidades (y el jugador si corresponde)
	while (entidad != listaEntidades.end()) {
		VistaEntidad* unaEntidad = *entidad;
		entidad++;

		// Si el jugador esta antes que la entidad que voy a dibujar lo dibujo primero
		if (jugador != listaJugadores.end()) {
			if (VistaNivel::ordenadorEntidades(*jugador, unaEntidad)) {
				if ((*jugador)->verificarBordePantalla(vistaNivel.getScroll())) {
					(*jugador)->setPantalla(this->pantalla);
					(*jugador)->setXEnPantalla(vistaNivel.getScroll()->getX());
					(*jugador)->setYEnPantalla(vistaNivel.getScroll()->getY());
					char visibilidad = this->visibilidadDeLaEntidad((*jugador),estadoNivel);
					if (visibilidad == VISIBLE ){
						if (!(*jugador)->graficar(visibilidad))
							return false;
					}
				}
				jugador++;
			}
		}

		if (unaEntidad->verificarBordePantalla(vistaNivel.getScroll())) {
			unaEntidad->setPantalla(this->pantalla);
			unaEntidad->setXEnPantalla(vistaNivel.getScroll()->getX());
			unaEntidad->setYEnPantalla(vistaNivel.getScroll()->getY());
			if (!unaEntidad->graficar(this->visibilidadDeLaEntidad(unaEntidad,estadoNivel)))
				return false;
		}
	}
	
	// Dibujo los jugadores que no dibuje
	while (jugador != listaJugadores.end()) {
		if ((*jugador)->verificarBordePantalla(vistaNivel.getScroll())) {
			(*jugador)->setPantalla(this->pantalla);
			(*jugador)->setXEnPantalla(vistaNivel.getScroll()->getX());
			(*jugador)->setYEnPantalla(vistaNivel.getScroll()->getY());
			char visibilidad = this->visibilidadDeLaEntidad((*jugador),estadoNivel);
			if (visibilidad == VISIBLE ){
  			   if (!(*jugador)->graficar(visibilidad))
				  return false;
			}
		}
		jugador++;
	}

	if (vistaNivel.getScroll()->getEsNecesarioRefrescar())
		vistaNivel.getScroll()->setEsNecesarioRefrescar(false);

	return true;
}

void VistaLoop::SetProxyModeloEntidad(ProxyModeloEntidad* pProxyEntidad){
	this->pProxyEntidad = pProxyEntidad;
}

// Tomo todas las notificaciones de actualización de entidades y las proceso
bool VistaLoop::actualizarEntidadesPorProxy(VistaNivel& vistaNivel,VistaFactory& vistaFactory){

	// Si antes corté por tener entidad con ID repetido, la misma quedó en espera y entonces ahora la actualizo primero
	if (this->hayEntidadEnEspera == true) {
		if (this->actualizarEntidad(this->entidadEnEspera,vistaNivel,vistaFactory) == false ) return false;
		this->entidadEnEspera.id = -1;
		this->hayEntidadEnEspera = false;
	}
	else {
		if (this->pProxyEntidad->recibirEntidad(this->entidadEnEspera) == false) {
			return true;
		}
		else {
			this->hayEntidadEnEspera = false;
			if (this->actualizarEntidad(this->entidadEnEspera,vistaNivel,vistaFactory) == false) return false;
		}
	}

	// Cargo la lista hasta que por alguna razon me detenga. Puede ser por que se vació el proxy o porque tengo dos entidad de un mismo ID
	ProxyModeloEntidad::stEntidad entidadObtenida;
	bool leerDeProxy = true;
	while (leerDeProxy == true) {
		if (this->pProxyEntidad->recibirEntidad(entidadObtenida) == false) { // Caso: El proxy no tiene entidad para dar
			leerDeProxy = false;
		}
		else {
			if (entidadObtenida.id == this->entidadEnEspera.id) { // Caso: Recibo entidad pero tengo uno de ese ID
				this->entidadEnEspera = entidadObtenida;
				this->hayEntidadEnEspera = true; // Como esta entidad se queda, lo notifico			
				leerDeProxy = false;
			}
			else { // Caso: Recibo entidad de un ID que no tenía hasta ahora
				this->entidadEnEspera = entidadObtenida;
				this->hayEntidadEnEspera = false;
				if( this->actualizarEntidad(this->entidadEnEspera,vistaNivel,vistaFactory) == false ) return false;
			}

		}
	}
	return true;
}

// Recorro todas las entidades tratando de actualizar o eliminar la entidad indicada por el stEntidad
bool VistaLoop::actualizarEntidad(ProxyModeloEntidad::stEntidad& entidad,VistaNivel& vistaNivel,VistaFactory& vistaFactory){

	// Primero me fijo si no hubo error de sockets
	if( entidad.errorEnSocket == true ){
		Log::getInstance().log(1,__FILE__,__LINE__,"Error al recibir datos desde el Servidor");	
		return false;
	}

	if( entidad.id == ID_FALSO ) return true;	// Si id == ID_FALSO quiere decir que este es un paquete de testeo de conexión, no hay que hacer nada
	
	// Preparo la búsqueda de la entidad
	VistaEntidad* jugador = vistaNivel.getJugador();
	std::list<VistaEntidad*> entidades = vistaNivel.getListaEntidades();
	std::list<VistaEntidad*> jugadores = vistaNivel.getListaOtrosJugadores();
	VistaEntidad* entidadEncontrada = NULL;
	int idBuscado = entidad.id;
	std::list<VistaEntidad*>::iterator iteradorEntidadEncontrada;
	
	// Si se recibio un mensaje para el chat
	if (entidad.idRemitente != -1) {
		if (entidad.id != vistaNivel.getJugador()->id())
			return true;
		VistaEntidad* remitente = NULL;
		// Busco al remitente en la lista de jugadores
		for (std::list<VistaEntidad*>::iterator unaEntidad = jugadores.begin(); unaEntidad != jugadores.end(); unaEntidad++) {
			if ((*unaEntidad)->id() == entidad.idRemitente) {
				remitente = *unaEntidad;
				break;
			}
		}
		this->vistaChat->agregarMensaje(remitente, entidad.mensaje);
		return true;
	}

	// Primero miro si la entidad que busco es el jugador
	if (jugador->id() == idBuscado) {
		entidadEncontrada = jugador;
	}
	else { // Si no es el jugador entonces busco en las otras entidades
		for (std::list<VistaEntidad*>::iterator it=entidades.begin() ; it != entidades.end() ; it++ ){ // Busco en el vector por el ID
			if( (*it)->id() == idBuscado ){
				iteradorEntidadEncontrada = it;
				entidadEncontrada = (*it);
			}
		}
		if (entidadEncontrada == NULL) {
			for (std::list<VistaEntidad*>::iterator it=jugadores.begin() ; it != jugadores.end() ; it++ ){ // Busco en el vector por el ID
				if( (*it)->id() == idBuscado ){
					iteradorEntidadEncontrada = it;
					entidadEncontrada = (*it);
				}
			}
		}
	}

	// Actuo si encontré la entidad que buscaba
	if( entidadEncontrada != NULL) {
		// Si no me pide eliminar entonces actualizo los datos
		entidadEncontrada->actualizar(entidad);
		vistaNivel.ordenarJugadores();
	}
	else {
		// Cuando no existe, crea la entidad
		vistaFactory.crearJugadorSinScroll(vistaNivel,entidad);
	}

	return true;
}

ProxyModeloEntidad** VistaLoop::getPunteroProxy(){
	return &(this->pProxyEntidad);
}

SDL_Surface** VistaLoop::getPunteroPantalla(){
	return &(this->pantalla);

}

void VistaLoop::asignarChat(VistaChat* vistaChat) {
	this->vistaChat = vistaChat;
}

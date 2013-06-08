#include "./VistaLoop.h"

VistaLoop::VistaLoop(void){
	this->pantalla = NULL;
	this->pProxyEntidad = NULL;
	this->hayEntidadEnEspera = false;
	this->reproduciAtacar = false;
	this->entidadEnEspera.id = -1;
	this->vistaChat = NULL;		
	this->textoVida = NULL;
	this->textoMagia = NULL;
	this->textoEscudo = NULL;		
	this->textoCantidadBombas = NULL;
	this->fuente = NULL;
}

VistaLoop::~VistaLoop(void){
	if( this->pProxyEntidad != NULL ) delete this->pProxyEntidad;	
	if( this->pantalla != NULL ) SDL_FreeSurface(this->pantalla);
	if (this->fuente != NULL) TTF_CloseFont( this->fuente ); 
	if (this->textoVida != NULL) SDL_FreeSurface( textoVida );    
	if (this->textoMagia != NULL) SDL_FreeSurface( textoMagia );    
	if (this->textoEscudo != NULL) SDL_FreeSurface( textoEscudo );    	
	if (this->textoCantidadBombas != NULL) SDL_FreeSurface( textoCantidadBombas );    		
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
	//Item Lampara
	estadoNivel->rangoVision(vistaNivel.getJugador()->getRangoVision());
	estadoNivel->visitar(vistaNivel.getJugador()->getTileX(), vistaNivel.getJugador()->getTileY());
}

void VistaLoop::reproducirSonidos(VistaNivel& vistaNivel){
	//Sonido de atacando.
	if ( vistaNivel.getJugador()->getCodigoAnimacion() > 8 && vistaNivel.getJugador()->getCodigoAnimacion() < 17 ){
		/*if (!this->reproduciAtacar) {
			VistaMusica::getInstance().atacar();			
			reproduciAtacar = true;
		}*/
		/*bool esPrimeraAnimacion = vistaNivel.getJugador()->getEsPrimerMovimiento();
		if ( esPrimeraAnimacion ){*/
			VistaMusica::getInstance().atacar();			
			//this->reproduciAtacar = false;			
		//}
	}

	//Sonido siendo atacado o sea sufrio danio.
	if (vistaNivel.getJugador()->getSufrioDanio()) {
		VistaMusica::getInstance().recibioUnGolpe();
		vistaNivel.getJugador()->setSufrioDanio(false);
	}

	//Sonido recibio golpe pero tenia escudo
	if (vistaNivel.getJugador()->getGastoEscudo()){
		VistaMusica::getInstance().conEscudo();
		vistaNivel.getJugador()->setGastoEscudo(false);
	}

	//Sonido gasta barra de magia
	if (vistaNivel.getJugador()->getGastoMagia()) {
		VistaMusica::getInstance().gastoMagia();
		vistaNivel.getJugador()->setGastoMagia(false);
	}

	//Sonido gasto bomba
	if (vistaNivel.getJugador()->getGastoBomba()) {
		VistaMusica::getInstance().gastoBomba();
		vistaNivel.getJugador()->setGastoBomba(false);
	}
}

bool VistaLoop::loop(VistaNivel& vistaNivel,VistaFactory& vistaFactory,EstadoNivel* estadoNivel){
	bool actualizarMatriz = false;
	if( this->actualizarEntidadesPorProxy(vistaNivel,vistaFactory,actualizarMatriz) == false) return false;	// Actuliza lo que vino por el proxy

	//Item Mapa
	estadoNivel->setTieneMapa(vistaNivel.getJugador()->getTieneMapa());

	this->reproducirSonidos(vistaNivel);

	if ( (vistaNivel.getJugador()->getTileXAnterior() != vistaNivel.getJugador()->getTileX())
		|| (vistaNivel.getJugador()->getTileYAnterior() != vistaNivel.getJugador()->getTileY()) || actualizarMatriz == true ) {
			this->refrescarMatriz(vistaNivel,estadoNivel);
	}

	if ( this->dibujarEntidades(vistaNivel, estadoNivel) == false) return false;	
	if ( this->vistaChat->graficar(this->pantalla) == false) return false;
	if ( this->dibujarStats(vistaNivel) == false) return false;
	ImageLoader::getInstance().refrescarPantalla(this->pantalla);
	return true;
}

bool VistaLoop::dibujarStats(VistaNivel& vistaNivel){
	VistaEntidad* jugador = vistaNivel.getJugador();
	int thickness = 10;			
	this->fuente = TTF_OpenFont( "./fonts/Lazy.ttf", 28 );
	SDL_Color textColor = { 255, 255, 255 }; //color blanco 	

	//Vida
	int vidaPorcentual = (jugador->getVida()*100/jugador->getMaximoVida());	
	stringstream ss; 	
	ss << vidaPorcentual;
	ss << '%';
	string auxiliar = ss.str();
	this->textoVida = TTF_RenderText_Solid( this->fuente, auxiliar.c_str(), textColor );		
	SDL_BlitSurface( textoVida, NULL, pantalla, NULL);
	boxRGBA( this->pantalla, 50, 10, 100*4+50, thickness+10, 0, 0, 0, 255); //barra negra
	if (vidaPorcentual <= 10) 
		boxRGBA( this->pantalla, 50, 10, vidaPorcentual*4+50, thickness+10, 255, 0, 0, 255);
	else
		boxRGBA( this->pantalla, 50, 10, vidaPorcentual*4+50, thickness+10, 0, 255, 0, 255);

	//Magia
	int magiaPorcentual = (jugador->getMagia()*100/jugador->getMaximoMagia());	
	ss.str("");
	ss << magiaPorcentual;	
	ss << '%';
	auxiliar = "";
	auxiliar = ss.str();
	this->textoMagia = TTF_RenderText_Solid( this->fuente, auxiliar.c_str(), textColor );	
	SDL_Rect offset;
	offset.x = 0;
	offset.y = 30;
	SDL_BlitSurface( textoMagia, NULL, pantalla, &offset);
	boxRGBA( this->pantalla, 50, 40, 100*4+50, thickness+40, 0, 0, 0, 255); //barra negra
	if (vidaPorcentual <= 10) 
		boxRGBA( this->pantalla, 50, 40, magiaPorcentual*4+50, thickness+40, 0, 255, 0, 255);
	else
		boxRGBA( this->pantalla, 50, 40, magiaPorcentual*4+50, thickness+40, 124, 230, 228, 255);

	//Escudo
	int escudoPorcentual = jugador->getEscudo()*100/MAXIMO_ESCUDO;
	ss.str("");
	ss << escudoPorcentual;		
	ss << '%';
	auxiliar = "";
	auxiliar = ss.str();
	this->textoEscudo = TTF_RenderText_Solid( this->fuente, auxiliar.c_str(), textColor );		
	offset.x = 0;
	offset.y = 60;
	SDL_BlitSurface( textoEscudo, NULL, pantalla, &offset);
	boxRGBA( this->pantalla, 50, 70, 100*4+50, thickness+70, 0, 0, 0, 255); //barra negra
	if (escudoPorcentual <= 10) 
		boxRGBA( this->pantalla, 50, 70, escudoPorcentual*4+50, thickness+70, 255, 0, 0, 255);
	else
		boxRGBA( this->pantalla, 50, 70, escudoPorcentual*4+50, thickness+70, 0, 255, 0, 255);	

	//Cantidad de bombas		
	ss.str("");
	ss << vistaNivel.getJugador()->getCantidadBombas();
	auxiliar = "";
	auxiliar = ss.str();	
	offset.x = 0;
	offset.y = 90;	
	if (vistaNivel.getJugador()->getCantidadBombas() > 0) {
		SDL_BlitSurface ( vistaNivel.getPngBomba(), NULL, pantalla, &offset );
		offset.x = 19;
		offset.y = 110;
		this->textoCantidadBombas = TTF_RenderText_Solid( this->fuente, auxiliar.c_str(), textColor );		
		SDL_BlitSurface( this->textoCantidadBombas, NULL, pantalla, &offset);
	}

	//Tiene hechizos		
	ss.str("");
	ss << 10;
	auxiliar = "";
	auxiliar = ss.str();
	offset.x = 0;
	offset.y = 150;
	if (vistaNivel.getJugador()->getTieneHechizoHielo()) 
		SDL_BlitSurface ( vistaNivel.getPngMagia(), NULL, pantalla, &offset );		
	
	
	//Tiene Golem
	/*ss.str("");
	ss << 10;
	auxiliar = "";
	auxiliar = ss.str();
	offset.x = 0;
	offset.y = 120;
	if (vistaNivel.getJugador()->getTieneGolem()) {
		offset.w = vistaNivel.getPngGolem()->w;
		offset.h = vistaNivel.getPngGolem()->h;
		SDL_BlitSurface ( vistaNivel.getPngGolem(), NULL, pantalla, &offset );		
	}*/
	
	return true;
}

bool VistaLoop::dibujarEntidades(VistaNivel& vistaNivel, EstadoNivel* estadoNivel){
	list<VistaEntidad*> listaJugadores = vistaNivel.getListaOtrosJugadores();
	list<VistaEntidad*> listaEntidades = vistaNivel.getListaEntidades();
	list<VistaEntidad*>::iterator jugador = listaJugadores.begin();
	list<VistaEntidad*>::iterator entidad = listaEntidades.begin();

	// Grafica los tiles
	vistaNivel.getScroll()->graficar(this->pantalla,estadoNivel);

	// Dibujo las entidades (y el jugador si corresponde)
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
bool VistaLoop::actualizarEntidadesPorProxy(VistaNivel& vistaNivel,VistaFactory& vistaFactory, bool& actualizarMatriz){

	// Si antes corté por tener entidad con ID repetido, la misma quedó en espera y entonces ahora la actualizo primero
	if (this->hayEntidadEnEspera == true) {
		if (this->actualizarEntidad(this->entidadEnEspera,vistaNivel,vistaFactory,actualizarMatriz) == false ) return false;
		this->entidadEnEspera.id = -1;
		this->hayEntidadEnEspera = false;
	}
	else {
		if (this->pProxyEntidad->recibirEntidad(this->entidadEnEspera) == false) {
			return true;
		}
		else {
			this->hayEntidadEnEspera = false;
			if (this->actualizarEntidad(this->entidadEnEspera,vistaNivel,vistaFactory,actualizarMatriz) == false) return false;
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
				if( this->actualizarEntidad(this->entidadEnEspera,vistaNivel,vistaFactory,actualizarMatriz) == false ) return false;
			}

		}
	}
	return true;
}

// Recorro todas las entidades tratando de actualizar o eliminar la entidad indicada por el stEntidad
bool VistaLoop::actualizarEntidad(ProxyModeloEntidad::stEntidad& entidad,VistaNivel& vistaNivel,VistaFactory& vistaFactory, bool& actualizarMatriz){

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

	// Primero miro si la entidad que busco es el jugador de este cliente
	if (jugador->id() == idBuscado) {
		entidadEncontrada = jugador;

		// Si además de ser mi jugador, se encuentra con vida == 0 muevo el scroll a su posición inicial.
		if( entidad.vida == 0 ) vistaNivel.reiniciarPosicionScroll();

	}
	else { // Si no es el jugador de este cliente entonces busco en las otras entidades
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
		if( entidadEncontrada->tipoEntidad() == TIPO_ITEM_LAMPARA) actualizarMatriz = true;  // TODO Cambiar por una constante que identifique solo a la lampara
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

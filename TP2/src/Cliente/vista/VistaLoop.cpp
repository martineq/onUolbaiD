#include "./VistaLoop.h"

VistaLoop::VistaLoop(void){
	this->pantalla = NULL;
	this->pProxyEntidad = NULL;
	this->hayEntidadEnEspera = false;
	this->entidadEnEspera.id = -1;
}

VistaLoop::~VistaLoop(void){
	if( this->pProxyEntidad != NULL ) delete this->pProxyEntidad;	
	if( this->pantalla != NULL ) SDL_FreeSurface(this->pantalla);
	ImageLoader::getInstance().cerrarSDL();	
}

void VistaLoop::setPantalla(SDL_Surface *pantalla){
	this->pantalla = pantalla;
}

bool VistaLoop::loop(VistaNivel& vistaNivel){
	if( this->actualizarEntidadesPorProxy(vistaNivel) == false) return false;	// Nuevo: Actuliza lo que vino por el proxy
	if( this->dibujarEntidades(vistaNivel) == false) return false;
	return true;
}

bool VistaLoop::dibujarEntidades(VistaNivel& vistaNivel){

	list<VistaEntidad*> listaDeEntidades = vistaNivel.getListaEntidades();	
	list<VistaEntidad*>::iterator it = listaDeEntidades.begin();	

	vistaNivel.getScroll()->graficar(this->pantalla);

	// Primero dibujo todas las entidades que no son el jugador
	while (it != listaDeEntidades.end()){
		VistaEntidad* unaEntidad = *it;
		//Es necesario actualizar o porque cambio de posicion o porque se actualizo el scroll
		
		//if ( (vistaNivel.getScroll()->getEsNecesarioRefrescar() == true ) ){
			unaEntidad->verificarBordePantalla(vistaNivel.getScroll());
			//vistaNivel.getScroll()->setEsNecesarioRefrescar(false);
		//}

		unaEntidad->setPantalla(this->pantalla);
		if( unaEntidad->graficar() == false ) return false;
		it++;
	}

	// Al final dibujo al jugador
	vistaNivel.getJugador()->verificarBordePantalla(vistaNivel.getScroll());
	vistaNivel.getJugador()->setPantalla(this->pantalla);
	if( vistaNivel.getJugador()->graficar() == false ) return false;
	
	if ( (vistaNivel.getScroll()->getEsNecesarioRefrescar() == true ) ){	
		vistaNivel.getScroll()->setEsNecesarioRefrescar(false);		
	}

	ImageLoader::getInstance().refrescarPantalla(this->pantalla);

	return true;
}

void VistaLoop::SetProxyModeloEntidad(ProxyModeloEntidad* pProxyEntidad){
	this->pProxyEntidad = pProxyEntidad;
}

// Tomo todas las notificaciones de actualización de entidades y las proceso
bool VistaLoop::actualizarEntidadesPorProxy(VistaNivel& vistaNivel){

	// Si antes corté por tener entidad con ID repetido, la misma quedó en espera y entonces ahora la actualizo primero
	if( this->hayEntidadEnEspera == true ){
		if( this->actualizarEntidad(this->entidadEnEspera,vistaNivel) == false ) return false;
		this->entidadEnEspera.id = -1;
		this->hayEntidadEnEspera = false;
	}else{
		if( this->pProxyEntidad->recibirEntidad(this->entidadEnEspera) == false ){
				return true;
		}else{
				this->hayEntidadEnEspera = false;
				if( this->actualizarEntidad(this->entidadEnEspera,vistaNivel) == false ) return false;
		}
	}

	// Cargo la lista hasta que por alguna razon me detenga. Puede ser por que se vació el proxy o porque tengo dos entidad de un mismo ID
	ProxyModeloEntidad::stEntidad entidadObtenida;
	bool leerDeProxy = true;
	while( leerDeProxy == true ){
		if( this->pProxyEntidad->recibirEntidad(entidadObtenida) == false ){	// Caso: El proxy no tiene entidad para dar
			leerDeProxy = false;
		}else{
			if( entidadObtenida.id == this->entidadEnEspera.id ){				// Caso: Recibo entidad pero tengo uno de ese ID
				this->entidadEnEspera = entidadObtenida;
				this->hayEntidadEnEspera = true;// Como esta entidad se queda, lo notifico			
				leerDeProxy = false;
			}else{																// Caso: Recibo entidad de un ID que no tenía hasta ahora
				this->entidadEnEspera = entidadObtenida;
				this->hayEntidadEnEspera = false;
				if( this->actualizarEntidad(this->entidadEnEspera,vistaNivel) == false ) return false;
			}

		}
		
	}
	return true;
}

// Recorro todas las entidades tratando de actualizar o eliminar la entidad indicada por el stEntidad
bool VistaLoop::actualizarEntidad(ProxyModeloEntidad::stEntidad& entidad,VistaNivel& vistaNivel){

	// Primero me fijo si no hubo error de sockets
	if( entidad.errorEnSocket == true ){
		Log::getInstance().log(1,__FILE__,__LINE__,"Error al recibir datos desde el Servidor");	
		return false;
	}
	
	// Preparo todo para la búsqueda de la entidad
	VistaEntidad* jugador = vistaNivel.getJugador();
	std::list<VistaEntidad*> entidades = vistaNivel.getListaEntidades();
	VistaEntidad* entidadEncontrada = NULL;
	int idBuscado = entidad.id;
	std::list<VistaEntidad*>::iterator iteradorEntidadEncontrada;
	
	// Primero miro si la entidad que busco es el jugador
	if( jugador->id() == idBuscado){
		entidadEncontrada = jugador;
	}else{	// Si no es el jugador entonces busco en las otras entidades
		for (std::list<VistaEntidad*>::iterator it=entidades.begin() ; it != entidades.end() ; it++ ){ // Busco en el vector por el ID
			if( (*it)->id() == idBuscado ){
				iteradorEntidadEncontrada = it;
				entidadEncontrada = (*it);
			}
		}
	}

	// Actuo si encontré la entidad que buscaba
	if( entidadEncontrada != NULL ){
		if( entidad.eliminarEntidad == true ){  // Si me pide eliminar
			if( entidadEncontrada == jugador ){
				return false;		// Doy por terminado el juego porque me pide eliminar a mi jugador
			}else{
				entidades.erase(iteradorEntidadEncontrada);		// Elimino a la entidad encontrada
			}
		}else{	// Si no me pide eliminar entonces actualizo los datos
			entidadEncontrada->actualizar(entidad);			
		}
	}
	return true;
}


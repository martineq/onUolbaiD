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
	this->actualizarEntidadesPorProxy(vistaNivel);
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

void VistaLoop::actualizarEntidadesPorProxy(VistaNivel& vistaNivel){
	// TODO: Repasar y ver si cumple con todo.

	// Si antes corté por tener entidad con ID repetido, la misma quedó en espera y entonces ahora la actualizo primero
	if( this->hayEntidadEnEspera == true ){
		this->actualizarEntidad(this->entidadEnEspera,vistaNivel);
		this->entidadEnEspera.id = -1;
		this->hayEntidadEnEspera = false;
	}else{
		if( this->pProxyEntidad->recibirEntidad(this->entidadEnEspera) == false ){
				return void();
		}else{
				this->hayEntidadEnEspera = false;
				this->actualizarEntidad(this->entidadEnEspera,vistaNivel);
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
				this->actualizarEntidad(entidadObtenida,vistaNivel);
			}

		}
		
	}
	return void();
}

void VistaLoop::actualizarEntidad(ProxyModeloEntidad::stEntidad& entidad,VistaNivel& vistaNivel){

	// TODO: Implementar. Busco la entidad en VistaNivel por su ID y actualizo los datos
}
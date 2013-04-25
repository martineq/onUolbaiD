#include "./VistaLoop.h"

VistaLoop::VistaLoop(void){
	this->pantalla = NULL;
}

void VistaLoop::setPantalla(SDL_Surface *pantalla){
	this->pantalla = pantalla;
}

bool VistaLoop::loop(VistaNivel& vistaNivel){
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

VistaLoop::~VistaLoop(void){
	if( this->pantalla != NULL ) SDL_FreeSurface(this->pantalla);
	ImageLoader::getInstance().cerrarSDL();	
}

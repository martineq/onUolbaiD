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

bool VistaLoop::dibujarEntidades(VistaNivel& vistaNivel) {
	list<VistaEntidad*> listaDeEntidades = vistaNivel.getListaEntidades();
	list<VistaEntidad*>::iterator it = listaDeEntidades.begin();	
	bool jugadorDibujado = false;

	vistaNivel.getScroll()->graficar(this->pantalla);

	while (it != listaDeEntidades.end()) {
		VistaEntidad* unaEntidad = *it;
		it++;

		// Si el jugador esta antes que la entidad que voy a dibujar lo dibujo primero
		if (!jugadorDibujado && (vistaNivel.getJugador()->posicion() < unaEntidad->posicion())) {
			vistaNivel.getJugador()->verificarBordePantalla(vistaNivel.getScroll());
			vistaNivel.getJugador()->setPantalla(this->pantalla);
			if (!vistaNivel.getJugador()->graficar())
				return false;
			jugadorDibujado = true;
		}

		unaEntidad->verificarBordePantalla(vistaNivel.getScroll());
		unaEntidad->setPantalla(this->pantalla);
		if(!unaEntidad->graficar())
			return false;
	}
	
	// Si no dibuje el jugador lo dibujo ahora
	if (!jugadorDibujado) {
		vistaNivel.getJugador()->verificarBordePantalla(vistaNivel.getScroll());
		vistaNivel.getJugador()->setPantalla(this->pantalla);
		if (!vistaNivel.getJugador()->graficar())
			return false;
	}

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

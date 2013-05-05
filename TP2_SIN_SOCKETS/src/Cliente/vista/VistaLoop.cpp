#include "./VistaLoop.h"

VistaLoop::VistaLoop(void){
	this->pantalla = NULL;
}

void VistaLoop::setPantalla(SDL_Surface *pantalla){
	this->pantalla = pantalla;
}

char VistaLoop::visibilidadDeLaEntidad(VistaEntidad* unaEntidad, char** matriz){

	if (int(unaEntidad->getAncho() / ANCHO_TILE) == 1 && int(unaEntidad->getAlto() / ALTO_TILE) == 1) {
		return matriz[unaEntidad->getTileX()][unaEntidad->getTileY()];
	}
	//si alguna esquina tiene el numero VISIBLE es porque es visible
	else if ( (matriz[unaEntidad->getTileX()][unaEntidad->getTileY()] == VISIBLE) || 
		 ((matriz[(int)(unaEntidad->getTileX())][(int)((unaEntidad->getTileX() + unaEntidad->getAncho() / ANCHO_TILE) - 1)]) == VISIBLE) ||
		 ((matriz[(int)((unaEntidad->getTileY() + unaEntidad->getAlto() / ALTO_TILE) - 1)][(int)unaEntidad->getTileY()]) == VISIBLE) || 
		 ((matriz[(int)((unaEntidad->getTileX() + unaEntidad->getAncho() / ANCHO_TILE) - 1)][(int)((unaEntidad->getTileY() + unaEntidad->getAlto() / ALTO_TILE) - 1)]) == VISIBLE) )
	return VISIBLE;

	//si alguna esquina tiene el numero 1 es porque es gris
	else if ( (matriz[unaEntidad->getTileX()][unaEntidad->getTileY()] == CONOCIDO_NO_VISIBLE) || 
		 ((matriz[(int)(unaEntidad->getTileX())][(int)((unaEntidad->getTileX() + unaEntidad->getAncho() / ANCHO_TILE) - 1)]) == CONOCIDO_NO_VISIBLE) ||
		 ((matriz[(int)((unaEntidad->getTileY() + unaEntidad->getAlto() / ALTO_TILE) - 1)][(int)unaEntidad->getTileY()]) == CONOCIDO_NO_VISIBLE) || 
		 ((matriz[(int)((unaEntidad->getTileX() + unaEntidad->getAncho() / ANCHO_TILE) - 1)][(int)((unaEntidad->getTileY() + unaEntidad->getAlto() / ALTO_TILE) - 1)]) == CONOCIDO_NO_VISIBLE) )
	return CONOCIDO_NO_VISIBLE;
	
	//si ninguna esquina es 1 o 2 es porque es 0
	else return NO_CONOCIDO;
}

void VistaLoop::refrescarMatriz(VistaNivel& vistaNivel, char** matriz){
	//pinto de gris segun el movimiento que hizo
	VistaEntidad* jugador = vistaNivel.getJugador();

	//******************************Validacion de posicion para arriba o abajo*****************************//

	int mitadDeZonaVisible = ZONA_VISIBLE/2;
	int inicioX = vistaNivel.getJugador()->getTileX() - mitadDeZonaVisible;
	int finX = vistaNivel.getJugador()->getTileX() + mitadDeZonaVisible;		
	int inicioY = vistaNivel.getJugador()->getTileY() - mitadDeZonaVisible;
	int finY = vistaNivel.getJugador()->getTileY() + mitadDeZonaVisible + 1;		

	//se movio hacia arriba 
	if ( (jugador->getTileY() < jugador->getTileYAnterior()) && (!(jugador->getTileX() < jugador->getTileXAnterior()))
		&& (!(jugador->getTileX() > jugador->getTileXAnterior())) ) {		
		
		if (inicioX < 0) inicioX = 0;
		if (finX >= vistaNivel.getAnchoDeNivelEnTiles()) finX = vistaNivel.getAnchoDeNivelEnTiles() - 1;
		if (inicioY < 0) inicioY = 0;
		if (finY >= vistaNivel.getAltoDeNivelEnTiles()) finY = vistaNivel.getAltoDeNivelEnTiles() - 1;	
		
		for (int i = inicioX; i <= finX; i++){
			if (jugador->getTileY() < vistaNivel.getAltoDeNivelEnTiles() - mitadDeZonaVisible - 1) matriz[i][finY] = CONOCIDO_NO_VISIBLE;
			matriz[i][inicioY] = VISIBLE;
		}
		
	}

	//se movio a la derecha
	else if ( (jugador->getTileX() > jugador->getTileXAnterior()) && (!(jugador->getTileY() < jugador->getTileYAnterior()))
		&& (!(jugador->getTileY() > jugador->getTileYAnterior())) ) {

		inicioX = vistaNivel.getJugador()->getTileX() - mitadDeZonaVisible - 1; 
		finX = vistaNivel.getJugador()->getTileX() + mitadDeZonaVisible; 
		if (inicioX < 0) inicioX = 0;	
		if (finX >= vistaNivel.getAnchoDeNivelEnTiles()) finX = vistaNivel.getAnchoDeNivelEnTiles() - 1;

		inicioY = jugador->getTileY() - mitadDeZonaVisible;
		finY = jugador->getTileY() + mitadDeZonaVisible;
		if (inicioY < 0) inicioY = 0;
		if (finY >= vistaNivel.getAltoDeNivelEnTiles()) finY = vistaNivel.getAltoDeNivelEnTiles() - 1;

		for (int i = inicioY; i <= finY; i++){
			if (jugador->getTileX() > mitadDeZonaVisible)  matriz[inicioX][i] = CONOCIDO_NO_VISIBLE; //posicion del jugador +3 del alto ahora del nivel
			matriz[finX][i] = VISIBLE;
		}		

	}

	
	//se movio hacia abajo		
	else if ( (jugador->getTileY() > jugador->getTileYAnterior()) && (!(jugador->getTileX() < jugador->getTileXAnterior()))
		&& (!(jugador->getTileX() > jugador->getTileXAnterior())) ) {
		
		inicioX = vistaNivel.getJugador()->getTileX() - mitadDeZonaVisible; 
		finX = vistaNivel.getJugador()->getTileX() + mitadDeZonaVisible; 
		if (inicioX < 0) inicioX = 0;	
		if (finX >= vistaNivel.getAnchoDeNivelEnTiles()) finX = vistaNivel.getAnchoDeNivelEnTiles() - 1;

		inicioY = jugador->getTileY() - mitadDeZonaVisible - 1;
		finY = jugador->getTileY() + mitadDeZonaVisible;
		if (inicioY < 0) inicioY = 0;
		if (finY >= vistaNivel.getAltoDeNivelEnTiles()) finY = vistaNivel.getAltoDeNivelEnTiles() - 1;

		for (int i = inicioX; i <= finX; i++){
			if (jugador->getTileY() > mitadDeZonaVisible) matriz[i][inicioY] = CONOCIDO_NO_VISIBLE;
			matriz[i][finY] = VISIBLE;
		}

	}	

	//se movio a la izquierda
	else if ( (jugador->getTileX() < jugador->getTileXAnterior()) && (!(jugador->getTileY() < jugador->getTileYAnterior()))
		&& (!(jugador->getTileY() > jugador->getTileYAnterior())) ) {

		inicioX = vistaNivel.getJugador()->getTileX() - mitadDeZonaVisible; 
		finX = vistaNivel.getJugador()->getTileX() + mitadDeZonaVisible + 1; 
		if (inicioX < 0) inicioX = 0;	
		if (finX >= vistaNivel.getAnchoDeNivelEnTiles()) finX = vistaNivel.getAnchoDeNivelEnTiles() - 1;

		inicioY = jugador->getTileY() - mitadDeZonaVisible;
		finY = jugador->getTileY() + mitadDeZonaVisible;
		if (inicioY < 0) inicioY = 0;
		if (finY >= vistaNivel.getAltoDeNivelEnTiles()) finY = vistaNivel.getAltoDeNivelEnTiles() - 1;
		
		for (int i = inicioY; i <= finY; i++){
			if (jugador->getTileX() < vistaNivel.getAnchoDeNivelEnTiles() - mitadDeZonaVisible -1) 
				matriz[finX][i] = CONOCIDO_NO_VISIBLE;
			matriz[inicioX][i] = VISIBLE;
		}		

	}

	//se movio a la derecha y arriba
	else if ( (jugador->getTileX() > jugador->getTileXAnterior()) && (jugador->getTileY() < jugador->getTileYAnterior()) ) {

		inicioX = vistaNivel.getJugador()->getTileX() - mitadDeZonaVisible - 1; //-3
		finX = vistaNivel.getJugador()->getTileX() + 1; 
		if (inicioX < 0) inicioX = 0;	
		if (finX >= vistaNivel.getAnchoDeNivelEnTiles()) finX = vistaNivel.getAnchoDeNivelEnTiles() - 1;  

		inicioY = jugador->getTileY() - 1;
		finY = jugador->getTileY() + mitadDeZonaVisible + 1;
		if (inicioY < 0) inicioY = 0;
		if (finY >= vistaNivel.getAltoDeNivelEnTiles()) finY = vistaNivel.getAltoDeNivelEnTiles() - 1;

		
		// pinta gris la columna de la izquierda 
		for (int i = inicioY; i <= finY; i++){
			if (jugador->getTileX() > mitadDeZonaVisible) matriz[inicioX][i] = CONOCIDO_NO_VISIBLE;
		}
		
		//pinta gris la fila de abajo
		for (int i = inicioX; i <= finX; i++){
			if (jugador->getTileY() < vistaNivel.getAltoDeNivelEnTiles() - mitadDeZonaVisible - 1) matriz[i][finY] = CONOCIDO_NO_VISIBLE;
		}

		inicioY = jugador->getTileY() - mitadDeZonaVisible;
		finY = jugador->getTileY() + mitadDeZonaVisible;
		if (inicioY < 0) inicioY = 0;
		if (finY >= vistaNivel.getAltoDeNivelEnTiles()) finY = vistaNivel.getAltoDeNivelEnTiles() - 1;

		inicioX = jugador->getTileX() - mitadDeZonaVisible;
		finX = jugador->getTileX() + mitadDeZonaVisible;
		if (inicioX < 0) inicioX = 0;
		if (finX >= vistaNivel.getAnchoDeNivelEnTiles()) finX = vistaNivel.getAnchoDeNivelEnTiles() - 1;

		for (int i = inicioY; i <= finY; i++){
			matriz[finX][i] = VISIBLE;
		}
		
		for (int i = inicioX; i <= finX; i++){
			matriz[i][inicioY] = VISIBLE;
		}
	}

	// se movio a la derecha y abajo
	else if ( (jugador->getTileX() > jugador->getTileXAnterior()) && (jugador->getTileY() > jugador->getTileYAnterior()) ) {

		inicioY = jugador->getTileY() - mitadDeZonaVisible - 1;
		finY = jugador->getTileY() + 1;
		if (inicioY < 0) inicioY = 0;
		if (finY >= vistaNivel.getAltoDeNivelEnTiles()) finY = vistaNivel.getAltoDeNivelEnTiles() - 1;

		inicioX = jugador->getTileX() - mitadDeZonaVisible - 1;
		finX = jugador->getTileX() + 1;
		if (inicioX < 0) inicioX = 0;
		if (finX >= vistaNivel.getAnchoDeNivelEnTiles()) finX = vistaNivel.getAnchoDeNivelEnTiles() - 1;

		
		for (int i = inicioY; i <= finY; i++){
			if (jugador->getTileX() > mitadDeZonaVisible) matriz[inicioX][i] = CONOCIDO_NO_VISIBLE;
		}
		
		for (int i = inicioX; i <= finX; i++){
			if (jugador->getTileY() > mitadDeZonaVisible) matriz[i][inicioY] = CONOCIDO_NO_VISIBLE;
		}

		inicioY = jugador->getTileY() - mitadDeZonaVisible;
		finY = jugador->getTileY() + mitadDeZonaVisible;
		if (inicioY < 0) inicioY = 0;
		if (finY >= vistaNivel.getAltoDeNivelEnTiles()) finY = vistaNivel.getAltoDeNivelEnTiles() - 1;

		inicioX = jugador->getTileX() - mitadDeZonaVisible;
		finX = jugador->getTileX() + mitadDeZonaVisible;
		if (inicioX < 0) inicioX = 0;
		if (finX >= vistaNivel.getAnchoDeNivelEnTiles()) finX = vistaNivel.getAnchoDeNivelEnTiles() - 1;

		for (int i = inicioY; i <= finY; i++){
			matriz[finX][i] = VISIBLE;
		}
		
		for (int i = inicioX; i <= finX; i++){
			matriz[i][finY] = VISIBLE;
		}
	}

	// se movio a la izquierda y arriba
	else if ( (jugador->getTileX() < jugador->getTileXAnterior()) && (jugador->getTileY() < jugador->getTileYAnterior()) ) {

		inicioY = jugador->getTileY() - 1;
		finY = jugador->getTileY() + mitadDeZonaVisible + 1;
		if (inicioY < 0) inicioY = 0;
		if (finY >= vistaNivel.getAltoDeNivelEnTiles()) finY = vistaNivel.getAltoDeNivelEnTiles() - 1;

		inicioX = jugador->getTileX() - 1;
		finX = jugador->getTileX() + mitadDeZonaVisible + 1;
		if (inicioX < 0) inicioX = 0;
		if (finX >= vistaNivel.getAnchoDeNivelEnTiles()) finX = vistaNivel.getAnchoDeNivelEnTiles() - 1;
		
		for (int i = inicioY; i <= finY; i++){
			if (jugador->getTileX() < vistaNivel.getAnchoDeNivelEnTiles() - mitadDeZonaVisible - 1) matriz[finX][i] = CONOCIDO_NO_VISIBLE;
		}
		
		for (int i = inicioX; i <= finX; i++){
			if (jugador->getTileY() < vistaNivel.getAltoDeNivelEnTiles() - mitadDeZonaVisible - 1) matriz[i][finY] = CONOCIDO_NO_VISIBLE;
		}

		inicioY = jugador->getTileY() - mitadDeZonaVisible;
		finY = jugador->getTileY() + mitadDeZonaVisible;
		if (inicioY < 0) inicioY = 0;
		if (finY >= vistaNivel.getAltoDeNivelEnTiles()) finY = vistaNivel.getAltoDeNivelEnTiles() - 1;

		inicioX = jugador->getTileX() - mitadDeZonaVisible;
		finX = jugador->getTileX() + mitadDeZonaVisible;
		if (inicioX < 0) inicioX = 0;
		if (finX >= vistaNivel.getAnchoDeNivelEnTiles()) finX = vistaNivel.getAnchoDeNivelEnTiles() - 1;

		for (int i = inicioY; i <= finY; i++){
			matriz[inicioX][i] = VISIBLE;
		}
		
		for (int i = inicioX; i <= finX; i++){
			matriz[i][inicioY] = VISIBLE;
		}
	}

	// se movio a la izquierda y abajo
	else if ( (jugador->getTileX() < jugador->getTileXAnterior()) && (jugador->getTileY() > jugador->getTileYAnterior()) ) {
		
		inicioY = jugador->getTileY() - mitadDeZonaVisible - 1;
		finY = jugador->getTileY() + 1;
		if (inicioY < 0) inicioY = 0;
		if (finY >= vistaNivel.getAltoDeNivelEnTiles()) finY = vistaNivel.getAltoDeNivelEnTiles() - 1;

		inicioX = jugador->getTileX() - 1;
		finX = jugador->getTileX() + mitadDeZonaVisible + 1;
		if (inicioX < 0) inicioX = 0;
		if (finX >= vistaNivel.getAnchoDeNivelEnTiles()) finX = vistaNivel.getAnchoDeNivelEnTiles() - 1;

		for (int i = inicioY; i <= finY; i++){
			if (jugador->getTileX() < vistaNivel.getAnchoDeNivelEnTiles() - mitadDeZonaVisible - 1) matriz[finX][i] = CONOCIDO_NO_VISIBLE;
		}
		
		for (int i = inicioX; i <= finX; i++){
			if (jugador->getTileY() > mitadDeZonaVisible) matriz[i][inicioY] = CONOCIDO_NO_VISIBLE;
		}

		inicioY = jugador->getTileY() - mitadDeZonaVisible;
		finY = jugador->getTileY() + mitadDeZonaVisible;
		if (inicioY < 0) inicioY = 0;
		if (finY >= vistaNivel.getAltoDeNivelEnTiles()) finY = vistaNivel.getAltoDeNivelEnTiles() - 1;

		inicioX = jugador->getTileX() - mitadDeZonaVisible;
		finX = jugador->getTileX() + mitadDeZonaVisible;
		if (inicioX < 0) inicioX = 0;
		if (finX >= vistaNivel.getAnchoDeNivelEnTiles()) finX = vistaNivel.getAnchoDeNivelEnTiles() - 1;

		for (int i = inicioY; i <= finY; i++){
			matriz[inicioX][i] = VISIBLE;
		}
		
		for (int i = inicioX; i <= finX; i++){
			matriz[i][finY] = VISIBLE;
		}
	}

}

bool VistaLoop::loop(VistaNivel& vistaNivel, char** matriz){
	//Antes de dibujar las entidades me fijo si tengo que refrescar la matriz
	if (vistaNivel.getJugador()->getTileX() > vistaNivel.getJugador()->getTileXAnterior())
				int a = 9;

	if ( (vistaNivel.getJugador()->getTileXAnterior() != vistaNivel.getJugador()->getTileX())
		|| (vistaNivel.getJugador()->getTileYAnterior() != vistaNivel.getJugador()->getTileY()) ) {
			this->refrescarMatriz(vistaNivel,matriz);
	}
	if( this->dibujarEntidades(vistaNivel,matriz) == false) return false;

	return true;
}

bool VistaLoop::dibujarEntidades(VistaNivel& vistaNivel, char** matriz) {
	list<VistaEntidad*> listaDeEntidades = vistaNivel.getListaEntidades();
	list<VistaEntidad*>::iterator it = listaDeEntidades.begin();	
	bool jugadorDibujado = false;

	//grafica los tiles
	vistaNivel.getScroll()->graficar(this->pantalla,matriz);

	//Dibujo las entidades (y el jugador si corresponde)
	
	while (it != listaDeEntidades.end()) {
		VistaEntidad* unaEntidad = *it;
		it++;

		// Si el jugador esta antes que la entidad que voy a dibujar lo dibujo primero
		if (!jugadorDibujado && VistaNivel::ordenadorEntidades(vistaNivel.getJugador(), unaEntidad)) {
			vistaNivel.getJugador()->verificarBordePantalla(vistaNivel.getScroll());
			vistaNivel.getJugador()->setPantalla(this->pantalla);
			if (!vistaNivel.getJugador()->graficar(VISIBLE))
				return false;
			jugadorDibujado = true;
		}

		if (unaEntidad->verificarBordePantalla(vistaNivel.getScroll())) {
			unaEntidad->setPantalla(this->pantalla);						
			bool funciona = unaEntidad->graficar(this->visibilidadDeLaEntidad(unaEntidad,matriz));
			if( funciona == false)
				return false;
		}

	}
	
	// Si no dibuje el jugador lo dibujo ahora
	if (!jugadorDibujado) {
		vistaNivel.getJugador()->verificarBordePantalla(vistaNivel.getScroll());
		vistaNivel.getJugador()->setPantalla(this->pantalla);
		if (!vistaNivel.getJugador()->graficar(VISIBLE))
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

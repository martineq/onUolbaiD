#include "./VistaJuego.h"

VistaJuego::VistaJuego(void){

}

VistaJuego::~VistaJuego(void){
	
	for (int i = 0; i < this->vistaNivel.getAnchoDeNivelEnTiles(); i++)	delete [] this->matriz[i];
	delete [] this->matriz;

}

Observador* VistaJuego::obtenerObservadorJugador(void){
	return this->vistaNivel.obtenerObservadorJugador();
}

Observador* VistaJuego::obtenerObservadorScroll(void){
	return this->vistaNivel.obtenerObservadorScroll();
}

std::list<Observador*> VistaJuego::obtenerObservadoresEntidad(void){
	return this->vistaNivel.obtenerObservadoresEntidad();
}

bool VistaJuego::iniciar(void){
	if( this->vistaFactory.crearVistaNivel(this->vistaNivel,this->vistaLoop) == false ) return false;
	
	//creo la matriz para niebla de guerra
	this->matriz = new char* [this->vistaNivel.getAltoDeNivelEnTiles()];
	for (int i = 0; i < this->vistaNivel.getAltoDeNivelEnTiles(); i++) {
		this->matriz[i] = new char [this->vistaNivel.getAnchoDeNivelEnTiles()];
	}

	//inicializo la matriz con 0 excepto alrededor del personaje la zona visible de 5x5 es con 2.
	for (int i= 0; i < this->vistaNivel.getAltoDeNivelEnTiles(); i++) {
		for (int j = 0; j < this->vistaNivel.getAnchoDeNivelEnTiles(); j++) {
			this->matriz[i][j] = NO_CONOCIDO;
		}
	}
	
	int zonaVisible = 5; 
	int k = (int)zonaVisible/2;
	int inicioX = this->vistaNivel.getJugador()->getTileX() - k;
	int finX = this->vistaNivel.getJugador()->getTileX() + k;		
	int inicioY = this->vistaNivel.getJugador()->getTileY() - k;
	int finY = this->vistaNivel.getJugador()->getTileY() + k;	
	int posicionDelJugadorX = this->vistaNivel.getJugador()->getTileX();
	int posicionDelJugadorY = this->vistaNivel.getJugador()->getTileY();

	if ((posicionDelJugadorX - k) < 0) {			
		inicioX = 0;
	}

	if ((posicionDelJugadorX + k) > vistaNivel.getAnchoDeNivelEnTiles()) {			
		finX = vistaNivel.getAnchoDeNivelEnTiles();
	}

	if ((posicionDelJugadorY - k) < 0) {			
		inicioY = 0;
	}

	if ((posicionDelJugadorY + k) > vistaNivel.getAltoDeNivelEnTiles()) {			
		finY = vistaNivel.getAltoDeNivelEnTiles();
	}	
	
	for (int i = inicioX; i <=  finX; i++){
		for (int j = inicioY; j <= finY; j++){
			this->matriz[i][j] = VISIBLE;
		}
	}
	
//	if( this->vistaLoop.levantarFondo(this->vistaNivel.getAltoNivel(),this->vistaNivel.getAnchoNivel()) == false ) return false;
	return true;
}

bool VistaJuego::loop(){
	return this->vistaLoop.loop(this->vistaNivel,this->matriz);
}

void VistaJuego::destruirEntidades(){
	this->vistaNivel.destruirEntidadesYScroll();
}
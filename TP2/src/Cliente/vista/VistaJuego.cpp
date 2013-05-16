#include "./VistaJuego.h"

VistaJuego::VistaJuego(void){
	this->matriz = NULL;
}

VistaJuego::~VistaJuego(void){

	if( this->matriz != NULL ){
		for (int i = 0; i < this->vistaNivel.getAnchoDeNivelEnTiles(); i++)	delete [] this->matriz[i];
		delete [] this->matriz;
	}

}

bool VistaJuego::iniciar(SocketCliente* pSocket,ControladorEvento* evento,std::string mote,std::string personaje){
	ImageLoader::getInstance().iniciarSDL();
	if( this->vistaFactory.crearNivel(this->vistaNivel,evento,pSocket,this->vistaLoop.getPunteroPantalla(),this->vistaLoop.getPunteroProxy(),mote,personaje) == false ) return false;
	
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
	
	// TODO: Borrar todo el código que no se usa mas de esta clase 

	//int zonaVisible = 5; 
	//int k = (int)zonaVisible/2;
	int k = (int) ZONA_VISIBLE / 2;
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
	
	return true;
}

void VistaJuego::cargarMatriz(){
	std::string matriz = this->vistaFactory.getMatriz();
	for (int i = 0; i < this->vistaNivel.getAltoDeNivelEnTiles(); i++){
		for (int j = 0; j < this->vistaNivel.getAnchoDeNivelEnTiles(); j++){
			int fila = i * this->vistaNivel.getAnchoDeNivelEnTiles();
			this->matriz[j][i] = matriz[fila+j];
		}	
	}
}

bool VistaJuego::loop(){
	return this->vistaLoop.loop(this->vistaNivel,this->vistaFactory, this->matriz);
}

VistaNivel* VistaJuego::getVistaNivel() {
	return &this->vistaNivel;
}

void VistaJuego::destruirEntidades(){
	this->vistaNivel.destruirEntidadesYScroll();
}

void VistaJuego::asignarChat(VistaChat* vistaChat) {
	this->vistaLoop.asignarChat(vistaChat);
}

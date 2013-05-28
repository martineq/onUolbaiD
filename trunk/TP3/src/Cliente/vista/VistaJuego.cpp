#include "./VistaJuego.h"

VistaJuego::VistaJuego(void){
	this->estadoNivel = NULL;
}

VistaJuego::~VistaJuego(void){

	if (this->estadoNivel != NULL)
		delete this->estadoNivel;
}

bool VistaJuego::iniciar(SocketCliente* pSocket,ControladorEvento* evento,std::string mote,std::string personaje,bool singlePlayer){
	ImageLoader::getInstance().iniciarSDL();
	if( this->vistaFactory.crearNivel(this->vistaNivel,evento,pSocket,this->vistaLoop.getPunteroPantalla(),this->vistaLoop.getPunteroProxy(),mote,personaje,singlePlayer) == false ) return false;
	
	this->estadoNivel = new EstadoNivel(this->vistaNivel.getAltoDeNivelEnTiles(), this->vistaNivel.getAnchoDeNivelEnTiles(), this->vistaNivel.getJugador()->getTileX(), this->vistaNivel.getJugador()->getTileY());
	return true;
}

void VistaJuego::cargarMatriz(){
	this->estadoNivel->setMatriz(this->vistaFactory.getMatriz());
}

bool VistaJuego::loop(){
	return this->vistaLoop.loop(this->vistaNivel,this->vistaFactory, this->estadoNivel);
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

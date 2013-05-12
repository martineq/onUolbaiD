#include "./VistaJuego.h"

VistaJuego::VistaJuego(void){

}

VistaJuego::~VistaJuego(void){

}

bool VistaJuego::iniciar(SocketCliente* pSocket,ControladorEvento* evento){
	ImageLoader::getInstance().iniciarSDL();
	if( this->vistaFactory.crearNivel(this->vistaNivel,evento,pSocket,this->vistaLoop.getPunteroPantalla(),this->vistaLoop.getPunteroProxy()) == false ) return false;
	return true;
}

bool VistaJuego::loop(){
	return this->vistaLoop.loop(this->vistaNivel,this->vistaFactory);
}

void VistaJuego::destruirEntidades(){
	this->vistaNivel.destruirEntidadesYScroll();
}
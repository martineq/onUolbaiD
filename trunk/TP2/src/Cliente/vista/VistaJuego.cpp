#include "./VistaJuego.h"

VistaJuego::VistaJuego(void){

}

VistaJuego::~VistaJuego(void){

}

bool VistaJuego::iniciar(SocketCliente* pSocket,ControladorEvento* evento,std::string mote,std::string personaje){
	ImageLoader::getInstance().iniciarSDL();
	if( this->vistaFactory.crearNivel(this->vistaNivel,evento,pSocket,this->vistaLoop.getPunteroPantalla(),this->vistaLoop.getPunteroProxy(),mote,personaje) == false ) return false;
	return true;
}

bool VistaJuego::loop(){
	return this->vistaLoop.loop(this->vistaNivel,this->vistaFactory);
}

void VistaJuego::destruirEntidades(){
	this->vistaNivel.destruirEntidadesYScroll();
}
#include "./VistaJuego.h"

VistaJuego::VistaJuego(void){

}

VistaJuego::~VistaJuego(void){

}

bool VistaJuego::iniciar(SocketCliente* pSocket,ControladorEvento* evento){
	if( this->vistaFactory.crearNivel(this->vistaNivel,this->vistaLoop,evento,pSocket) == false ) return false;
	return true;
}

bool VistaJuego::loop(){
	return this->vistaLoop.loop(this->vistaNivel);
}

void VistaJuego::destruirEntidades(){
	this->vistaNivel.destruirEntidadesYScroll();
}
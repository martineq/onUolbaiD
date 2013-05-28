#include "HiloSinglePlayer.h"


HiloSinglePlayer::HiloSinglePlayer(void){

}


HiloSinglePlayer::~HiloSinglePlayer(void){

}

// Acá activo el hilo y hago el start
void HiloSinglePlayer::correrSinglePlayer(HiloSinglePlayer::stParametrosSinglePlayer parametrosRun){
	this->parametrosRun = parametrosRun;
	this->start(&(this->parametrosRun)); 
	return void();
}

void* HiloSinglePlayer::run(void* parametrosRun){
	HiloSinglePlayer::stParametrosSinglePlayer* parametros = ((HiloSinglePlayer::stParametrosSinglePlayer*)parametrosRun);

	if( parametros->esServidor == true ){
		parametros->pServidor->correrJuegoSinglePlayer();
	}else{
		if( parametros->pCliente->correrJuegoSinglePlayer(parametros->mote,parametros->personaje) == false ){
			Log::getInstance().log(1,__FILE__,__LINE__,"Error al correr el juego en modo Cliente");
		}
	}

	return NULL;
}
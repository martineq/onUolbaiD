#include "VistaMusica.h"

VistaMusica::VistaMusica() {
	this->music = NULL;	
	this->atacando = NULL;
	this->sufrioDanio = NULL;
	this->murioItem = NULL;
	this->atacadoConEscudo = NULL;
	this->magia = NULL;
}

VistaMusica::VistaMusica(const VistaMusica&){	
}

bool VistaMusica::iniciar(){
	//inicia Mixer
	Mix_Init( MIX_INIT_MP3 );
    if ( (Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 )  == -1) )  return false;
	
	//Carga de sonidos
	this->music = Mix_LoadMUS( "./sounds/musica.wav" );
	this->atacando = Mix_LoadWAV( "./sounds/deleted.wav" );
	this->sufrioDanio = Mix_LoadWAV( "./sounds/adios.wav" );
	this->murioElJugador = Mix_LoadWAV( "./sounds/pigman.wav" );
	this->murioElEnemigo = Mix_LoadWAV( "./sounds/uh.wav" );
	this->murioItem = Mix_LoadWAV( "./sounds/uh2.wav" );
	this->atacadoConEscudo = Mix_LoadWAV( "./sounds/yourmom.wav" );
	this->magia = Mix_LoadWAV( "./sounds/updere.wav" );
	
	return true;
}

void VistaMusica::playTheMusic(){
	//if( !Mix_PlayingMusic() ) 
	//	   Mix_PlayMusic( music, -1 );
}

void VistaMusica::stopTheMusic(){
	if( Mix_PlayingMusic() ) 
		Mix_HaltMusic();
}

void VistaMusica::pauseTheMusic(){
	if( Mix_PlayingMusic() ) 
		Mix_PauseMusic();                 
}

void VistaMusica::resumeTheMusic(){
	if( Mix_PausedMusic() == 1 )            				
		Mix_ResumeMusic();    
}

void VistaMusica::atacar(){
	Mix_PlayChannel( -1, atacando, 0 );
}

void VistaMusica::recibioUnGolpe(){
	Mix_PlayChannel( -1, sufrioDanio, 0 );
}

void VistaMusica::murioJugador(){
	Mix_PlayChannel( -1, murioElJugador, 0 );
}

void VistaMusica::murioEnemigo(){
	Mix_PlayChannel( -1, murioElEnemigo, 0 );
}

void VistaMusica::itemTomado(){
	Mix_PlayChannel( -1, murioItem, 0 );
}

void VistaMusica::conEscudo(){
	Mix_PlayChannel( -1, atacadoConEscudo, 0 );
}

void VistaMusica::gastoMagia(){
	Mix_PlayChannel( -1, magia, 0 );
}

VistaMusica::~VistaMusica() {
	Mix_FreeMusic( music );
	Mix_FreeChunk( atacando );
	Mix_FreeChunk( sufrioDanio );
	Mix_FreeChunk( murioElJugador );
	Mix_FreeChunk( murioElEnemigo );
	Mix_FreeChunk( murioItem );
	Mix_FreeChunk( atacadoConEscudo );
	Mix_FreeChunk( magia );
}


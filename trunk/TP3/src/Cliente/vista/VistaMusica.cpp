#include "VistaMusica.h"

VistaMusica::VistaMusica() {
	this->music = NULL;	
	this->atacando = NULL;
}

VistaMusica::VistaMusica(const VistaMusica&){	
}

bool VistaMusica::iniciar(){
	//inicia Mixer
	Mix_Init( MIX_INIT_MP3 );
    if ( (Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 )  == -1) )  return false;
	
	//Carga de sonidos
	music = Mix_LoadMUS( "./sounds/musica.wav" );
	atacando = Mix_LoadWAV( "./sounds/deleted.wav" );
	
	return true;
}

void VistaMusica::playTheMusic(){
	if( !Mix_PlayingMusic() ) 
		   Mix_PlayMusic( music, -1 );
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


VistaMusica::~VistaMusica() {
	Mix_FreeMusic( music );
	Mix_FreeChunk( atacando );
}
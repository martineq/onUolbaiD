#include "Temporizador.h"

Temporizador::Temporizador(){
    ticInicial = 0;
    ticPausado = 0;
    pausado = false;
    comenzado = false;

	// Arranca comenzado
	Temporizador::comenzar();

}

Temporizador::~Temporizador(){
 
}

void Temporizador::comenzar(){
    comenzado = true;
    pausado = false;
    ticInicial = SDL_GetTicks();
}

void Temporizador::parar(){
    comenzado = false;
    pausado = false;
}

void Temporizador::pausar(){
    // Si arrancó y no está pausado
    if( ( comenzado == true ) && ( pausado == false ) ){
        pausado = true;
        ticPausado = SDL_GetTicks() - ticInicial;
    }
}

void Temporizador::sacarPausa(){
    if( pausado == true ){
        pausado = false;
        ticInicial = SDL_GetTicks() - ticPausado;
        ticPausado = 0;
    }
}

void Temporizador::crearDelay(long milisegundos){
	SDL_Delay(milisegundos);
}

unsigned long Temporizador::obtenerTics(){
    if( comenzado == true ){
        if( pausado == true ){
            return ticPausado;
        }else{
            return SDL_GetTicks() - ticInicial;
        }
    }

    return 0;	// Si el Temporizador no comenzó devuelvo cero
}

bool Temporizador::estaComenzado(){
    return comenzado;
}

bool Temporizador::estaPausado(){
    return pausado;
}
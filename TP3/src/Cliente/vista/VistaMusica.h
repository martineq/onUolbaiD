#pragma once

#include <SDL_mixer.h>

class VistaMusica {
	private:
		VistaMusica();
		VistaMusica(const VistaMusica&);
		VistaMusica& operator =(const VistaMusica&);		

		//Musica
		Mix_Music *music;

		//FX
		Mix_Chunk *atacando;		
		Mix_Chunk *sufrioDanio;
		Mix_Chunk *murioElJugador;
		Mix_Chunk *murioElEnemigo;
		Mix_Chunk *murioItem;
		Mix_Chunk *atacadoConEscudo;
		Mix_Chunk *magia;
		Mix_Chunk *bomba;
	public:	
		static VistaMusica& getInstance();
		virtual ~VistaMusica();
		void playTheMusic();
		void pauseTheMusic();
		void resumeTheMusic();
		void stopTheMusic();
		void atacar();
		void recibioUnGolpe();
		void murioJugador();		
		void murioEnemigo();
		void itemTomado();
		void conEscudo();
		void gastoMagia();
		void gastoBomba();
		bool iniciar();
};

inline VistaMusica& VistaMusica::getInstance(){
   static VistaMusica object;
   return object;
}

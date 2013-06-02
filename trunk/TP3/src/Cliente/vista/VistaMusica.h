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
	public:	
		static VistaMusica& getInstance();
		virtual ~VistaMusica();
		void playTheMusic();
		void pauseTheMusic();
		void resumeTheMusic();
		void stopTheMusic();
		void atacar();
		bool iniciar();
};

inline VistaMusica& VistaMusica::getInstance(){
   static VistaMusica object;
   return object;
}

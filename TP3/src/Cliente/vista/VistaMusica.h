#pragma once

#include <iostream>
#include <SDL_mixer.h>
#include "../../utils/Constantes/Constantes.h"

class VistaMusica {
	private:
		VistaMusica();
		VistaMusica(const VistaMusica&);
		VistaMusica& operator =(const VistaMusica&);		

		//Musica
		Mix_Music *MusicaFondo1;
		Mix_Music *MusicaFondo2;
		Mix_Music *MusicaFondo3;
		Mix_Music *MusicaFondo4;

		//FX
		Mix_Chunk *BombaExplota;
		Mix_Chunk *BombaLanzada;
		Mix_Chunk *Carnicero_ataca;
		Mix_Chunk *Carnicero_muere;
		Mix_Chunk *Carnicero_recibeGolpe;
		Mix_Chunk *Carnicero_rie;
		Mix_Chunk *EnemigoA_ataca;
		Mix_Chunk *EnemigoA_muere;
		Mix_Chunk *EnemigoA_recibeGolpe;
		Mix_Chunk *EnemigoB_ataca;
		Mix_Chunk *EnemigoB_muere;
		Mix_Chunk *EnemigoB_recibeGolpe;
		Mix_Chunk *EnemigoC_ataca;
		Mix_Chunk *EnemigoC_muere;
		Mix_Chunk *EnemigoC_recibeGolpe;
		Mix_Chunk *EscudoBloqueo;
		Mix_Chunk *GastoMagia;
		Mix_Chunk *Golem_ataca;
		Mix_Chunk *Golem_muere;
		Mix_Chunk *Golem_recibeGolpe;
		Mix_Chunk *HechizoHieloLanzado;
		Mix_Chunk *ItemBomba;
		Mix_Chunk *ItemBotella;
		Mix_Chunk *ItemCorazon;
		Mix_Chunk *ItemEscudo;
		Mix_Chunk *ItemEspada;
		Mix_Chunk *ItemGolem;
		Mix_Chunk *ItemHechizoHielo;
		Mix_Chunk *ItemLampara;
		Mix_Chunk *ItemMapa;
		Mix_Chunk *ItemZapato;
		Mix_Chunk *JugadorHombre_ataca;
		Mix_Chunk *JugadorHombre_muere;
		Mix_Chunk *JugadorHombre_recibeGolpe;
		Mix_Chunk *JugadorMujer_ataca;
		Mix_Chunk *JugadorMujer_muere;
		Mix_Chunk *JugadorMujer_RecibeGolpe;


	public:	
		static VistaMusica& getInstance();
		virtual ~VistaMusica();
		
		// Musica de fondo
		void playTheMusic();
		void pauseTheMusic();
		void resumeTheMusic();
		void stopTheMusic();

		// Acciones
		void atacar(std::string nombreEntidad);
		void recibioUnGolpe(std::string nombreEntidad);
		void murioJugador(std::string nombreEntidad);		
		void murioEnemigo(std::string nombreEntidad);
		void itemTomado(std::string nombreEntidad);
		void sonidoExtra(std::string nombreEntidad);
		void conEscudo();
		void gastoMagia();
		void gastoBomba();
		bool iniciar();
};

inline VistaMusica& VistaMusica::getInstance(){
   static VistaMusica object;
   return object;
}

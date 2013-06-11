#include "VistaMusica.h"

VistaMusica::VistaMusica() {
	this->BombaExplota = NULL;
	this->BombaLanzada = NULL;
	this->Carnicero_ataca = NULL;
	this->Carnicero_muere = NULL;
	this->Carnicero_recibeGolpe = NULL;
	this->Carnicero_rie = NULL;
	this->EnemigoA_ataca = NULL;
	this->EnemigoA_muere = NULL;
	this->EnemigoA_recibeGolpe = NULL;
	this->EnemigoB_ataca = NULL;
	this->EnemigoB_muere = NULL;
	this->EnemigoB_recibeGolpe = NULL;
	this->EnemigoC_ataca = NULL;
	this->EnemigoC_muere = NULL;
	this->EnemigoC_recibeGolpe = NULL;
	this->EscudoBloqueo = NULL;
	this->GastoMagia = NULL;
	this->Golem_ataca = NULL;
	this->Golem_muere = NULL;
	this->Golem_recibeGolpe = NULL;
	this->HechizoHieloLanzado = NULL;
	this->ItemBomba = NULL;
	this->ItemBotella = NULL;
	this->ItemCorazon = NULL;
	this->ItemEscudo = NULL;
	this->ItemEspada = NULL;
	this->ItemGolem = NULL;
	this->ItemHechizoHielo = NULL;
	this->ItemLampara = NULL;
	this->ItemMapa = NULL;
	this->ItemZapato = NULL;
	this->JugadorHombre_ataca = NULL;
	this->JugadorHombre_muere = NULL;
	this->JugadorHombre_recibeGolpe = NULL;
	this->JugadorMujer_ataca = NULL;
	this->JugadorMujer_muere = NULL;
	this->JugadorMujer_RecibeGolpe = NULL;
	this->MusicaFondo1 = NULL;
	this->MusicaFondo2 = NULL;
	this->MusicaFondo3 = NULL;
	this->MusicaFondo4 = NULL;
}

VistaMusica::VistaMusica(const VistaMusica&){	
}

bool VistaMusica::iniciar(){
	//inicia Mixer
	Mix_Init( MIX_INIT_MP3 );
    if ( (Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 )  == -1) )  return false;
	
	// Musica de fondo
	this->MusicaFondo1 = Mix_LoadMUS( "./sounds/MusicaFondo1.wav" );
	this->MusicaFondo2 = Mix_LoadMUS( "./sounds/MusicaFondo2.wav" );
	this->MusicaFondo3 = Mix_LoadMUS( "./sounds/MusicaFondo3.wav" );
	this->MusicaFondo4 = Mix_LoadMUS( "./sounds/MusicaFondo4.wav" );

	//Carga de sonidos
	this->BombaExplota = Mix_LoadWAV( "./sounds/BombaExplota.wav" );
	this->BombaLanzada = Mix_LoadWAV( "./sounds/BombaLanzada.wav" );
	this->Carnicero_ataca = Mix_LoadWAV( "./sounds/Carnicero_ataca.wav" );
	this->Carnicero_muere = Mix_LoadWAV( "./sounds/Carnicero_muere.wav" );
	this->Carnicero_recibeGolpe = Mix_LoadWAV( "./sounds/Carnicero_recibeGolpe.wav" );
	this->Carnicero_rie = Mix_LoadWAV( "./sounds/Carnicero_rie.wav" );
	this->EnemigoA_ataca = Mix_LoadWAV( "./sounds/EnemigoA_ataca.wav" );
	this->EnemigoA_muere = Mix_LoadWAV( "./sounds/EnemigoA_muere.wav" );
	this->EnemigoA_recibeGolpe = Mix_LoadWAV( "./sounds/EnemigoA_recibeGolpe.wav" );
	this->EnemigoB_ataca = Mix_LoadWAV( "./sounds/EnemigoB_ataca.wav" );
	this->EnemigoB_muere = Mix_LoadWAV( "./sounds/EnemigoB_muere.wav" );
	this->EnemigoB_recibeGolpe = Mix_LoadWAV( "./sounds/EnemigoB_recibeGolpe.wav" );
	this->EnemigoC_ataca = Mix_LoadWAV( "./sounds/EnemigoC_ataca.wav" );
	this->EnemigoC_muere = Mix_LoadWAV( "./sounds/EnemigoC_muere.wav" );
	this->EnemigoC_recibeGolpe = Mix_LoadWAV( "./sounds/EnemigoC_recibeGolpe.wav" );
	this->EscudoBloqueo = Mix_LoadWAV( "./sounds/EscudoBloqueo.wav" );
	this->GastoMagia = Mix_LoadWAV( "./sounds/GastoMagia.wav" );
	this->Golem_ataca = Mix_LoadWAV( "./sounds/Golem_ataca.wav" );
	this->Golem_muere = Mix_LoadWAV( "./sounds/Golem_muere.wav" );
	this->Golem_recibeGolpe = Mix_LoadWAV( "./sounds/Golem_recibeGolpe.wav" );
	this->HechizoHieloLanzado = Mix_LoadWAV( "./sounds/HechizoHieloLanzado.wav" );
	this->ItemBomba = Mix_LoadWAV( "./sounds/ItemBomba.wav" );
	this->ItemBotella = Mix_LoadWAV( "./sounds/ItemBotella.wav" );
	this->ItemCorazon = Mix_LoadWAV( "./sounds/ItemCorazon.wav" );
	this->ItemEscudo = Mix_LoadWAV( "./sounds/ItemEscudo.wav" );
	this->ItemEspada = Mix_LoadWAV( "./sounds/ItemEspada.wav" );
	this->ItemGolem = Mix_LoadWAV( "./sounds/ItemGolem.wav" );
	this->ItemHechizoHielo = Mix_LoadWAV( "./sounds/ItemHechizoHielo.wav" );
	this->ItemLampara = Mix_LoadWAV( "./sounds/ItemLampara.wav" );
	this->ItemMapa = Mix_LoadWAV( "./sounds/ItemMapa.wav" );
	this->ItemZapato = Mix_LoadWAV( "./sounds/ItemZapato.wav" );
	this->JugadorHombre_ataca = Mix_LoadWAV( "./sounds/JugadorHombre_ataca.wav" );
	this->JugadorHombre_muere = Mix_LoadWAV( "./sounds/JugadorHombre_muere.wav" );
	this->JugadorHombre_recibeGolpe = Mix_LoadWAV( "./sounds/JugadorHombre_recibeGolpe.wav" );
	this->JugadorMujer_ataca = Mix_LoadWAV( "./sounds/JugadorMujer_ataca.wav" );
	this->JugadorMujer_muere = Mix_LoadWAV( "./sounds/JugadorMujer_muere.wav" );
	this->JugadorMujer_RecibeGolpe = Mix_LoadWAV( "./sounds/JugadorMujer_RecibeGolpe.wav" );

	return true;
}

void VistaMusica::playTheMusic(){
	if( !Mix_PlayingMusic() ){
		// Elegir una de las cuatro
	//	   Mix_PlayMusic( MusicaFondo1 , -1 );
		   Mix_PlayMusic( MusicaFondo2 , -1 );
	//	   Mix_PlayMusic( MusicaFondo3 , -1 );
	//	   Mix_PlayMusic( MusicaFondo4 , -1 );
	}
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

void VistaMusica::atacar(std::string nombreEntidad){
	if ( nombreEntidad.compare(STRING_QUEEN) == 0 ){ Mix_PlayChannel( -1, JugadorMujer_ataca , 0 );
	}else if ( nombreEntidad.compare(STRING_KNIGHT) == 0 ){ Mix_PlayChannel( -1, JugadorHombre_ataca , 0 );
	}else if ( nombreEntidad.compare(STRING_VLAD) == 0 ){ Mix_PlayChannel( -1, JugadorHombre_ataca , 0 );
	}else if ( nombreEntidad.compare(STRING_BJORN) == 0 ){ Mix_PlayChannel( -1, JugadorHombre_ataca , 0 );
	}else if ( nombreEntidad.compare(ENTIDAD_GOLEM) == 0 ){ Mix_PlayChannel( -1, Golem_ataca , 0 );
	}else if ( nombreEntidad.compare(STRING_CARNICERO) == 0 ){ Mix_PlayChannel( -1, Carnicero_ataca , 0 );
	}else if ( nombreEntidad.compare(STRING_ENEMIGO_A) == 0 ){ Mix_PlayChannel( -1, EnemigoA_ataca , 0 );
	}else if ( nombreEntidad.compare(STRING_ENEMIGO_B) == 0 ){ Mix_PlayChannel( -1, EnemigoB_ataca , 0 );
	}else if ( nombreEntidad.compare(STRING_ENEMIGO_C) == 0 ){ Mix_PlayChannel( -1, EnemigoC_ataca , 0 );
	}else if ( nombreEntidad.compare(STRING_BOMBA) == 0 ){Mix_PlayChannel( -1, BombaExplota , 0 );
	}else if ( nombreEntidad.compare(STRING_HECHIZO_HIELO) == 0 ){Mix_PlayChannel( -1, HechizoHieloLanzado, 0 );
	}else{  }
}

void VistaMusica::recibioUnGolpe(std::string nombreEntidad){
	if ( nombreEntidad.compare(STRING_QUEEN) == 0 ){ Mix_PlayChannel( -1, JugadorMujer_RecibeGolpe , 0 );
	}else if ( nombreEntidad.compare(STRING_KNIGHT) == 0 ){ Mix_PlayChannel( -1, JugadorHombre_recibeGolpe , 0 );
	}else if ( nombreEntidad.compare(STRING_VLAD) == 0 ){ Mix_PlayChannel( -1, JugadorHombre_recibeGolpe , 0 );
	}else if ( nombreEntidad.compare(STRING_BJORN) == 0 ){ Mix_PlayChannel( -1, JugadorHombre_recibeGolpe , 0 );
	}else if ( nombreEntidad.compare(ENTIDAD_GOLEM) == 0 ){ Mix_PlayChannel( -1, Golem_recibeGolpe , 0 );
	}else if ( nombreEntidad.compare(STRING_CARNICERO) == 0 ){ Mix_PlayChannel( -1, Carnicero_recibeGolpe , 0 );
	}else if ( nombreEntidad.compare(STRING_ENEMIGO_A) == 0 ){ Mix_PlayChannel( -1, EnemigoA_recibeGolpe , 0 );
	}else if ( nombreEntidad.compare(STRING_ENEMIGO_B) == 0 ){ Mix_PlayChannel( -1, EnemigoB_recibeGolpe , 0 );
	}else if ( nombreEntidad.compare(STRING_ENEMIGO_C) == 0 ){ Mix_PlayChannel( -1, EnemigoC_recibeGolpe , 0 );
	}else{  }
}

void VistaMusica::murioJugador(std::string nombreEntidad){
	if ( nombreEntidad.compare(STRING_QUEEN) == 0 ){ Mix_PlayChannel( -1, JugadorMujer_muere , 0 );
	}else if ( nombreEntidad.compare(STRING_KNIGHT) == 0 ){ Mix_PlayChannel( -1, JugadorHombre_muere , 0 );
	}else if ( nombreEntidad.compare(STRING_VLAD) == 0 ){ Mix_PlayChannel( -1, JugadorHombre_muere , 0 );
	}else if ( nombreEntidad.compare(STRING_BJORN) == 0 ){ Mix_PlayChannel( -1, JugadorHombre_muere , 0 );
	}else{  }
}

void VistaMusica::murioEnemigo(std::string nombreEntidad){
	if ( nombreEntidad.compare(ENTIDAD_GOLEM) == 0 ){ Mix_PlayChannel( -1, Golem_muere , 0 );
	}else if ( nombreEntidad.compare(STRING_CARNICERO) == 0 ){ Mix_PlayChannel( -1, Carnicero_muere , 0 );
	}else if ( nombreEntidad.compare(STRING_ENEMIGO_A) == 0 ){ Mix_PlayChannel( -1, EnemigoA_muere , 0 );
	}else if ( nombreEntidad.compare(STRING_ENEMIGO_B) == 0 ){ Mix_PlayChannel( -1, EnemigoB_muere , 0 );
	}else if ( nombreEntidad.compare(STRING_ENEMIGO_C) == 0 ){ Mix_PlayChannel( -1, EnemigoC_muere , 0 );
	}else if ( nombreEntidad.compare(STRING_QUEEN) == 0 ){ Mix_PlayChannel( -1, JugadorMujer_muere , 0 );
	}else if ( nombreEntidad.compare(STRING_KNIGHT) == 0 ){ Mix_PlayChannel( -1, JugadorHombre_muere , 0 );
	}else if ( nombreEntidad.compare(STRING_VLAD) == 0 ){ Mix_PlayChannel( -1, JugadorHombre_muere , 0 );
	}else if ( nombreEntidad.compare(STRING_BJORN) == 0 ){ Mix_PlayChannel( -1, JugadorHombre_muere , 0 );
	}else{  }
}

void VistaMusica::itemTomado(std::string nombreEntidad){
	if ( nombreEntidad.compare(STRING_CORAZON) == 0 ){ Mix_PlayChannel( -1, ItemCorazon , 0 );
	}else if ( nombreEntidad.compare(STRING_ESCUDO) == 0 ){ Mix_PlayChannel( -1, ItemEscudo , 0 );
	}else if ( nombreEntidad.compare(STRING_ZAPATO) == 0 ){ Mix_PlayChannel( -1, ItemZapato , 0 );
	}else if ( nombreEntidad.compare(STRING_BOTELLA) == 0 ){ Mix_PlayChannel( -1, ItemBotella , 0 );
	}else if ( nombreEntidad.compare(STRING_LAMPARA) == 0 ){ Mix_PlayChannel( -1, ItemLampara , 0 );
	}else if ( nombreEntidad.compare(STRING_MAPA) == 0 ){ Mix_PlayChannel( -1, ItemMapa , 0 );
	}else if ( nombreEntidad.compare(STRING_ESPADA) == 0 ){ Mix_PlayChannel( -1, ItemEspada , 0 );
	}else if ( nombreEntidad.compare(STRING_HECHIZO_HIELO) == 0 ){ Mix_PlayChannel( -1, ItemHechizoHielo , 0 );
	}else if ( nombreEntidad.compare(STRING_BOMBA) == 0 ){ Mix_PlayChannel( -1, ItemBomba , 0 );
	}else if ( nombreEntidad.compare(STRING_GOLEM) == 0 ){ Mix_PlayChannel( -1, ItemGolem , 0 );
	}else{  }
}

void VistaMusica::sonidoExtra(std::string nombreEntidad){
	if ( nombreEntidad.compare(STRING_CARNICERO) == 0 ){ Mix_PlayChannel( -1, Carnicero_rie , 0 );
	}else{  }
}

void VistaMusica::conEscudo(){
	Mix_PlayChannel( -1, EscudoBloqueo, 0 );
}

void VistaMusica::gastoMagia(){
	Mix_PlayChannel( -1, GastoMagia, 0 );
}

void VistaMusica::gastoBomba(){
	Mix_PlayChannel( -1, BombaLanzada, 0 );
}

VistaMusica::~VistaMusica() {
		Mix_FreeMusic(MusicaFondo1);
		Mix_FreeMusic(MusicaFondo2);
		Mix_FreeMusic(MusicaFondo3);
		Mix_FreeMusic(MusicaFondo4);
		Mix_FreeChunk(BombaExplota);
		Mix_FreeChunk(BombaLanzada);
		Mix_FreeChunk(Carnicero_ataca);
		Mix_FreeChunk(Carnicero_muere);
		Mix_FreeChunk(Carnicero_recibeGolpe);
		Mix_FreeChunk(Carnicero_rie);
		Mix_FreeChunk(EnemigoA_ataca);
		Mix_FreeChunk(EnemigoA_muere);
		Mix_FreeChunk(EnemigoA_recibeGolpe);
		Mix_FreeChunk(EnemigoB_ataca);
		Mix_FreeChunk(EnemigoB_muere);
		Mix_FreeChunk(EnemigoB_recibeGolpe);
		Mix_FreeChunk(EnemigoC_ataca);
		Mix_FreeChunk(EnemigoC_muere);
		Mix_FreeChunk(EnemigoC_recibeGolpe);
		Mix_FreeChunk(EscudoBloqueo);
		Mix_FreeChunk(Golem_ataca);
		Mix_FreeChunk(Golem_muere);
		Mix_FreeChunk(Golem_recibeGolpe);
		Mix_FreeChunk(HechizoHieloLanzado);
		Mix_FreeChunk(ItemBomba);
		Mix_FreeChunk(ItemBotella);
		Mix_FreeChunk(ItemCorazon);
		Mix_FreeChunk(ItemEscudo);
		Mix_FreeChunk(ItemEspada);
		Mix_FreeChunk(ItemGolem);
		Mix_FreeChunk(ItemHechizoHielo);
		Mix_FreeChunk(ItemLampara);
		Mix_FreeChunk(ItemMapa);
		Mix_FreeChunk(ItemZapato);
		Mix_FreeChunk(JugadorHombre_ataca);
		Mix_FreeChunk(JugadorHombre_muere);
		Mix_FreeChunk(JugadorHombre_recibeGolpe);
		Mix_FreeChunk(JugadorMujer_ataca);
		Mix_FreeChunk(JugadorMujer_muere);
		Mix_FreeChunk(JugadorMujer_RecibeGolpe);
		Mix_CloseAudio();
		Mix_Quit();
}

#include "./Administrador.h"

Administrador::Administrador(void){
	this->modoServidor = false;
	this->modoUnJugador = false;
	this->servidor = NULL;
	this->cliente = NULL;
}

Administrador::~Administrador(void){
	if( this->servidor != NULL){
		this->servidor->destruirEntidades();
		delete this->servidor;
		this->servidor = NULL;
	}

	if( this->cliente != NULL){
		this->cliente->destruirEntidades();
		delete this->cliente;
		this->cliente = NULL;
	}
}

void Administrador::correrJuego(std::string mote,std::string personaje){

	//this->menuLineaComandos();

	if (this->nuevoMenu1() == false) return;

	if( this->modoUnJugador == true ){

		// Inicio el modo para un jugador
		this->correrSinglePlayer(mote,personaje);

	}else{
		if( this->modoServidor == true ){
			this->servidor = new Servidor();
			if( this->servidor->correrJuego() == false ){
				Log::getInstance().log(1,__FILE__,__LINE__,"Error al correr el juego en modo Servidor");
			}
		}else{
			this->cliente = new Cliente();
			if( this->cliente->correrJuego(mote,personaje) == false ){
			Log::getInstance().log(1,__FILE__,__LINE__,"Error al correr el juego en modo Cliente");
			}	
		}
	}

	return void();
}

void Administrador::menuLineaComandos(void){

	std::string opc;

	// Pregunto por el modo de un jugador
	std::cout << "Ingrese \"s\" para modo Un Jugador, otra para Multijugador " << std::endl;
	getline (std::cin,opc);
	if( opc.compare("s") == 0 || opc.compare("S") == 0 ){
		this->modoUnJugador = true;
		std::cout << "Modo Un Jugador seleccionado." << std::endl;
		Log::getInstance().log(1,__FILE__,__LINE__,"Modo Un Jugador seleccionado.");
		return void();
	}else{
		std::cout << "Modo Multijugador seleccionado." << std::endl;
		Log::getInstance().log(1,__FILE__,__LINE__,"Modo Multijugador seleccionado.");
		this->modoUnJugador = false;
	}
	
	// Elijo servidor o cliente
	while( opc.compare("s") != 0 && opc.compare("S") != 0  && opc.compare("c") != 0 && opc.compare("C") != 0 ){
		std::cout << "Ingrese \"s\" para modo Servidor o \"c\" para Cliente: " << std::endl;
		getline (std::cin,opc);
		if( opc.compare("s") != 0 && opc.compare("S") != 0  && opc.compare("c") != 0 && opc.compare("C") != 0 ){
			std::cout << "Se ha ingresado: "<< opc << std::endl;
		}
	}

	// Seteo la elección hecha
	if( opc.compare("s") == 0 || opc.compare("S") == 0 ){
		this->modoServidor = true;
		std::cout << "Modo Servidor seleccionado" << std::endl;
		Log::getInstance().log(1,__FILE__,__LINE__,"Modo Servidor seleccionado");
	}
	if( opc.compare("c") == 0 || opc.compare("C") == 0 ){
		this->modoServidor = false;
		std::cout << "Modo Cliente seleccionado" << std::endl;
		Log::getInstance().log(1,__FILE__,__LINE__,"Modo Cliente seleccionado");
	}

	return void();
}

bool Administrador::nuevoMenu1(){
	SDL_Surface *imagenDeFondo = NULL;
	SDL_Surface *textoSinglePlayer = NULL;
	SDL_Surface *textoMultiPlayer = NULL;	
	SDL_Surface *pantalla = NULL;
	SDL_Event event;
	TTF_Font *fuente = NULL;
	SDL_Color textColor = { 255, 255, 255 }; //color blanco 	
	bool quit = false;
	bool clicBotonMouseIzquierdo = false;		
	int posicionMouseX, posicionMouseY;
	SDL_Init( SDL_INIT_EVERYTHING );
	TTF_Init();
	pantalla = SDL_SetVideoMode( PANTALLA_ANCHO, PANTALLA_ALTO, SCREEN_BPP, SDL_SWSURFACE );	
	SDL_WM_SetCaption( "Menu", NULL );
	imagenDeFondo  = ImageLoader::getInstance().load_image( "./img/background.png"  );	
	fuente = TTF_OpenFont( "./fonts/Lazy.ttf", 28 );
	textoSinglePlayer = TTF_RenderText_Solid( fuente, "Single Player", textColor );
	textoMultiPlayer  = TTF_RenderText_Solid( fuente, "Multiplayer", textColor );	
	SDL_Rect offsetDelFondo;
	offsetDelFondo.x = 0;
	offsetDelFondo.y = 0;
	SDL_BlitSurface( imagenDeFondo, NULL, pantalla, &offsetDelFondo );
	SDL_Rect offsetDelTextoSinglePlayer;
	offsetDelTextoSinglePlayer.x = 100;
	offsetDelTextoSinglePlayer.y = 200;
	SDL_BlitSurface( textoSinglePlayer, NULL, pantalla, &offsetDelTextoSinglePlayer );
	SDL_Rect offsetDelTextoMultiPlayer;
	offsetDelTextoMultiPlayer.x = 400;
	offsetDelTextoMultiPlayer.y = 200;
	SDL_BlitSurface( textoMultiPlayer, NULL, pantalla, &offsetDelTextoMultiPlayer );
	rectangleRGBA( pantalla, 95, 195, 260, 238, 0, 255, 0, 255);
	rectangleRGBA( pantalla, 395, 195, 540, 238, 0, 255, 0, 255);
	SDL_Flip( pantalla );
	while( quit == false ) {
        while( SDL_PollEvent( &event ) ) {            
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
				break;
				case SDL_MOUSEMOTION:
					posicionMouseX = event.motion.x;
					posicionMouseY = event.motion.y;
				break;		
				case SDL_MOUSEBUTTONDOWN:
					switch (event.button.button) {
						case SDL_BUTTON_LEFT:	
							clicBotonMouseIzquierdo = true;
						break;						
					}			
					break;
				case SDL_MOUSEBUTTONUP:
					switch (event.button.button) {
						case SDL_BUTTON_LEFT:	
							clicBotonMouseIzquierdo = false;
						break;				
					}			
				break;
			}
		}
		if (clicBotonMouseIzquierdo && posicionMouseX >95 && posicionMouseX <260 && posicionMouseY >195 && posicionMouseY <238) {
			this->modoUnJugador = true;
			std::cout << "Modo Un Jugador seleccionado" << std::endl;
			Log::getInstance().log(1,__FILE__,__LINE__,"Modo Un Jugador seleccionado");
			SDL_FreeSurface( imagenDeFondo );
			SDL_FreeSurface( textoSinglePlayer );   
			SDL_FreeSurface( textoMultiPlayer );    	
			TTF_CloseFont( fuente );
			TTF_Quit();   
			SDL_Quit();
			return true;
		}
		else  if (clicBotonMouseIzquierdo && posicionMouseX >395 && posicionMouseX <540 && posicionMouseY >195 && posicionMouseY <238){
			this->modoUnJugador = false;	
			std::cout << "Modo Multiplayer seleccionado" << std::endl;
			Log::getInstance().log(1,__FILE__,__LINE__,"Modo Multiplayer seleccionado");			
			bool ok = this->nuevoMenu2( pantalla, fuente );
			SDL_FreeSurface( imagenDeFondo );
			SDL_FreeSurface( textoSinglePlayer );   
			SDL_FreeSurface( textoMultiPlayer );    	
			TTF_CloseFont( fuente );
			TTF_Quit();   
			SDL_Quit();
			if (ok) return true;
			else return false;
		}				
	}	
}

bool Administrador::nuevoMenu2(SDL_Surface *pantalla, TTF_Font * fuente){
	SDL_Surface *imagenDeFondo2 = NULL;
	SDL_Surface *textoCliente = NULL;
	SDL_Surface *textoServidor = NULL;	
	SDL_Event event;	
	SDL_Color textColor = { 255, 255, 255 }; //color blanco 	
	bool quit = false;
	bool clicBotonMouseIzquierdo = false;		
	int posicionMouseX, posicionMouseY;	
	imagenDeFondo2 = ImageLoader::getInstance().load_image( "./img/background2.png" );	
	textoCliente = TTF_RenderText_Solid( fuente, "Cliente", textColor );
	textoServidor  = TTF_RenderText_Solid( fuente, "Servidor", textColor );	
	SDL_Rect offsetDelFondo;
	offsetDelFondo.x = 0;
	offsetDelFondo.y = 0;
	SDL_BlitSurface( imagenDeFondo2, NULL, pantalla, &offsetDelFondo );		
	SDL_Rect offsetDelTextoCliente;
	offsetDelTextoCliente.x = 100;
	offsetDelTextoCliente.y = 100;
	SDL_BlitSurface( textoCliente, NULL, pantalla, &offsetDelTextoCliente );
	SDL_Rect offsetDelTextoServidor;
	offsetDelTextoServidor.x = 400;
	offsetDelTextoServidor.y = 100;
	SDL_BlitSurface( textoServidor, NULL, pantalla, &offsetDelTextoServidor );
	rectangleRGBA( pantalla, 95, 95, 240, 135, 0, 255, 0, 255);
	rectangleRGBA( pantalla, 395, 95, 540, 135, 0, 255, 0, 255);
	SDL_Flip( pantalla );
	while( quit == false ) {
        while( SDL_PollEvent( &event ) ) {            
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
				break;
				case SDL_MOUSEMOTION:
					posicionMouseX = event.motion.x;
					posicionMouseY = event.motion.y;
				break;		
				case SDL_MOUSEBUTTONDOWN:
					switch (event.button.button) {
						case SDL_BUTTON_LEFT:	
							clicBotonMouseIzquierdo = true;
						break;						
					}			
					break;
				case SDL_MOUSEBUTTONUP:
					switch (event.button.button) {
						case SDL_BUTTON_LEFT:	
							clicBotonMouseIzquierdo = false;
						break;				
					}			
				break;
			}
		}
		if (clicBotonMouseIzquierdo && posicionMouseX >395 && posicionMouseX <540 && posicionMouseY >95 && posicionMouseY <135){
			this->modoServidor = true;
			std::cout << "Modo Servidor seleccionado" << std::endl;
			Log::getInstance().log(1,__FILE__,__LINE__,"Modo Servidor seleccionado");
			SDL_FreeSurface( imagenDeFondo2 );
			SDL_FreeSurface( textoCliente );   
			SDL_FreeSurface( textoServidor );    				
			return true;
		}
		else  if (clicBotonMouseIzquierdo && posicionMouseX >95 && posicionMouseX <240 && posicionMouseY >95 && posicionMouseY <135){
			this->modoServidor = false;
			std::cout << "Modo Cliente seleccionado" << std::endl;
			Log::getInstance().log(1,__FILE__,__LINE__,"Modo Cliente seleccionado");
			SDL_FreeSurface( imagenDeFondo2 );
			SDL_FreeSurface( textoCliente );   
			SDL_FreeSurface( textoServidor );    				
			return true;
		}		
    }	
	return false;
}


void Administrador::correrSinglePlayer(std::string mote,std::string personaje){

	HiloSinglePlayer hiloServidorSinglePlayer;

	this->servidor = new Servidor();
	this->cliente = new Cliente();

	HiloSinglePlayer::stParametrosSinglePlayer parametrosServidor;
	parametrosServidor.esServidor = true;
	parametrosServidor.mote.assign(mote);
	parametrosServidor.personaje.assign(personaje);
	parametrosServidor.pCliente = NULL;
	parametrosServidor.pServidor = this->servidor;

	// Inicio el servidor
	if( this->servidor->iniciarSinglePlayer() == false ){
		Log::getInstance().log(1,__FILE__,__LINE__,"Error al correr el juego en modo Servidor");
		return void();
	}

	// Corro el juego del lado del Servidor en un hilo
	hiloServidorSinglePlayer.correrSinglePlayer(parametrosServidor);

	// Corro el Cliente en el hilo principal
	this->cliente->correrJuegoSinglePlayer(mote,personaje);

	// Una vez que terminó el cliente, puedo hacer el join del hilo del servidor
	hiloServidorSinglePlayer.join();

	return void();
}

void Administrador::correrPruebas(void){

	Pruebas p;

}
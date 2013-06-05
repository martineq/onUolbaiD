#include "Pruebas.h"

using namespace std;

Pruebas::Pruebas() {
}

Pruebas::~Pruebas() {
}

void Pruebas::PruebaMusica(){
	// Estructura para la superficie gráfica, donde se va a dibujar
	SDL_Surface *pantalla, *temp, *sprite, *pasto;

	// Define un área rectangular
	SDL_Rect rcSprite, rcPasto;

	// Estructura para los eventos generales (teclado, mouse, etc.)
	SDL_Event event;

	Uint8 *estadoTecla;
	int colorkey, finJuego;

	// Inicio SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Seteo el nombre en la barra
	SDL_WM_SetCaption("..::Prueba SDL::..", "<Prueba SDL>");

	// Creo la ventana
	pantalla = SDL_SetVideoMode(PANTALLA_ANCHO, PANTALLA_ALTO, 0, 0);

	// Carga el sprite
	temp   = SDL_LoadBMP("./img/sprite.bmp");
	sprite = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	// Seteo el color del sprite  y lo transforma en RLE (Run-length encoding)
	colorkey = SDL_MapRGB(pantalla->format, 255, 0, 255);
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

	// Cargo el pasto
	temp  = SDL_LoadBMP("./img/pasto.bmp");
	pasto = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	// Seteo la posición del sprite
	rcSprite.x = 0;
	rcSprite.y = 0;

	// -------------------- MUSICA ------------------------ //
	
	//Initialize SDL_mixer
	//For MP3 support
	Mix_Init( MIX_INIT_MP3 );
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );

	//The music that will be played
	Mix_Music *music = NULL;
	music = Mix_LoadMUS( "./sounds/musica.wav" );

	//The sound effects that will be used
	Mix_Chunk *scratch = NULL;
	Mix_Chunk *high = NULL;
	Mix_Chunk *med = NULL;
	Mix_Chunk *low = NULL;
	scratch = Mix_LoadWAV( "./sounds/deleted.wav" );
    high = Mix_LoadWAV( "./sounds/pigman.wav" );
    med = Mix_LoadWAV( "./sounds/uh.wav" );
    low = Mix_LoadWAV( "./sounds/uh2.wav" );

	//Arranca la musica 
	Mix_PlayMusic( music, -1 );

	// Pongo fin del juego en falso
	finJuego = 0;
	bool tecla9 = false;

	// Tomo las acciones
	while (!finJuego)
	{
	// Miro si hay un evento <event>
	if (SDL_PollEvent(&event)) {
	  // Encontró un evento
	  switch (event.type) {
		// Se presionó el botón de salir
		case SDL_QUIT:
		  finJuego = 1;
		  break;

		// Manejo eventos del teclado
		case SDL_KEYDOWN:
		  switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
			case SDLK_q:
			  finJuego = 1;
			  break;
			case SDLK_9:
				tecla9 = true;
				break;
		  }	
		  break;
		  case SDL_KEYUP:
			  switch (event.key.keysym.sym) {
			  case SDLK_9:
				  tecla9 = false;
				  break;
			  }
	      break;
	  }
	}

	// Manejo el movimiento del Sprite
	estadoTecla = SDL_GetKeyState(NULL);
	if( tecla9 ) {		
		std::cout << "tecla9" << std::endl;
		 //If there is no music playing
         if( !Mix_PlayingMusic() )			 
			//Play the music
			Mix_PlayMusic( music, -1 );		 
		 else         
			//If the music is paused
			if( Mix_PausedMusic() == 1 )            
				//Resume the music
				Mix_ResumeMusic();            
			else	
				//Pause the music
				Mix_PauseMusic();                 
		 SDL_Delay(200);
	}
	if( event.key.keysym.sym == SDLK_0 )
    {
        //Stop the music
        Mix_HaltMusic();
    }
	if (estadoTecla[SDLK_LEFT] ) {
	  Mix_PlayChannel( -1, scratch, 0 );
	  rcSprite.x -= 1;
	}
	if (estadoTecla[SDLK_RIGHT] ) {
	  Mix_PlayChannel( -1, high, 0 );
	  rcSprite.x += 1;
	}
	if (estadoTecla[SDLK_UP] ) {
	  Mix_PlayChannel( -1, med, 0 );
	  rcSprite.y -= 1;
	}
	if (estadoTecla[SDLK_DOWN] ) {
	  Mix_PlayChannel( -1, low, 0 );
	  rcSprite.y += 1;
	}

	// Hago conincidir con los bordes de la pantalla
	if ( rcSprite.x < 0 ) {
	  rcSprite.x = 0;
	}
	else if ( rcSprite.x > PANTALLA_ANCHO-TAMANIO_SPRITE ) {
	  rcSprite.x = PANTALLA_ANCHO-TAMANIO_SPRITE;
	}
	if ( rcSprite.y < 0 ) {
	  rcSprite.y = 0;
	}
	else if ( rcSprite.y > PANTALLA_ALTO-TAMANIO_SPRITE ) {
	  rcSprite.y = PANTALLA_ALTO-TAMANIO_SPRITE;
	}

	// Dibujo el pasto
	for (int x = 0; x < PANTALLA_ANCHO / TAMANIO_SPRITE; x++) {
	  for (int y = 0; y < PANTALLA_ALTO / TAMANIO_SPRITE; y++) {
		rcPasto.x = x * TAMANIO_SPRITE;
		rcPasto.y = y * TAMANIO_SPRITE;
		SDL_BlitSurface(pasto, NULL, pantalla, &rcPasto);
	  }
	}

	// Dibujo el sprite
	SDL_BlitSurface(sprite, NULL, pantalla, &rcSprite);

	// Refresco la pantalla
	SDL_UpdateRect(pantalla, 0, 0, 0, 0);
	}

	// Limpio la superficie
	SDL_FreeSurface(sprite);
	SDL_FreeSurface(pasto);

	// Salgo del SDL
	//Free the sound effects
    Mix_FreeChunk( scratch );
    Mix_FreeChunk( high );
    Mix_FreeChunk( med );
    Mix_FreeChunk( low );
    
    //Free the music
    Mix_FreeMusic( music );
    
    //Quit SDL_mixer
    Mix_CloseAudio();

	Mix_Quit();
	SDL_Quit();

	Log::getInstance().log(1,__FILE__,__LINE__,"Fin de prueba SDL");

}

void Pruebas::PruebaSdl() {
	// Estructura para la superficie gráfica, donde se va a dibujar
	SDL_Surface *pantalla, *temp, *sprite, *pasto;

	// Define un área rectangular
	SDL_Rect rcSprite, rcPasto;

	// Estructura para los eventos generales (teclado, mouse, etc.)
	SDL_Event event;

	Uint8 *estadoTecla;
	int colorkey, finJuego;

	// Escribo una linea en el archivo de log
	Log::getInstance().log(1,__FILE__,__LINE__,"Inicio de prueba SDL");

	// Inicio SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Seteo el nombre en la barra
	SDL_WM_SetCaption("..::Prueba SDL::..", "<Prueba SDL>");

	// Creo la ventana
	pantalla = SDL_SetVideoMode(PANTALLA_ANCHO, PANTALLA_ALTO, 0, 0);

	// Carga el sprite
	temp   = SDL_LoadBMP(SDL_RUTA_SPRITE);
	sprite = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	// Seteo el color del sprite  y lo transforma en RLE (Run-length encoding)
	colorkey = SDL_MapRGB(pantalla->format, 255, 0, 255);
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

	// Cargo el pasto
	temp  = SDL_LoadBMP(SDL_RUTA_PASTO);
	pasto = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	
	// Seteo la posición del sprite
	rcSprite.x = 0;
	rcSprite.y = 0;

	// Pongo fin del juego en falso
	finJuego = 0;

	// Tomo las acciones
	while (!finJuego)
	{
	// Miro si hay un evento <event>
	if (SDL_PollEvent(&event)) {
	  // Encontró un evento
	  switch (event.type) {
		// Se presionó el botón de salir
		case SDL_QUIT:
		  finJuego = 1;
		  break;

		// Manejo eventos del teclado
		case SDL_KEYDOWN:
		  switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
			case SDLK_q:
			  finJuego = 1;
			  break;
		  }
		  break;
	  }
	}

	// Manejo el movimiento del Sprite
	estadoTecla = SDL_GetKeyState(NULL);
	if (estadoTecla[SDLK_LEFT] ) {
	  rcSprite.x -= 1;
	}
	if (estadoTecla[SDLK_RIGHT] ) {
	  rcSprite.x += 1;
	}
	if (estadoTecla[SDLK_UP] ) {
	  rcSprite.y -= 1;
	}
	if (estadoTecla[SDLK_DOWN] ) {
	  rcSprite.y += 1;
	}

	// Hago conincidir con los bordes de la pantalla
	if ( rcSprite.x < 0 ) {
	  rcSprite.x = 0;
	}
	else if ( rcSprite.x > PANTALLA_ANCHO-TAMANIO_SPRITE ) {
	  rcSprite.x = PANTALLA_ANCHO-TAMANIO_SPRITE;
	}
	if ( rcSprite.y < 0 ) {
	  rcSprite.y = 0;
	}
	else if ( rcSprite.y > PANTALLA_ALTO-TAMANIO_SPRITE ) {
	  rcSprite.y = PANTALLA_ALTO-TAMANIO_SPRITE;
	}

	// Dibujo el pasto
	for (int x = 0; x < PANTALLA_ANCHO / TAMANIO_SPRITE; x++) {
	  for (int y = 0; y < PANTALLA_ALTO / TAMANIO_SPRITE; y++) {
		rcPasto.x = x * TAMANIO_SPRITE;
		rcPasto.y = y * TAMANIO_SPRITE;
		SDL_BlitSurface(pasto, NULL, pantalla, &rcPasto);
	  }
	}

	// Dibujo el sprite
	SDL_BlitSurface(sprite, NULL, pantalla, &rcSprite);

	// Dibujo los triangulos
	dibujarTriangulos(pantalla,PANTALLA_ALTO,PANTALLA_ANCHO,0,PANTALLA_ANCHO/2,0,0,0,0,0,0,0,PANTALLA_ANCHO/2,0,0,0,PANTALLA_ALTO/2,PANTALLA_ALTO/2,PANTALLA_ALTO,0,0,0,255);

	// Refresco la pantalla
	SDL_UpdateRect(pantalla, 0, 0, 0, 0);
	}

	// Limpio la superficie
	SDL_FreeSurface(sprite);
	SDL_FreeSurface(pasto);

	// Salgo del SDL
	SDL_Quit();

	Log::getInstance().log(1,__FILE__,__LINE__,"Fin de prueba SDL");

}

void Pruebas::PruebaYAML() {
	ParserYaml::getInstance().cargarConfiguracionDeJuego();
	ParserYaml::getInstance().cargarConfiguracionDeJuego();
}

void Pruebas::PruebaHilos() {
	HiloDePrueba hiloUno;
	HiloDePrueba hiloDos;

	// Lanzo los hilos. Si lo necesito puedo pasar por parámetro un void*
	// para luego ser usado en la implementación del run(void*) HiloDePrueba
	hiloUno.start(NULL);
	hiloDos.start(NULL);
	
	// Espero a que terminen los hilos
	hiloUno.join();
	hiloDos.join();

	char c;
	std::cin >> c;

	return void();
}

void Pruebas::PruebaAnimacion() {
	ImageLoader::getInstance().iniciarSDL();
	double ALTO_SPRITE = 70;
	double ANCHO_SPRITE = 50;
	SDL_Surface* pantalla = ImageLoader::getInstance().levantarPantalla(PANTALLA_ANCHO,PANTALLA_ALTO);
	SDL_Surface* temp, *pasto;
	list<string> lista;
	list<list<string>> listaAnimaciones;
	list<string> listaN;

	listaN.push_back("./img/castillo01.png");
	listaN.push_back("./img/castillo02.png");
	listaN.push_back("./img/castillo03.png");
	listaN.push_back("./img/castillo04.png");
	listaN.push_back("./img/castillo05.png");

	listaAnimaciones.push_back(listaN);

	VistaEntidad* vEntidad = new VistaEntidad(0,0,263,260,0,0,1,15,1000,listaAnimaciones,false,0,0,0,"SORA",false,0,"",1);
	vEntidad->setPantalla(pantalla);
	SDL_Rect rcPasto;

	// Estructura para los eventos generales (teclado, mouse, etc.)
	SDL_Event event;

	Uint8 *estadoTecla;
	int finJuego;


	temp  = SDL_LoadBMP(SDL_RUTA_PASTO);
	pasto = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	// Pongo fin del juego en falso
	finJuego = 0;
	double x = 0;
	double y = 0;

	// Tomo las acciones
	while (!finJuego)
	{
	// Miro si hay un evento <event>
	if (SDL_PollEvent(&event)) {
	  // Encontró un evento
	  switch (event.type) {
		// Se presionó el botón de salir
		case SDL_QUIT:
		  finJuego = 1;
		  break;

		// Manejo eventos del teclado
		case SDL_KEYDOWN:
		  switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
			case SDLK_q:
			  finJuego = 1;
			  break;
		  }
		  break;
	  }
	}

	// Manejo el movimiento del Sprite
	estadoTecla = SDL_GetKeyState(NULL);
	if (estadoTecla[SDLK_LEFT] ) {
	  x -= 1;
	  vEntidad->setAnimacion(ACCION_OESTE);
	}
	if (estadoTecla[SDLK_RIGHT] ) {
	  x += 1;
	  vEntidad->setAnimacion(ACCION_ESTE);
	}
	if (estadoTecla[SDLK_UP] ) {
	  y -= 1;
	  vEntidad->setAnimacion(ACCION_NORTE);
	}
	if (estadoTecla[SDLK_DOWN] ) {
	  y += 1;
	  vEntidad->setAnimacion(ACCION_SUR);
	}

	// Hago conincidir con los bordes de la pantalla
	if ( x < 0 ) {
	  x = 0;
	}
	else if ( x > PANTALLA_ANCHO-ANCHO_SPRITE ) {
	  x = PANTALLA_ANCHO-ANCHO_SPRITE;
	}
	if ( y < 0 ) {
	  y = 0;
	}
	else if ( y > PANTALLA_ALTO-ALTO_SPRITE ) {
	  y = PANTALLA_ALTO-ALTO_SPRITE;
	}

	// Dibujo el pasto
	for (int x = 0; x < PANTALLA_ANCHO / TAMANIO_SPRITE; x++) {
	  for (int y = 0; y < PANTALLA_ALTO / TAMANIO_SPRITE; y++) {
		rcPasto.x = x * TAMANIO_SPRITE;
		rcPasto.y = y * TAMANIO_SPRITE;
		SDL_BlitSurface(pasto, NULL, pantalla, &rcPasto);
	  }
	}

	// Dibujo el sprite

	// Refresco la pantalla
	SDL_UpdateRect(pantalla, 0, 0, 0, 0);
	}

	// Limpio la superficie
	SDL_FreeSurface(pasto);

	// Salgo del SDL
	SDL_Quit();

}

void Pruebas::dibujarTriangulos(SDL_Surface* pantalla, int alto,int ancho,
	int supAIni,int supAFin,int supBIni,int supBFin,int derAIni,int derAFin,int derBIni,int derBFin,
	int infAIni,int infAFin,int infBIni,int infBFin,int izqAIni,int izqAFin,int izqBIni,int izqBFin,
	int rojo, int verde, int azul,int alfa){

	if( (supBIni != supBFin) && (derAIni != derAFin) ){
		filledTrigonRGBA(pantalla,supBIni,derAIni,supBFin,derAIni,supBFin,derAFin, rojo, verde, azul, alfa);
	}

	if( (derBIni != derBFin) && ( infBIni != infBFin) ){
		filledTrigonRGBA(pantalla,infBFin,derBIni,infBIni,derBFin,infBFin,derBFin, rojo, verde, azul, alfa);
	}

	if( ( infAIni != infAFin) && (izqBIni != izqBFin) ){
		filledTrigonRGBA(pantalla,infAIni,izqBIni,infAIni,izqBFin,infAFin,izqBFin,rojo, verde, azul, alfa);
	}

	if( (izqAIni != izqAFin) && (supAIni != supAFin) ){
		filledTrigonRGBA(pantalla,supAIni,izqAIni,supAFin,izqAIni,supAIni,izqAFin,rojo, verde, azul, alfa);
	}

}

void Pruebas::PruebaServidorChat() {
	SocketServidor socketServidor;
	Serializadora serializadora;
	LectorDirectorios lectorDirectorios;
	int puerto = 444;
	string entrada;

	cout << "Ingrese puerto (defecto 444): ";
	getline(cin, entrada);
	if (!entrada.empty()) {
		stringstream flujo(entrada);
		flujo >> puerto;
	}

	if (!socketServidor.inciarServidor(puerto)) {
		cout << "No se pudo iniciar el servidor para el puerto " << puerto << endl;
		return;
	}

	while (true) {
		int cliente = socketServidor.aceptarCliente();
		if (cliente == ACEPTAR_ERROR) {
			cout << "Error al aceptar al cliente" << endl;
			return;
		}
		else if (cliente != ACEPTAR_TIMEOUT) {
			list<string> archivos;
			
			archivos.push_back("img/chat.png");
			archivos.push_back("verdana.ttf");
			
			socketServidor.setClienteIndividual(cliente);
			if (!socketServidor.enviarArchivosIndividual(archivos, cliente)) {
				cout << "No se pudieron enviar archivos" << endl;
				return;
			}
			socketServidor.setClienteMasivo(cliente);
		}

		if (!socketServidor.recibirMasivo(serializadora)) {
			cout << "Error al recibir mensaje" << endl;
			return;
		}

		if (serializadora.size() > 0) {
			string mensajeRecibido = serializadora.getString();
			serializadora.nuevaSerializacion();
			serializadora.addString(mensajeRecibido);
			if (!socketServidor.enviarMasivo(serializadora)) {
				cout << "Error al enviar mensaje" << endl;
				return;
			}
		}
	}
}

void Pruebas::PruebaClienteChat() {
	Serializadora serializadora;
	DetectorEventos detectorEventos;
	SocketCliente socketCliente;
	string servidor = "localhost";
	int puerto = 444;
	string entrada;

	cout << "Ingrese servidor (defecto localhost): ";
	getline(cin, servidor);
	if (servidor.empty())
		servidor = "localhost";
	
	cout << "Ingrese puerto (defecto 444): ";
	getline(cin, entrada);
	if (!entrada.empty()) {
		stringstream flujo(entrada);
		flujo >> puerto;
	}

	if (!socketCliente.iniciarCliente(servidor.c_str(), puerto)) {
		cout << "No se pudo conectar al servidor " << servidor << ":" << puerto << endl;
		return;
	}

	socketCliente.setEnvioDirecto();
	if (!socketCliente.recibirArchivo("img/chat.png")) {
		cout << "Error al recibir archivo imagen" << endl;
		return;
	}
	if (!socketCliente.recibirArchivo("verdana.ttf")) {
		cout << "Error al recibir archivo fuente" << endl;
		return;
	}
	socketCliente.setEnvioIndirecto();

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	Posicion posicion;

	posicion.x = 0;
	posicion.y = 416;

	VistaChat* vistaChat = new VistaChat(posicion, NULL, NULL);
	SDL_Surface* pantalla = SDL_SetVideoMode(800, 600, 0, 0);
	
	SDL_EnableUNICODE(SDL_ENABLE);

	while (!detectorEventos.getQuit()) {
		if (!socketCliente.recibir(serializadora)) {
			cout << "Error al recibir mensaje" << endl;
			return;
		}

		if (serializadora.size() > 0) {
			string mensajeRecibido = serializadora.getString();
			serializadora.nuevaSerializacion();
			vistaChat->agregarMensaje(NULL, mensajeRecibido);
		}
		
		detectorEventos.detectar();
		
		if (detectorEventos.getEscape())
			vistaChat->visible(false);
		else if (detectorEventos.getEnter()) {
			if (vistaChat->visible())
				vistaChat->enviarMensaje();
			else
				vistaChat->visible(true);
		}
		else if (detectorEventos.getRetroceso())
			vistaChat->borrarCaracter();
		else if (detectorEventos.getCaracter() != 0)
			vistaChat->agregarCaracter(detectorEventos.getCaracter());
		
		if (!detectorEventos.getQuit()) {
			SDL_FillRect(pantalla, NULL, SDL_MapRGB(pantalla->format, 0, 0, 0));
			if (!vistaChat->graficar(pantalla)) {
				cout << "Error al graficar" << endl;
				return;
			}
			SDL_Flip(pantalla);
		}
	}

	SDL_EnableUNICODE(SDL_DISABLE);

	delete vistaChat;

	TTF_Quit();
	SDL_Quit();
}

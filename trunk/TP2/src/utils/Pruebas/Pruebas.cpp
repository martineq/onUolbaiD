#include "Pruebas.h"

using namespace std;

Pruebas::Pruebas() {
}

Pruebas::~Pruebas() {
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
//	double PANTALLA_ANCHO = 800;
//	double PANTALLA_ALTO = 600;
//	double TAMANIO_SPRITE = 10;
	double ALTO_SPRITE = 70;
	double ANCHO_SPRITE = 50;
	SDL_Surface* pantalla = ImageLoader::getInstance().levantarPantalla(PANTALLA_ANCHO,PANTALLA_ALTO);
	SDL_Surface* temp, *pasto;
	list<string> lista;
	list<list<string>> listaAnimaciones;
	/*lista.push_back("./img/SORA_S1.bmp");
	lista.push_back("./img/SORA_S2.bmp");
	lista.push_back("./img/SORA_S3.bmp");
	lista.push_back("./img/SORA_S4.bmp");
	lista.push_back("./img/SORA_S5.bmp");
	lista.push_back("./img/SORA_S6.bmp");
	lista.push_back("./img/SORA_S7.bmp");
	lista.push_back("./img/SORA_S8.bmp");
	lista.push_back("./img/SORA_S9.bmp");*/

	//listaAnimaciones.push_back(lista);
/*	lista.push_back("./img/SORA_N1.bmp");
	lista.push_back("./img/SORA_N2.bmp");
	lista.push_back("./img/SORA_N3.bmp");
	lista.push_back("./img/SORA_N4.bmp");
	lista.push_back("./img/SORA_N5.bmp");
	lista.push_back("./img/SORA_N6.bmp");
	lista.push_back("./img/SORA_N7.bmp");
	lista.push_back("./img/SORA_N8.bmp");
*/
	list<string> listaN;
	//list<string> listaNE;
	//list<string> listaE;
	//list<string> listaSE;
	//list<string> listaS;
	//list<string> listaSO;
	//list<string> listaO;
	//list<string> listaNO;
	/*listaE.push_back("./img/SORA_E1.png");
	listaE.push_back("./img/SORA_E2.png");
	listaE.push_back("./img/SORA_E3.png");
	listaE.push_back("./img/SORA_E4.png");
	listaE.push_back("./img/SORA_E5.png");
	listaE.push_back("./img/SORA_E6.png");
	listaE.push_back("./img/SORA_E7.png");
	listaE.push_back("./img/SORA_E8.png");
	listaAnimaciones.push_back(listaE);*/

	/*listaN.push_back("./img/IMG00000.png");
	listaN.push_back("./img/IMG00001.png");
	listaN.push_back("./img/IMG00002.png");
	listaN.push_back("./img/IMG00003.png");
	listaN.push_back("./img/IMG00004.png");
	listaN.push_back("./img/IMG00005.png");
	listaN.push_back("./img/IMG00006.png");
	listaN.push_back("./img/IMG00007.png");
	listaN.push_back("./img/IMG00008.png");
	listaN.push_back("./img/IMG00009.png");
	listaN.push_back("./img/IMG00010.png");
	listaN.push_back("./img/IMG00011.png");
	listaN.push_back("./img/IMG00012.png");
	listaN.push_back("./img/IMG00013.png");
	listaN.push_back("./img/IMG00014.png");
	listaN.push_back("./img/IMG00015.png");
	listaN.push_back("./img/IMG00016.png");
	listaN.push_back("./img/IMG00017.png");
	listaN.push_back("./img/IMG00018.png");
	listaN.push_back("./img/IMG00019.png");
	listaN.push_back("./img/IMG00020.png");
	listaN.push_back("./img/IMG00021.png");
	listaN.push_back("./img/IMG00022.png");
	listaN.push_back("./img/IMG00023.png");
	listaN.push_back("./img/IMG00024.png");
	listaN.push_back("./img/IMG00025.png");
	listaN.push_back("./img/IMG00026.png");
	listaN.push_back("./img/IMG00027.png");
	listaN.push_back("./img/IMG00028.png");
	listaN.push_back("./img/IMG00029.png");
	listaN.push_back("./img/IMG00030.png");
	listaN.push_back("./img/IMG00031.png");
	listaN.push_back("./img/IMG00032.png");
	listaN.push_back("./img/IMG00033.png");
	listaN.push_back("./img/IMG00034.png");
	listaN.push_back("./img/IMG00035.png");
	listaN.push_back("./img/IMG00036.png");
	listaN.push_back("./img/IMG00037.png");
	listaN.push_back("./img/IMG00038.png");
	listaN.push_back("./img/IMG00039.png");*/

	//listaN.push_back("./img/CasaA01.png");
	//listaN.push_back("./img/CasaA02.png");
	//listaN.push_back("./img/CasaA03.png");
	//listaN.push_back("./img/CasaA04.png");

	//listaN.push_back("./img/MiniMapa01.png");
	//listaN.push_back("./img/MiniMapa02.png");
	//listaN.push_back("./img/MiniMapa03.png");
	//listaN.push_back("./img/MiniMapa04.png");
	//listaN.push_back("./img/MiniMapa05.png");

	//listaN.push_back("./img/molino01.png");
	//listaN.push_back("./img/molino02.png");
	//listaN.push_back("./img/molino03.png");
	//listaN.push_back("./img/molino04.png");

	listaN.push_back("./img/castillo01.png");
	listaN.push_back("./img/castillo02.png");
	listaN.push_back("./img/castillo03.png");
	listaN.push_back("./img/castillo04.png");
	listaN.push_back("./img/castillo05.png");

	/*listaN.push_back("./img/castillo01.png");
	listaN.push_back("./img/castillo02.png");
	listaN.push_back("./img/castillo03.png");
	listaN.push_back("./img/castillo04.png");
	listaN.push_back("./img/castillo05.png");*/

	//listaN.push_back("./img/testxyh_N1.png");
	//listaN.push_back("./img/testxyh_N2.png");
	//listaN.push_back("./img/testxyh_N3.png");
	//listaN.push_back("./img/testxyh_N4.png");
	//listaNE.push_back("./img/testxyh_NE1.png");
	//listaNE.push_back("./img/testxyh_NE2.png");
	//listaNE.push_back("./img/testxyh_NE3.png");
	//listaNE.push_back("./img/testxyh_NE4.png");
	//listaE.push_back("./img/testxyh_E1.png");
	//listaE.push_back("./img/testxyh_E2.png");
	//listaE.push_back("./img/testxyh_E3.png");
	//listaE.push_back("./img/testxyh_E4.png");
	//listaSE.push_back("./img/testxyh_SE1.png");
	//listaSE.push_back("./img/testxyh_SE2.png");
	//listaSE.push_back("./img/testxyh_SE3.png");
	//listaSE.push_back("./img/testxyh_SE4.png");
	//listaS.push_back("./img/testxyh_S1.png");
	//listaS.push_back("./img/testxyh_S2.png");
	//listaS.push_back("./img/testxyh_S3.png");
	//listaS.push_back("./img/testxyh_S4.png");
	//listaSO.push_back("./img/testxyh_SO1.png");
	//listaSO.push_back("./img/testxyh_SO2.png");
	//listaSO.push_back("./img/testxyh_SO3.png");
	//listaSO.push_back("./img/testxyh_SO4.png");
	//listaO.push_back("./img/testxyh_O1.png");
	//listaO.push_back("./img/testxyh_O2.png");
	//listaO.push_back("./img/testxyh_O3.png");
	//listaO.push_back("./img/testxyh_O4.png");
	//listaNO.push_back("./img/testxyh_NO1.png");
	//listaNO.push_back("./img/testxyh_NO2.png");
	//listaNO.push_back("./img/testxyh_NO3.png");
	//listaNO.push_back("./img/testxyh_NO4.png");
	listaAnimaciones.push_back(listaN);
	//listaAnimaciones.push_back(listaNE);
	//listaAnimaciones.push_back(listaE);
	//listaAnimaciones.push_back(listaSE);
	//listaAnimaciones.push_back(listaS);
	//listaAnimaciones.push_back(listaSO);
	//listaAnimaciones.push_back(listaO);
	//listaAnimaciones.push_back(listaNO);

	VistaEntidad* vEntidad = new VistaEntidad(0,0,263,260,0,0,15,1000,listaAnimaciones,false,0,0,0,"SORA"/*Este es el ID*/,false,0,"");
	vEntidad->setPantalla(pantalla);
	//VistaAnimaciones* animaciones = new VistaAnimaciones();
	//animaciones->agregar(lista.front(),lista,200,50,70,15);
	//animaciones->agregar(listaE.front(),listaE,200,50,70,15);
	//VistaAnimacion* animacion = new VistaAnimacion(lista,1000,ANCHO_SPRITE,ALTO_SPRITE,true,10);
	//VistaAnimacion* animacion = animaciones->get(lista.front());
	//animaciones->setPantalla(pantalla);
	//animacion->graficar(0,0);
	SDL_Rect rcPasto;

	// Estructura para los eventos generales (teclado, mouse, etc.)
	SDL_Event event;

	Uint8 *estadoTecla;
//	int colorkey
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

	//vEntidad->graficar();
	// Refresco la pantalla
	SDL_UpdateRect(pantalla, 0, 0, 0, 0);
	}

//	delete animacion;
	// Limpio la superficie
	SDL_FreeSurface(pasto);

	// Salgo del SDL
	SDL_Quit();

}

void Pruebas::dibujarTriangulos(SDL_Surface* pantalla, int alto,int ancho,
	int supAIni,int supAFin,int supBIni,int supBFin,int derAIni,int derAFin,int derBIni,int derBFin,
	int infAIni,int infAFin,int infBIni,int infBFin,int izqAIni,int izqAFin,int izqBIni,int izqBFin,
	int rojo, int verde, int azul,int alfa){

	// Dibujo un triangulo sólido en la pantalla
	// Draw a filled triangle with vertices (x1, y1), (x2, y2), (x3, y3) and RGBA color (r, g, b, a)
	//int filledTrigonRGBA(SDL_Surface* dst,Sint16 x1, Sint16 y1,Sint16 x2, Sint16 y2,Sint16 x3, Sint16 y3, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	

	//int alto = PANTALLA_ALTO;
	//int ancho = PANTALLA_ANCHO;

	//int supAIni = 0;
	//int supAFin = ancho/2;
	//int supBIni = 0;//ancho/2;
	//int supBFin = 0;//ancho;
	//int derAIni = 0;
	//int derAFin = 0;//alto/2;
	//int derBIni = 0;//alto/2;
	//int derBFin = 0;//alto;
	//int infAIni = 0;
	//int infAFin = ancho/2;
	//int infBIni = 0;//ancho/2;
	//int infBFin = 0;//ancho;
	//int izqAIni = 0;
	//int izqAFin = alto/2;
	//int izqBIni = alto/2;
	//int izqBFin = alto;
	//
	//int rojo=0/*25*/, verde=0/*25*/, azul=0/*112*/, alfa=255;
	//
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

void Pruebas::PruebaSockets() {
	MenuSocket ms;
	ms.prueba();
	return void();
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
			vistaChat->agregarMensaje("servidor", mensajeRecibido);
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

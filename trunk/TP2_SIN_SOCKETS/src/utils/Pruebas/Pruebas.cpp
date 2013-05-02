#include "Pruebas.h"

Pruebas::Pruebas(void){

}

Pruebas::~Pruebas(void){

}

void Pruebas::PruebaNieblaDeGuerra(void){

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
	pantalla = SDL_SetVideoMode(PANTALLA_ANCHO, PANTALLA_ALTO, 32,  SDL_HWSURFACE|SDL_DOUBLEBUF);

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

	// Seteo la posicion anterior del sprite que voy a usar para pintar de gris.
	int posicionAnteriorDelSpriteX = 0;
	int posicionAnteriorDelSpriteY = 0;	

	// Dibujo el pasto o sea el fondo completo
	/*for (int x = 0; x < PANTALLA_ANCHO / TAMANIO_SPRITE; x++) {
		for (int y = 0; y < PANTALLA_ALTO / TAMANIO_SPRITE; y++) {
		rcPasto.x = x * TAMANIO_SPRITE;
		rcPasto.y = y * TAMANIO_SPRITE;
		SDL_BlitSurface(pasto, NULL, pantalla, &rcPasto);
		}
	}*/

	//ZONA PARA DIBUJAR EL LIENZO NEGRO QUE CUBRE TODO EL NIVEL AL INICIO.
	//creo una superficie para meter el rectangulo porque solo dibujo superficies no rectangulos
	SDL_Surface* zonaNoDescubiertaSup = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, PANTALLA_ANCHO, PANTALLA_ALTO, 32, 0, 0, 0, 0);
	//dibujo la superficie negra en la pantalla, no la quiero recortar asi que el primer rect es NULL
	//quiero que pegue la superficie sobre la pantalla desde la posicion 0,0 asi que el segundo rectangulo tambien es nulo.
	SDL_BlitSurface(zonaNoDescubiertaSup, NULL, pantalla, NULL);
	
	// Pongo fin del juego en falso
	finJuego = 0;

	// Variables para indicar hacia donde fue el movimiento.
	bool seMovioHaciaLaIzquierda = false;
	bool seMovioHaciaLaDerecha = false;
	bool seMovioHaciaAbajo = false;
	bool seMovioHaciaArriba = false;

	// Tomo las acciones
	while (!finJuego)
	{
		//me guardo la posicion anterior para dibujar la zona no visible pero descubierta
		posicionAnteriorDelSpriteX = rcSprite.x;
		posicionAnteriorDelSpriteY = rcSprite.y;

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
			rcSprite.x -= 2;
			seMovioHaciaLaIzquierda = true;
			seMovioHaciaLaDerecha = false;
			seMovioHaciaAbajo= false;
			seMovioHaciaArriba = false;			
		}
		if (estadoTecla[SDLK_RIGHT] ) {
			rcSprite.x += 2;
			seMovioHaciaLaDerecha = true;
			seMovioHaciaAbajo= false;
			seMovioHaciaArriba = false;			
			seMovioHaciaLaIzquierda = false;
		}
		if (estadoTecla[SDLK_UP] ) {
			rcSprite.y -= 2;
			seMovioHaciaArriba = true;
			seMovioHaciaLaIzquierda = false;
			seMovioHaciaLaDerecha = false;
			seMovioHaciaAbajo= false;
		}
		if (estadoTecla[SDLK_DOWN] ) {
			rcSprite.y += 2;
			seMovioHaciaAbajo= true;
			seMovioHaciaArriba = false;
			seMovioHaciaLaDerecha = false;
			seMovioHaciaLaIzquierda = false;
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

		// Dibujo el pasto visible por el personaje
		for (int x = rcSprite.x - TAMANIO_SPRITE; x < rcSprite.x + 2*TAMANIO_SPRITE; x+=TAMANIO_SPRITE) {
			for (int y = rcSprite.y - TAMANIO_SPRITE; y < rcSprite.y + 2*TAMANIO_SPRITE; y+=TAMANIO_SPRITE) {
				rcPasto.x = x;
				rcPasto.y = y;
				SDL_BlitSurface(pasto, NULL, pantalla, &rcPasto);
			}
		}
		
		// Dibujo el sprite
		SDL_BlitSurface(sprite, NULL, pantalla, &rcSprite);	

		//ZONA PARA DIBUJAR LA ZONA GRIS NO VISIBLE PERO DESCUBIERTA			
		//obtengo color gris
		Uint32 colorGris = SDL_MapRGB(pantalla->format, 127, 127, 127);
		//creo un rectangulo que va a hacer la zona visible del personaje
		SDL_Rect zonaDescubiertaNoVisibleRect;
		//quiero encajar este rectangulo en la pantalla y sobre el personaje (x,y) y hacer un area visible (w,h)
		if (rcSprite.x > posicionAnteriorDelSpriteX) {
			zonaDescubiertaNoVisibleRect.x = posicionAnteriorDelSpriteX - TAMANIO_SPRITE; 
			zonaDescubiertaNoVisibleRect.y = rcSprite.y - TAMANIO_SPRITE; 
			zonaDescubiertaNoVisibleRect.w = 2; 
			zonaDescubiertaNoVisibleRect.h = 3*TAMANIO_SPRITE;
			//creo una superficie para meter el rectangulo porque solo dibujo superficies no rectangulos
			SDL_Surface* zonaDescubiertaNoVisibleSup = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, 2, 3*TAMANIO_SPRITE, 32, 0, 0, 0, 0);
			//seteo la transparencia de la superfice a la mitad
			SDL_SetAlpha(zonaDescubiertaNoVisibleSup, SDL_SRCALPHA|SDL_RLEACCEL, 255);
			//relleno la superficie con el rectangulo
			SDL_FillRect(zonaDescubiertaNoVisibleSup, NULL, colorGris);	
			//dibujo la superficie negra en la pantalla, no la quiero recortar asi que el primer rect es NULL
			//pero el segundo rectangulo no es NULL porque quiero que vaya sobre el sprite.
			SDL_BlitSurface(zonaDescubiertaNoVisibleSup, NULL, pantalla, &zonaDescubiertaNoVisibleRect);	
			SDL_FreeSurface(zonaDescubiertaNoVisibleSup);
		}
		if (rcSprite.x < posicionAnteriorDelSpriteX) {
			zonaDescubiertaNoVisibleRect.x = posicionAnteriorDelSpriteX + 2*TAMANIO_SPRITE - 2; 
			zonaDescubiertaNoVisibleRect.y = rcSprite.y - TAMANIO_SPRITE; 
			zonaDescubiertaNoVisibleRect.w = 2; 
			zonaDescubiertaNoVisibleRect.h = 3*TAMANIO_SPRITE;
			//creo una superficie para meter el rectangulo porque solo dibujo superficies no rectangulos
			SDL_Surface* zonaDescubiertaNoVisibleSup = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, 2, 3*TAMANIO_SPRITE, 32, 0, 0, 0, 0);
			//seteo la transparencia de la superfice a la mitad
			SDL_SetAlpha(zonaDescubiertaNoVisibleSup, SDL_SRCALPHA|SDL_RLEACCEL, 255);
			//relleno la superficie con el rectangulo
			SDL_FillRect(zonaDescubiertaNoVisibleSup, NULL, colorGris);	
			//dibujo la superficie negra en la pantalla, no la quiero recortar asi que el primer rect es NULL
			//pero el segundo rectangulo no es NULL porque quiero que vaya sobre el sprite.
			SDL_BlitSurface(zonaDescubiertaNoVisibleSup, NULL, pantalla, &zonaDescubiertaNoVisibleRect);	
			SDL_FreeSurface(zonaDescubiertaNoVisibleSup);
		}
		if (rcSprite.y < posicionAnteriorDelSpriteY) {
			zonaDescubiertaNoVisibleRect.x = rcSprite.x - TAMANIO_SPRITE; 
			zonaDescubiertaNoVisibleRect.y = posicionAnteriorDelSpriteY + 2*TAMANIO_SPRITE - 2; 
			zonaDescubiertaNoVisibleRect.w = 3*TAMANIO_SPRITE; 
			zonaDescubiertaNoVisibleRect.h = 2;
			//creo una superficie para meter el rectangulo porque solo dibujo superficies no rectangulos
			SDL_Surface* zonaDescubiertaNoVisibleSup = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, 3*TAMANIO_SPRITE, 2, 32, 0, 0, 0, 0);
			//seteo la transparencia de la superfice a la mitad
			SDL_SetAlpha(zonaDescubiertaNoVisibleSup, SDL_SRCALPHA|SDL_RLEACCEL, 255);
			//relleno la superficie con el rectangulo
			SDL_FillRect(zonaDescubiertaNoVisibleSup, NULL, colorGris);	
			//dibujo la superficie negra en la pantalla, no la quiero recortar asi que el primer rect es NULL
			//pero el segundo rectangulo no es NULL porque quiero que vaya sobre el sprite.
			SDL_BlitSurface(zonaDescubiertaNoVisibleSup, NULL, pantalla, &zonaDescubiertaNoVisibleRect);	
			SDL_FreeSurface(zonaDescubiertaNoVisibleSup);
		}
		if (rcSprite.y > posicionAnteriorDelSpriteY) {
			zonaDescubiertaNoVisibleRect.x = rcSprite.x - TAMANIO_SPRITE; 
			zonaDescubiertaNoVisibleRect.y = posicionAnteriorDelSpriteY - TAMANIO_SPRITE; 
			zonaDescubiertaNoVisibleRect.w = 3*TAMANIO_SPRITE; 
			zonaDescubiertaNoVisibleRect.h = 2;
			//creo una superficie para meter el rectangulo porque solo dibujo superficies no rectangulos
			SDL_Surface* zonaDescubiertaNoVisibleSup = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, 3*TAMANIO_SPRITE, 2, 32, 0, 0, 0, 0);
			//seteo la transparencia de la superfice a la mitad
			SDL_SetAlpha(zonaDescubiertaNoVisibleSup, SDL_SRCALPHA|SDL_RLEACCEL, 255);
			//relleno la superficie con el rectangulo
			SDL_FillRect(zonaDescubiertaNoVisibleSup, NULL, colorGris);	
			//dibujo la superficie negra en la pantalla, no la quiero recortar asi que el primer rect es NULL
			//pero el segundo rectangulo no es NULL porque quiero que vaya sobre el sprite.
			SDL_BlitSurface(zonaDescubiertaNoVisibleSup, NULL, pantalla, &zonaDescubiertaNoVisibleRect);	
			SDL_FreeSurface(zonaDescubiertaNoVisibleSup);
		}			
		
		/*
		//ZONA PARA DIBUJAR LOS 3 RECTANGULOS DE ARRIBA
		//obtengo el color
		Uint32 unColor = SDL_MapRGB(pantalla->format, 255, 128, 128);
		//creo una superficie
		SDL_Surface* unaSuperficie = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, 96, 96, 32, 0, 0, 0, 0);
		//creo un rectangulo
		SDL_Rect unRectangulo;
		//seteo el lugar de la superficie donde quiero encajar el rectangulo (x,y) y su tamaño (w,h)
		unRectangulo.x = 0; unRectangulo.y = 0; unRectangulo.w = 96; unRectangulo.h = 96;
		//seteo la transparencia de la superfice 0 es transparente, 255 es opaco
		SDL_SetAlpha(unaSuperficie, SDL_SRCALPHA|SDL_RLEACCEL, 128);
		//relleno el rectangulo del color y lo dibujo en la superficie. Si no le paso ningun rectangulo pinta la superficie completa. 
		//o sea aca lo que hago es pintar la superficie.
		SDL_FillRect(unaSuperficie, NULL, unColor);		
		//dibuja la superficie en la pantalla pero recortandola segun los rectangulos que ponga. 
		//del primer rectangulo toma x,y,w,h y recorta la superficie. Del segundo toma la posicion para colocar en la pantalla lo que recorto.
		SDL_BlitSurface(unaSuperficie, NULL, pantalla, NULL);	

		Uint32 otroColor = SDL_MapRGB(pantalla->format, 128, 255, 128);
		SDL_Surface* otraSuperficie = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, 96, 96, 32, 0, 0, 0, 0);
		SDL_Rect otroRectangulo;
		otroRectangulo.x = 250; otroRectangulo.y = 0; otroRectangulo.w = 96; otroRectangulo.h = 96;
		SDL_SetAlpha(otraSuperficie, SDL_SRCALPHA|SDL_RLEACCEL, 128);
		SDL_FillRect(otraSuperficie, NULL, otroColor);		
		SDL_BlitSurface(otraSuperficie, NULL, pantalla, &otroRectangulo);	

		Uint32 otroColorMas = SDL_MapRGB(pantalla->format, 128, 128, 255);
		SDL_Surface* otraSuperficieMas = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, 96, 96, 32, 0, 0, 0, 0);
		SDL_Rect otroRectanguloMas;
		otroRectanguloMas.x = 500; otroRectanguloMas.y = 0; otroRectanguloMas.w = 96; otroRectanguloMas.h = 96;
		SDL_SetAlpha(otraSuperficieMas, SDL_SRCALPHA|SDL_RLEACCEL, 128);
		SDL_FillRect(otraSuperficieMas, NULL, otroColorMas);		
		SDL_BlitSurface(otraSuperficieMas, NULL, pantalla, &otroRectanguloMas);	

		*/

		// Refresco la pantalla		
		SDL_Flip (pantalla);	
		//SDL_FreeSurface(unaSuperficie); SDL_FreeSurface(otraSuperficie); SDL_FreeSurface(otraSuperficieMas);
		//SDL_FreeSurface(zonaDescubiertaNoVisibleSup);
		//SDL_UpdateRect(pantalla, 0, 0, 0, 0);
		
	}

	// Limpio la superficie
	SDL_FreeSurface(sprite);
	SDL_FreeSurface(pasto);	

	// Salgo del SDL
	SDL_Quit();

}

void Pruebas::PruebaSdl(void){

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

void Pruebas::PruebaYAML(void){
	ParserYaml::getInstance().cargarConfiguracionDeJuego();
	ParserYaml::getInstance().cargarConfiguracionDeJuego();
}

void Pruebas::PruebaHilos(void){

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

void Pruebas::PruebaAnimacion(){
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

	VistaEntidad* vEntidad = new VistaEntidad(0,0,263,260,0,0,15,1000,listaAnimaciones,false,0,0);
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
	int colorkey, finJuego;


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

//	vEntidad->graficar();
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

void Pruebas::PruebaChat() {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	bool salir = false;
	SDL_Event evento;
	Posicion posicion;

	posicion.x = 0;
	posicion.y = 431;

	VistaChat* vistaChat = new VistaChat(posicion, "remitente");
	SDL_Surface* pantalla = SDL_SetVideoMode(800, 600, 0, 0);
	
	vistaChat->asignarDestinatario("destinatario");

	SDL_EnableUNICODE(SDL_ENABLE);

	while (!salir) {
		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_KEYDOWN) {
				if (vistaChat->visible() && (evento.key.keysym.sym == SDLK_ESCAPE))
					vistaChat->visible(false);
				else if (!vistaChat->visible() && (evento.key.keysym.sym == SDLK_RETURN))
					vistaChat->visible(true);
				else if (vistaChat->visible())
					vistaChat->teclaPresionada(evento.key.keysym.unicode);
			}
		}
		salir = (evento.type == SDL_QUIT);

		if (!salir) {
			SDL_FillRect(pantalla, NULL, SDL_MapRGB(pantalla->format, 0, 0, 0));
			salir = !vistaChat->graficar(pantalla);
			SDL_Flip(pantalla);
		}
	}

	SDL_EnableUNICODE(SDL_DISABLE);

	delete vistaChat;

	TTF_Quit();
	SDL_Quit();
}
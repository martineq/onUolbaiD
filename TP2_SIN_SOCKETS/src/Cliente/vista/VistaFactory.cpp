#include "VistaFactory.h"

VistaFactory::VistaFactory(void){

}

VistaFactory::~VistaFactory(void){

}

bool VistaFactory::crearVistaNivel(VistaNivel& vistaNivel,VistaLoop& vistaLoop){

	if( ImageLoader::getInstance().iniciarSDL() == false ) return false;	

	ParserYaml::stJuego juego;
	juego = ParserYaml::getInstance().cargarConfiguracionDeJuego();

	if( juego.juegoValido == false ) return false;

	vistaNivel.setAltoDePantallaEnPixel(juego.pantalla.alto);
	vistaNivel.setAnchoDePantallaEnPixel(juego.pantalla.ancho);

	SDL_Surface* pantalla = ImageLoader::getInstance().levantarPantalla(juego.pantalla.ancho,juego.pantalla.alto);
	vistaLoop.setPantalla(pantalla);

	this->crearJugadorConScroll(juego,vistaNivel,pantalla);
	this->crearEntidades(juego,vistaNivel);

	return true;
}

void VistaFactory::crearJugadorConScroll(ParserYaml::stJuego juego, VistaNivel& vistaNivel,SDL_Surface* pantalla){

	ParserYaml::stProtagonista protagonista = juego.escenarios.front().protagonistas.front();
	std::string nombre = protagonista.entidad;
	ParserYaml::stEntidad entidad = ParserYaml::getInstance().buscarStEntidad(juego,nombre);

	double tamanioX = (double)juego.escenarios.front().tamanioX;
	double tamanioY = (double)juego.escenarios.front().tamanioY;
	double x = (double)protagonista.x;
	double y = (double)protagonista.y;
	double alto = (double)entidad.altoBase;
	double ancho = (double)entidad.anchoBase;
	double posicionReferenciaX = (double)entidad.pixelReferenciaX;
	double posicionReferenciaY = (double)entidad.pixelReferenciaY;
	double fps = (double)entidad.fps;
	double delay = (double)entidad.delay;
	std::list<std::list<std::string>> listaAnimaciones = entidad.imagenes;

	VistaEntidad* pJugador = new VistaEntidad(x,y,alto,ancho,posicionReferenciaX,posicionReferenciaY,fps,delay,listaAnimaciones,true,tamanioX,tamanioY);
	VistaScroll* pScroll = new VistaScroll(x,y,juego.pantalla.alto,juego.pantalla.ancho,tamanioX,tamanioY,pantalla);	// Tomo el mismo x,y,velocidad que el personaje
	vistaNivel.agregarJugador(pJugador);
	vistaNivel.agregarScroll(pScroll);
	vistaNivel.agregarTamanioNivel(tamanioX,tamanioY);

	return void();
}

void VistaFactory::crearEntidades(ParserYaml::stJuego juego, VistaNivel& vistaNivel){
	
	std::list<ParserYaml::stEntidadDefinida> entidadesDef = juego.escenarios.front().entidadesDefinidas;
	std::string nombre = juego.escenarios.front().protagonistas.front().entidad;	

	for (std::list<ParserYaml::stEntidadDefinida>::iterator it=entidadesDef.begin() ; it != entidadesDef.end(); it++ ){	

		ParserYaml::stEntidadDefinida entidadDef = (*it);
		std::string nombre = entidadDef.entidad;
		ParserYaml::stEntidad entidad = ParserYaml::getInstance().buscarStEntidad(juego,nombre);

		double tamanioX = (double)juego.escenarios.front().tamanioX;
		double tamanioY = (double)juego.escenarios.front().tamanioY;
		double x = (double)entidadDef.x;
		double y = (double)entidadDef.y;
		double alto = (double)entidad.altoBase;
		double ancho = (double)entidad.anchoBase;
		double posicionReferenciaX = (double)entidad.pixelReferenciaX;
		double posicionReferenciaY = (double)entidad.pixelReferenciaY;
		double fps = (double)entidad.fps;
		double delay = (double)entidad.delay;
		std::list<std::list<std::string>> listaAnimaciones = entidad.imagenes;

//		VistaEntidad* pEntidad = new VistaEntidad(x,y,alto,ancho,posicionReferenciaX,posicionReferenciaY,fps,delay,listaAnimaciones,false,tamanioX,tamanioY);
		VistaEntidad* pEntidad = new VistaEntidad(x,y,alto,ancho,posicionReferenciaX,posicionReferenciaY,fps,delay,listaAnimaciones,false,tamanioX,tamanioY,nombre);
		vistaNivel.agregarEntidad(pEntidad);
	}

	return void();
}

#include "VistaFactory.h"

VistaFactory::VistaFactory(void){

}

VistaFactory::~VistaFactory(void){

}

bool VistaFactory::crearVistaNivel(VistaNivel& vistaNivel){

	ParserYaml::stJuego juego;
	juego = ParserYaml::getInstance().cargarConfiguracionDeJuego();

	if( juego.juegoValido == false ) return false;

	vistaNivel.setAltoPantalla(juego.pantalla.alto);
	vistaNivel.setAnchoPantalla(juego.pantalla.ancho);
	this->crearJugadorConScroll(juego,vistaNivel);
	this->crearEntidades(juego,vistaNivel);

	return true;
}

void VistaFactory::crearJugadorConScroll(ParserYaml::stJuego juego, VistaNivel& vistaNivel){

	ParserYaml::stProtagonista protagonista = juego.escenarios.front().protagonistas.front();
	std::string nombre = protagonista.entidad;
	ParserYaml::stEntidad entidad = ParserYaml::getInstance().buscarStEntidad(juego,nombre);

	double x = (double)protagonista.x;
	double y = (double)protagonista.y;
	double alto = (double)entidad.altoBase;
	double ancho = (double)entidad.anchoBase;
	double posicionReferenciaX = (double)entidad.pixelReferenciaX;
	double posicionReferenciaY = (double)entidad.pixelReferenciaY;
	double fps = (double)entidad.fps;
	double delay = (double)entidad.delay;
	std::list<std::string> listaAnimaciones = entidad.imagenes;

	VistaEntidad* pJugador = new VistaEntidad(x,y,alto,ancho,posicionReferenciaX,posicionReferenciaY,fps,delay,listaAnimaciones,true);
	VistaScroll* pScroll = new VistaScroll(x,y,juego.pantalla.alto,juego.pantalla.ancho);	// Tomo el mismo x,y,velocidad que el personaje
	vistaNivel.agregarJugador(pJugador);
	vistaNivel.agregarScroll(pScroll); 

	return void();
}

void VistaFactory::crearEntidades(ParserYaml::stJuego juego, VistaNivel& vistaNivel){
	
	std::list<ParserYaml::stEntidadDefinida> entidadesDef = juego.escenarios.front().entidadesDefinidas;
	std::string nombre = juego.escenarios.front().protagonistas.front().entidad;	

	for (std::list<ParserYaml::stEntidadDefinida>::iterator it=entidadesDef.begin() ; it != entidadesDef.end(); it++ ){	

		ParserYaml::stEntidadDefinida entidadDef = (*it);
		std::string nombre = entidadDef.entidad;
		ParserYaml::stEntidad entidad = ParserYaml::getInstance().buscarStEntidad(juego,nombre);

		double x = (double)entidadDef.x;
		double y = (double)entidadDef.y;
		double alto = (double)entidad.altoBase;
		double ancho = (double)entidad.anchoBase;
		double posicionReferenciaX = (double)entidad.pixelReferenciaX;
		double posicionReferenciaY = (double)entidad.pixelReferenciaY;
		double fps = (double)entidad.fps;
		double delay = (double)entidad.delay;
		std::list<std::string> listaAnimaciones = entidad.imagenes;

		VistaEntidad* pEntidad = new VistaEntidad(x,y,alto,ancho,posicionReferenciaX,posicionReferenciaY,fps,delay,listaAnimaciones,false);
		vistaNivel.agregarEntidad(pEntidad);
	}

	return void();
}

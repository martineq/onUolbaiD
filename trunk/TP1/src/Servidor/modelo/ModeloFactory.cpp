#include "ModeloFactory.h"

ModeloFactory::ModeloFactory(void){

}

ModeloFactory::~ModeloFactory(void){

}

bool ModeloFactory::crearModeloNivel(ModeloNivel& modeloNivel){
	
	ParserYaml::stJuego juego;
	juego = ParserYaml::getInstance().cargarConfiguracionDeJuego();

	if( juego.juegoValido == false ) return false;
	
	this->crearJugadorConScroll(juego,modeloNivel);
	this->crearEntidades(juego,modeloNivel);

	return true;
}

void ModeloFactory::crearJugadorConScroll(ParserYaml::stJuego juego, ModeloNivel& modeloNivel){
	
	ParserYaml::stProtagonista protagonista = juego.escenarios.front().protagonistas.front();
	std::string nombre = protagonista.entidad;
	ParserYaml::stEntidad entidad = ParserYaml::getInstance().buscarStEntidad(juego,nombre);

	double x = (double)protagonista.x;
	double y = (double)protagonista.y;
	double alto = (double)entidad.altoBase;
	double ancho = (double)entidad.anchoBase;
	double velocidad = (double)juego.configuracion.velocidadPersonaje;

	modeloNivel.agregarJugador(x,y,alto,ancho,velocidad);
	modeloNivel.agregarScroll(x,y,juego.pantalla.alto,juego.pantalla.ancho,velocidad,juego.configuracion.margenScroll); // Tomo el mismo x,y,velocidad que el personaje

	return void();
}

void ModeloFactory::crearEntidades(ParserYaml::stJuego juego, ModeloNivel& modeloNivel){
	
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
		double velocidad = (double)0;

		modeloNivel.agregarEntidad(x,y,alto,ancho,velocidad);
	}

	return void();
}

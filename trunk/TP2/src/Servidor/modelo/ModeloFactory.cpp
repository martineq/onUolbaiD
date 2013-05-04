#include "ModeloFactory.h"

ModeloFactory::ModeloFactory(void){

}

ModeloFactory::~ModeloFactory(void){

}

bool ModeloFactory::crearModeloNivel(ModeloNivel& modeloNivel){
	
	ParserYaml::stJuego juego;
	juego = ParserYaml::getInstance().cargarConfiguracionDeJuego();

	if( juego.juegoValido == false ) return false;

	modeloNivel.setAnchoTiles(juego.escenarios.front().tamanioX);
	modeloNivel.setAltoTiles(juego.escenarios.front().tamanioY);
	this->crearJugador(juego,modeloNivel);
	this->crearEntidades(juego,modeloNivel);

	return true;
}

void ModeloFactory::crearJugador(ParserYaml::stJuego juego, ModeloNivel& modeloNivel){

	ParserYaml::stProtagonista protagonista = juego.escenarios.front().protagonistas.front();
	std::string nombre = protagonista.entidad;
	ParserYaml::stEntidad entidad = ParserYaml::getInstance().buscarStEntidad(juego.entidades,nombre); // TODO: sacar el front()

	int alto = entidad.altoBase;
	int ancho = entidad.anchoBase;
	int velocidad = juego.configuracion.velocidadPersonaje;
	int anchoEscenario = juego.escenarios.front().tamanioX;
	int altoEscenario = juego.escenarios.front().tamanioY;
	Posicion pos;
	pos.x = protagonista.x;
	pos.y = protagonista.y;

	ModeloEntidad* pJugador = new ModeloEntidad(alto,ancho,velocidad,pos,true,altoEscenario,anchoEscenario,entidad.fps); 

	modeloNivel.agregarJugador(pJugador);
	
	return void();
}

void ModeloFactory::crearEntidades(ParserYaml::stJuego juego, ModeloNivel& modeloNivel){
	
	std::list<ParserYaml::stEntidadDefinida> entidadesDef = juego.escenarios.front().entidadesDefinidas;
	std::string nombre = juego.escenarios.front().protagonistas.front().entidad;	

	for (std::list<ParserYaml::stEntidadDefinida>::iterator it=entidadesDef.begin() ; it != entidadesDef.end(); it++ ){	

		ParserYaml::stEntidadDefinida entidadDef = (*it);
		std::string nombre = entidadDef.entidad;
		ParserYaml::stEntidad entidad = ParserYaml::getInstance().buscarStEntidad(juego.entidades,nombre); // TODO: sacar el front()

		int x = entidadDef.x;
		int y = entidadDef.y;
		int alto = entidad.altoBase;
		int ancho = entidad.anchoBase;
		int velocidad = 0;
		int anchoEscenario = juego.escenarios.front().tamanioX;
		int altoEscenario = juego.escenarios.front().tamanioY;
		Posicion pos;
		pos.x = x;
		pos.y = y;

		ModeloEntidad* pEntidad = new ModeloEntidad(alto,ancho,velocidad,pos,false,altoEscenario,anchoEscenario,entidad.fps); 

		modeloNivel.agregarEntidad(pEntidad);
	}

	return void();
}

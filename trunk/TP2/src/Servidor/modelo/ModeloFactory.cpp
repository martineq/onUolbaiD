#include "ModeloFactory.h"

ModeloFactory::ModeloFactory(void){

}

ModeloFactory::~ModeloFactory(void){

}

// En este método puedo no usar mutex porque se hace antes de lanzar otros hilos
bool ModeloFactory::crearNivel(ModeloNivel& modeloNivel,ModeloLoop& modeloLoop,SocketServidor* pSocket){
	
	// Inicio el servidor
	if( pSocket->inciarServidor(PUERTO_SERVIDOR) == false ) return false;

	// Cargo el archivo de configuración
	ParserYaml::stJuego juegoYaml;
	juegoYaml = ParserYaml::getInstance().cargarConfiguracionDeJuego();
	if( juegoYaml.juegoValido == false ){
		Log::getInstance().log(1,__FILE__,__LINE__,"Error al obtener la configuración de juego.");
		return false;
	}

	// Preparo el juego elegido
	stModeloJuegoElegido juegoElegido;
	juegoElegido.listaEntidades = juegoYaml.entidades;
	juegoElegido.pantalla = juegoYaml.pantalla;
	juegoElegido.configuracion = juegoYaml.configuracion;
	juegoElegido.escenario = this->elegirEscenario(juegoYaml.escenarios,pSocket);
	juegoElegido.protagonista = this->elegirProtagonista(juegoElegido.escenario.protagonistas,pSocket);

	modeloNivel.setAnchoTiles(juegoElegido.escenario.tamanioX);
	modeloNivel.setAltoTiles(juegoElegido.escenario.tamanioY);

	this->crearEntidades(juegoElegido,modeloNivel,pSocket);

	ProxyControladorEvento* pProxyEvento = new ProxyControladorEvento();
	pProxyEvento->setSocketServidor(pSocket);
	modeloLoop.setProxyControladorEvento(pProxyEvento);

	return true;
}


ParserYaml::stEscenario ModeloFactory::elegirEscenario(std::list<ParserYaml::stEscenario>& listaEscenarios,SocketServidor* pSocket){
	ParserYaml::stEscenario escenario = listaEscenarios.front();
	
	// TODO: Ver si el escenario siempre va a poder ser el 1ro de la lista o si el Servidor me dice cual tengo que elegir

	return escenario;
}

ParserYaml::stProtagonista ModeloFactory::elegirProtagonista(std::list<ParserYaml::stProtagonista>& listaProtagonistas,SocketServidor* pSocket){
	ParserYaml::stProtagonista protagonista = listaProtagonistas.front();
	
	// TODO: Implementar toda la comunicación con el Servidor para decirle el protagonista elelgido, el nombre de usuario y
	// luego de obtener una respuesta positiva del servidor devolver el protagonista elegido. (Por ahora devuelvo el primero)

	return protagonista;
}


// Para que lo use el hilo de configuración
void ModeloFactory::crearJugador(ModeloNivel& modeloNivel,SocketServidor* pSocket){
// TODO: *** Refactorizar de acuerdo al TP2. Esta es la contraparte del VistaFactory::elegirProtagonista() ***

/*	ParserYaml::stProtagonista protagonista = juego.escenarios.front().protagonistas.front();
	std::string nombre = protagonista.entidad;
	ParserYaml::stEntidad entidad = ParserYaml::getInstance().buscarStEntidad(juego.entidades,nombre);

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
	*/
	return void();
}

void ModeloFactory::crearEntidades(stModeloJuegoElegido& juego, ModeloNivel& modeloNivel,SocketServidor* pSocket){
	
	std::list<ParserYaml::stEntidadDefinida> entidadesDef = juego.escenario.entidadesDefinidas;

	for (std::list<ParserYaml::stEntidadDefinida>::iterator it=entidadesDef.begin() ; it != entidadesDef.end(); it++ ){	

		ParserYaml::stEntidadDefinida entidadDef = (*it);
		std::string nombreEntidad = entidadDef.entidad;
		ParserYaml::stEntidad entidad = ParserYaml::getInstance().buscarStEntidad(juego.listaEntidades,nombreEntidad); 
		int x = entidadDef.x;
		int y = entidadDef.y;
		int alto = entidad.altoBase;
		int ancho = entidad.anchoBase;
		int velocidad = 0;
		int anchoEscenario = juego.escenario.tamanioX;
		int altoEscenario = juego.escenario.tamanioY;
		Posicion pos;
		pos.x = x;
		pos.y = y;

		ProxyModeloEntidad* pProxyEntidad = new ProxyModeloEntidad();
		pProxyEntidad->setSocketServidor(pSocket);
		ModeloEntidad* pEntidad = new ModeloEntidad(alto,ancho,velocidad,pos,false,altoEscenario,anchoEscenario,entidad.fps,pProxyEntidad); 
		modeloNivel.agregarEntidad(pEntidad);
	}

	return void();
}

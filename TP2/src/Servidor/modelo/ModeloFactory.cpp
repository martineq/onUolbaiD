#include "ModeloFactory.h"

ModeloFactory::ModeloFactory(void){

}

ModeloFactory::~ModeloFactory(void){

}

// En este método no hace falta usar mutex porque se hace antes de lanzar otros hilos
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
	this->juegoElegido.listaEntidades = juegoYaml.entidades;
	this->juegoElegido.pantalla = juegoYaml.pantalla;
	this->juegoElegido.configuracion = juegoYaml.configuracion;
	if( this->elegirEscenario(juegoYaml.escenarios) == false) return false;

	// Seteo alto y ancho
	modeloNivel.setAnchoTiles(this->juegoElegido.escenario.tamanioX);
	modeloNivel.setAltoTiles(this->juegoElegido.escenario.tamanioY);

	// Creo las entidades del nivel, las que no son los jugadores
	this->crearEntidades(modeloNivel,pSocket);

	// Agrego el ProxyControladorEvento
	ProxyControladorEvento* pProxyEvento = new ProxyControladorEvento();
	pProxyEvento->setSocketServidor(pSocket);
	modeloLoop.setProxyControladorEvento(pProxyEvento);

	return true;
}

bool ModeloFactory::elegirEscenario(std::list<ParserYaml::stEscenario>& listaEscenarios){
	
	// Ver si el escenario se elije desde consola, o si hay que levantarlo de archivo. Por ahora lo tomo de consola
	std::cout << "Elija el escenario: " << std::endl;
	for (std::list<ParserYaml::stEscenario>::iterator it=listaEscenarios.begin() ; it != listaEscenarios.end(); it++ ){
		std::string opc;
		std::cout << "Elije el escenario: "<< (*it).nombre << " ? (s) para confirmar, otra tecla para rechazar" << std::endl;
		getline (std::cin,opc);
		if( opc.compare("s") == 0 || opc.compare("S") == 0 ){
			std::cout << "Se usara el escenario: "<< (*it).nombre << std::endl;
			this->juegoElegido.escenarioElegido = (*it).nombre;
			this->juegoElegido.escenario = (*it);
			return true;
		}
	}

	// Si no eligió nada
	std::cout << "Se usara el escenario: "<< listaEscenarios.front().nombre << std::endl;
	this->juegoElegido.escenarioElegido = listaEscenarios.front().nombre;
	this->juegoElegido.escenario = listaEscenarios.front();
	return true;
}

bool ModeloFactory::rutinaAgregarNuevoCliente(ModeloNivel* modeloNivel,SocketServidor* pSocket, int id){
	if( this->enviarEscenario(pSocket,id) == false ) return false;
	if( this->elegirProtagonista(modeloNivel,pSocket,id) == false ) return false;
	if( this->enviarOtrosJugadores(modeloNivel,pSocket,id) == false ) return false;
	return true;
}

bool ModeloFactory::enviarEscenario(SocketServidor* pSocket, int id){

	std::string nombre = this->juegoElegido.escenarioElegido;
	std::list<int> listaId = this->juegoElegido.listaIdEntidades;
	Serializadora s;

	// Serializo primero el nombre del escenario
	s.addString(nombre);

	// Luego agregro la lista de ID's
	int cantidadDeIds = (int)listaId.size();
	s.addInt(cantidadDeIds);	// Al principio agrego la cantidad total de ID's que estoy mandando
	for (std::list<int>::iterator it=listaId.begin() ; it != listaId.end(); it++ ){ // Luego agrego todos los ID's
		s.addInt( (*it) );
	}

	// Envio el nombre y la lista de ID's serializados en una cadena de chars
	std::string* pStr = s.getSerializacion();
	if( pSocket->enviarIndividual(pStr->c_str(),pStr->size(),id) == false ){
		delete pStr;
		return false;
	}else{
		delete pStr;
	}

	return true; 
}

// Para que lo use el hilo de configuración
bool ModeloFactory::elegirProtagonista(ModeloNivel* modeloNivel,SocketServidor* pSocket, int id){
	ParserYaml::stProtagonista protagonista = this->juegoElegido.escenario.protagonistas.front();
	// TODO: *** Refactorizar de acuerdo al TP2. Esta es la contraparte del VistaFactory::recibirProtagonista() ***
	//		 + Acá es donde le paso this->listaIdEntidades a cada cliente para que sepa que ID ponerle a sus entidades vista. 
	//	     + Ademas le paso aparte el ID de la entidad que es el jugador
	//		 + Aparte le paso los id y los datos de los jugadores que se agregaron además de el
	
	// Implementar toda la comunicación con el Servidor para decirle el protagonista elelgido, el nombre de usuario y
	// luego de obtener una respuesta positiva del servidor devolver el protagonista elegido. (Por ahora devuelvo el primero)

	// Acá llamo a this->crearJugador() una vez elegido por el cliente

	return true; // return false si hay error de sockets
}

bool ModeloFactory::enviarOtrosJugadores(ModeloNivel* modeloNivel,SocketServidor* pSocket,int idMiJugador){
	// TODO: Implementar. Acá envio los datos necesarios para crear en la vista a los otros jugadores conectados (si es que hay) 
	std::list<ModeloEntidad*> listaJugadores = modeloNivel->getListaJugadores();
	int cantidadOtrosJugadores = listaJugadores.size() - 1;  // Descarto a mi jugador
	ProxyModeloEntidad proxy;
	proxy.setSocketServidor(pSocket);
	ProxyModeloEntidad::stEntidad entidad;

	// Envío la cantidad de jugadores que voy a transferir
	Serializadora s;
	s.addInt(cantidadOtrosJugadores);
	std::string* pStr = s.getSerializacion();
	if( pSocket->enviarIndividual(pStr->c_str(),pStr->size(),idMiJugador) == false ){
		delete pStr;
		return false;
	}else{
		delete pStr;
	}

	// Envío los datos de los jugadores, a través de un proxy
	for (std::list<ModeloEntidad*>::iterator it=listaJugadores.begin() ; it != listaJugadores.end(); it++ ){ 
		ModeloEntidad* pEntidad = (*it);
		if( pEntidad->id() != idMiJugador ){
			// Cargo los datos
			entidad.eliminarEntidad = false;
			entidad.errorEnSocket = false;
			entidad.direccion = pEntidad->direccion();
			entidad.esUltimoMovimiento = pEntidad->esUltimoMovimiento();
			entidad.id = pEntidad->id();
			entidad.nombreNuevaEntidad = pEntidad->nombreEntidad();
			entidad.pixelSiguienteX = pEntidad->pixelSiguiente().x;
			entidad.pixelSiguienteY = pEntidad->pixelSiguiente().y;

			// Los envio a través del proxy
			if( proxy.enviarEntidadIndividual(entidad,idMiJugador) == false ) return false;
		}
	}

	return true; 
}

// Para que lo use el hilo de configuración
void ModeloFactory::crearJugador(ModeloNivel* modeloNivel,SocketServidor* pSocket, int id){
// TODO: acá tengo que agregar las líneas:
//		ProxyModeloEntidad* pProxyEntidad = new ProxyModeloEntidad();
//		pProxyEntidad->setSocketServidor(pSocket);
//		para luego ponerlo en el construcotr de ModeloEntidad del personaje

/*	ParserYaml::stProtagonista protagonista = juego.escenarios.front().protagonistas.front();
	std::string nombreEntidad = protagonista.entidad;
	ParserYaml::stEntidad entidad = ParserYaml::getInstance().buscarStEntidad(juego.entidades,nombreEntidad);

	int alto = entidad.altoBase;
	int ancho = entidad.anchoBase;
	int velocidad = juego.configuracion.velocidadPersonaje;
	int anchoEscenario = juego.escenarios.front().tamanioX;
	int altoEscenario = juego.escenarios.front().tamanioY;
	Posicion pos;
	pos.x = protagonista.x;
	pos.y = protagonista.y;

	ModeloEntidad* pJugador = new ModeloEntidad(alto,ancho,velocidad,pos,true,altoEscenario,anchoEscenario,entidad.fps,id,nombreEntidad); 

	modeloNivel.agregarJugador(pJugador);
	*/
	return void();
}

void ModeloFactory::crearEntidades(ModeloNivel& modeloNivel,SocketServidor* pSocket){
	
	ModeloFactory::stModeloJuegoElegido juego = this->juegoElegido;

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

		// Voy guardando todos los ID's que se crean por cada entidad en uan lista, para luego pasarle esta a cada cliente así puede numerar de la misma forma a todas las entidades vista.
		// De esta forma cada EntidadModelo y cada EntidadVista van a tener el mismo ID
		int nuevoID = Ticket::getInstance().pedirNumero();
		this->juegoElegido.listaIdEntidades.push_back(nuevoID);
		ModeloEntidad* pEntidad = new ModeloEntidad(alto,ancho,velocidad,pos,false,altoEscenario,anchoEscenario,entidad.fps,pProxyEntidad,nuevoID,nombreEntidad);
		modeloNivel.agregarEntidad(pEntidad);
	}

	

	return void();
}

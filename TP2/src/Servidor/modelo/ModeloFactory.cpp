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

// No es usado por hilos
bool ModeloFactory::elegirEscenario(std::list<ParserYaml::stEscenario>& listaEscenarios){
	
	// Ver si el escenario se elije desde consola, o si hay que levantarlo de archivo. Por ahora lo tomo de consola
	std::cout << "Elija el escenario: " << std::endl;
	for (std::list<ParserYaml::stEscenario>::iterator it=listaEscenarios.begin() ; it != listaEscenarios.end(); it++ ){
		std::string opc;
		std::cout << "Elije el escenario: "<< (*it).nombre << " ? (s) para confirmar, otra tecla para rechazar" << std::endl;
		getline (std::cin,opc);
		if( opc.compare("s") == 0 || opc.compare("S") == 0 ){
			std::cout << "Se usara el escenario: "<< (*it).nombre << std::endl;
			this->juegoElegido.nombreEscenario = (*it).nombre;
			this->juegoElegido.escenario = (*it);
			return true;
		}
	}

	// Si no eligió nada
	std::cout << "Se usara el escenario: "<< listaEscenarios.front().nombre << std::endl;
	this->juegoElegido.nombreEscenario = listaEscenarios.front().nombre;
	this->juegoElegido.escenario = listaEscenarios.front();
	return true;
}

bool ModeloFactory::rutinaAgregarNuevoCliente(void* modeloNivel,SocketServidor* pSocket,int id){

	ModeloNivel* pModeloNivel = (ModeloNivel*)modeloNivel;

	// Envío los archivos de configuración
	if( this->enviarArchivosDeConfiguracion(pSocket,id) == false ) return false;

	// Envío el escenario creado, junto con los ID's de cada entidad del escenario para que se puedan setear en el cliente
	if( this->enviarEscenario(pSocket,id) == false ) return false;

	// Elijo junto al cliente el protagonista que va a usar, envio los datos para la creación en el Cliente y lo creo en el Modelo
	if( this->elegirProtagonista(pModeloNivel,pSocket,id) == false ) return false;
	
	// Envío los datos para la creación de los demas jugadores
	if( this->enviarOtrosJugadores(pModeloNivel,pSocket,id) == false ) return false;

	// Una vez que está completamente configurado, seteo al cliente en modo "masivo" para que reciba/envie desde colas y no directamente
	pSocket->setClienteMasivo(id);

	// A lo último, aumento el número de jugadores en uno para que se notifique el ModeloNivel
	pModeloNivel->incrementarJugadores();

	return true;
}

bool ModeloFactory::enviarEscenario(SocketServidor* pSocket, int id){
	ModeloFactory::stModeloJuegoElegido juego = this->getCopiaJuegoElegido();
	std::string nombre = juego.nombreEscenario;
	std::list<int> listaId = juego.listaIdEntidades;
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
	ModeloFactory::stModeloJuegoElegido juego = this->getCopiaJuegoElegido();
	ParserYaml::stProtagonista protagonista = juego.escenario.protagonistas.front();
	// TODO: *** Refactorizar de acuerdo al TP2. Esta es la contraparte del VistaFactory::recibirProtagonista() ***
	//		 + Acá es donde le paso this->listaIdEntidades a cada cliente para que sepa que ID ponerle a sus entidades vista. 
	//	     + Ademas le paso aparte el ID de la entidad que es el jugador
	//		 + Aparte le paso los id y los datos de los jugadores que se agregaron además de el
	
	// Implementar toda la comunicación con el Servidor para decirle el protagonista elegido, el nombre de usuario y
	// luego de obtener una respuesta positiva del servidor devolver el protagonista elegido. (Por ahora devuelvo el primero)

	// Acá llamo a this->crearJugador() una vez elegido por el cliente

	return true; // return false si hay error de sockets
}

bool ModeloFactory::enviarOtrosJugadores(ModeloNivel* modeloNivel,SocketServidor* pSocket,int idMiJugador){

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
void ModeloFactory::crearJugador(ModeloNivel* modeloNivel,SocketServidor* pSocket,std::string nombreJugador, int id){

	ModeloFactory::stModeloJuegoElegido juego = this->getCopiaJuegoElegido();
	ParserYaml::stEntidad entidadJugador = ParserYaml::getInstance().buscarStEntidad(juego.listaEntidades,nombreJugador);
	ParserYaml::stProtagonista protagonista = ParserYaml::getInstance().buscarStProtagonista(juego.escenario,nombreJugador);

	// Seteo todos los valores
	int alto = entidadJugador.altoBase;
	int ancho = entidadJugador.anchoBase;
	int velocidad = juego.configuracion.velocidadPersonaje;
	int anchoEscenario = juego.escenario.tamanioX;
	int altoEscenario = juego.escenario.tamanioY;
	Posicion pos;
	pos.x = protagonista.x;
	pos.y = protagonista.y;

	// Creo el proxy para esta entidad jugador
	ProxyModeloEntidad* pProxyEntidad = new ProxyModeloEntidad();
	pProxyEntidad->setSocketServidor(pSocket);

	// Creo la entidad y la agrego al nivel
	ModeloEntidad* pJugador = new ModeloEntidad(alto,ancho,velocidad,pos,true,altoEscenario,anchoEscenario,entidadJugador.fps,pProxyEntidad,id,entidadJugador.nombre); 
	modeloNivel->agregarJugador(pJugador);

	return void();
}

// No es usado por hilos
void ModeloFactory::crearEntidades(ModeloNivel& modeloNivel,SocketServidor* pSocket){
	ModeloFactory::stModeloJuegoElegido juego = this->getCopiaJuegoElegido();
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
		this->juegoElegido.listaIdEntidades.push_back(nuevoID);	// Puedo escribirlo directamente porque a esta altura no hay hilos (no hace falta usar el mutex)
		ModeloEntidad* pEntidad = new ModeloEntidad(alto,ancho,velocidad,pos,false,altoEscenario,anchoEscenario,entidad.fps,pProxyEntidad,nuevoID,nombreEntidad);
		modeloNivel.agregarEntidad(pEntidad);
	}
	return void();
}


// Envia al cliente todos los archivos necesarios para el funcionamiento del juego
bool ModeloFactory::enviarArchivosDeConfiguracion(SocketServidor* pServidor,int idSocketCliente){
	bool exito = true;
	LectorDirectorios lector;	// Para obtener todos los nombres de los archivos
	std::vector<std::string> listaArchivos;

	// Envio los archivos de configuracion
	listaArchivos = lector.leerDirectorio(DIRECTORIO_IMG);
	if( !this->enviarListaDeArchivos(listaArchivos,pServidor,idSocketCliente)) {
		Log::getInstance().log(1,__FILE__,__LINE__,"El Servidor no pudo enviar todos los archivos de imagenes al cliente con ID ",idSocketCliente);
		exito = false;
	}
	
	// Envio los archivos de imagenes
		listaArchivos = lector.leerDirectorio(DIRECTORIO_CONFIG);
	if( this->enviarListaDeArchivos(listaArchivos,pServidor,idSocketCliente) == false)  {
		Log::getInstance().log(1,__FILE__,__LINE__,"El Servidor no pudo enviar todos los archivos de imagenes al cliente con ID ",idSocketCliente);
		exito = false;
	}

	return exito;
}

bool ModeloFactory::enviarListaDeArchivos(std::vector<std::string> vector,SocketServidor* pServidor,int idSocketCliente){

	// Lista con todos las rutas de los archivos que voy a enviar
	std::list<std::string> rutaDeArchivosParaEnviar;

	// Serializo el vector de strings
	Serializadora s;
	int cantidadDeArchivos = (int)vector.size();
	s.addInt(cantidadDeArchivos);
	for ( int i=0 ; i < cantidadDeArchivos ; i++ ){
		s.addString(vector[i]);								// Los agrego al serializado
		rutaDeArchivosParaEnviar.push_back(vector[i]);		// Los agrego a la lista de archivos
	}

	// Envio el vector de strings serializado en una cadena de chars
	std::string* pStr = s.getSerializacion();
	if( pServidor->enviarIndividual(pStr->c_str(),pStr->size(),idSocketCliente) == false ){
		delete pStr;
		return false;
	}else{
		delete pStr;
	}

	// Envio todos los archivos 
	pServidor->enviarArchivosIndividual(rutaDeArchivosParaEnviar,idSocketCliente);

	return true;
}

// Se usa para los métodos que son invocados por hilos de configuración, en tiempo de juego. Seguro contra hilos
ModeloFactory::stModeloJuegoElegido ModeloFactory::getCopiaJuegoElegido(void){
	ModeloFactory::stModeloJuegoElegido juego;
	this->mutexJuegoElegido.lockLectura(__FILE__,__LINE__);
	juego = this->juegoElegido;
	this->mutexJuegoElegido.unlock(__FILE__,__LINE__);
	return juego;
}
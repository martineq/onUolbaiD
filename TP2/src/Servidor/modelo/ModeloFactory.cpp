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
	std::cout << "Eleccion de escenario: " << std::endl;
	for (std::list<ParserYaml::stEscenario>::iterator it=listaEscenarios.begin() ; it != listaEscenarios.end(); it++ ){
		std::string opc;
		std::cout << "Elije el escenario "<< (*it).nombre << "? (s) para confirmar, otra para rechazar" << std::endl;
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
	if( this->enviarProtagonista(pModeloNivel,pSocket,id) == false ) return false;
	
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
	return pSocket->enviarIndividual(s,id); 
}

// Selecciona y envia los datos del protagonista elegido. Además crea la EntidadModelo correspondiente y la setea en el ModeloNivel. Método usado por el hilo de configuración
bool ModeloFactory::enviarProtagonista(ModeloNivel* modeloNivel,SocketServidor* pSocket, int& id){

	// Recibo el nombres de usuario y nombre de protagonista serializados, luego los hidrato
	Serializadora s;
	if( pSocket->recibirIndividual(s,id) == false ) return false;
	std::string mote(s.getString());
	std::string nombreEntidadPersonaje(s.getString());

	// Elijo al protagonista, lo creo y envio los datos del mismo
	ProxyModeloEntidad::stEntidad entidad = this->elegirProtagonista(modeloNivel,mote,nombreEntidadPersonaje,pSocket,id);
	ProxyModeloEntidad proxy;
	proxy.setSocketServidor(pSocket);
	if( proxy.enviarEntidadIndividual(entidad,entidad.id) == false ) return false;

	return true; // return false si hay error de sockets
}

// Devuelve el jugador que va a usar el cliente
// Caso 1: Si el jugador NO está en uso se crea y se devuelve una copia del mismo
// Caso 2: Si el jugador SI está en uso y SI se encuentra "congelado", se cambia su condición y se devuelve una copia del mismo
// Caso 3: Si el jugador SI está en uso y NO se encuentra "congelado", se elige otro jugador que no se encuentre en uso, se crea y se devuelve una copia del mismo
ProxyModeloEntidad::stEntidad ModeloFactory::elegirProtagonista(ModeloNivel* modeloNivel,std::string& mote,std::string& nombreEntidadPersonaje,SocketServidor* pSocket,int& id){

	std::list<ModeloEntidad*> listaEntidades = modeloNivel->getListaJugadores();
	std::list<std::string> listaJugadoresUsados;
	ProxyModeloEntidad::stEntidad stEntidad;
	ModeloEntidad* pEntidad = NULL;
	bool moteEncontrado = false;

	for( std::list<ModeloEntidad*>::iterator itEntidad = listaEntidades.begin() ; itEntidad != listaEntidades.end() ; itEntidad++ ){
		// Obtengo el nombre de jugador y entidad
		std::string moteJugador = (*itEntidad)->nombreJugador();
		std::string entidadPersonaje = (*itEntidad)->nombreEntidad();
		
		// Guardo el nombre de la entidad usada
		listaJugadoresUsados.push_back(entidadPersonaje);
		
		// Comparo el nombre del jugador usado con el que me pide el usuario nuevo
		if( moteJugador.compare(mote) == 0 ){
			pEntidad = (*itEntidad);
			moteEncontrado = true;
		}
	}

	// NOTA: Observar que si encuentro al usuario, ya no me interesa el personaje que eligió el cliente, porque este ya se encuentra creado
	if( moteEncontrado == true ){		
		// Me fijo si está congelado o no
		if( pEntidad->estaCongelado() == true){

			// Si está congelado y es el mismo nombre de usuario, lo descongelo y obtengo sus datos
			pEntidad->estaCongelado(false);

			// Cargo la entidad
			stEntidad = pEntidad->stEntidad();

			// Como se está conectando de vuelta, le reasigno al socket de cliente el ID que tenia antes (stEntidad.id), para poder reconocerlo en el loop de juego
			pSocket->renombrarIdCliente(id,stEntidad.id);

			// Renombro el id pasado por referencia
			id = stEntidad.id;

			return stEntidad;

		}else{
			// Si no está congelado y es el mismo nombre de usuario, no lo puedo usar, así que busco otro personaje libre y lo creo
			std::string nombrePersonajeObtenido = this->obtenerPersonajeLibre(listaJugadoresUsados,nombreEntidadPersonaje);
			
			// Anexo el ID al mote para diferenciarlo del que ya está jugando
			std::stringstream ss;
			ss << id;
			mote.append(ss.str());
			
			nombreEntidadPersonaje = nombrePersonajeObtenido;	// Actualizo el nombre que va a tener el personaje
			this->crearJugador(modeloNivel,stEntidad,pSocket,nombrePersonajeObtenido,mote,id);
			return stEntidad;
		}
	}else{
		// Si no encontré ese nombre entre los jugadores creo uno nuevo
		std::string nombrePersonajeObtenido = this->obtenerPersonajeLibre(listaJugadoresUsados,nombreEntidadPersonaje);
		nombreEntidadPersonaje = nombrePersonajeObtenido;	// Actualizo el nombre que va a tener el personaje
		this->crearJugador(modeloNivel,stEntidad,pSocket,nombrePersonajeObtenido,mote,id);
		return stEntidad;
	}
	return stEntidad;
}

std::string ModeloFactory::obtenerPersonajeLibre(std::list<std::string> listaEntidadesUsadas,std::string personajePedido){
	std::string personajeElegido;
	ModeloFactory::stModeloJuegoElegido juego = this->getCopiaJuegoElegido();
	std::list<ParserYaml::stProtagonista> listaEntidadesTotal = juego.escenario.protagonistas;

	// Obtengo los protagonistas libres
	std::list<std::string> listaEntidadesLibres;
	for( std::list<ParserYaml::stProtagonista>::iterator itTotal = listaEntidadesTotal.begin() ; itTotal != listaEntidadesTotal.end() ; itTotal++ ){

		std::string protagonistaCandidato = (*itTotal).entidad;
		bool encontrado = false;
		for( std::list<std::string>::iterator itUsadas = listaEntidadesUsadas.begin() ; itUsadas != listaEntidadesUsadas.end() ; itUsadas++ ){
			std::string protagonistaUsado = (*itUsadas);
			if( protagonistaUsado.compare(protagonistaCandidato) == 0 ) encontrado = true;
		}
	
		if( encontrado == false ) listaEntidadesLibres.push_back(protagonistaCandidato);
	}

	// Asigno un personaje libre
	if( listaEntidadesLibres.empty() == false){

		for( std::list<std::string>::iterator itLibres = listaEntidadesLibres.begin() ; itLibres != listaEntidadesLibres.end() ; itLibres++ ){
			std::string protagonistaLibre = (*itLibres);
			if( protagonistaLibre.compare(personajePedido) == 0 ){ 
				personajeElegido = protagonistaLibre;
				return personajeElegido;
			}
		}
		
		personajeElegido = listaEntidadesLibres.front();
		return personajeElegido;
	}else{
		// Si no hay ninguno libre, voy a tener que darle uno repetido. Elijo cualquiera, menos el que pidió (así se da cuenta que no estaba disponible y lo notifica)
		for( std::list<std::string>::iterator itUsadas = listaEntidadesUsadas.begin() ; itUsadas != listaEntidadesUsadas.end() ; itUsadas++ ){
			std::string protagonistaUsado = (*itUsadas);
			if( protagonistaUsado.compare(personajePedido) != 0 ){ 
				personajeElegido = protagonistaUsado;
				return personajeElegido;
			}
		}
	}

	return personajeElegido;
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
 
	if( pSocket->enviarIndividual(s,idMiJugador) == false ) return false;

	// Envío los datos de los jugadores, a través de un proxy
	for (std::list<ModeloEntidad*>::iterator it=listaJugadores.begin() ; it != listaJugadores.end(); it++ ){ 
		ModeloEntidad* pEntidad = (*it);
		if( pEntidad->id() != idMiJugador ){
			// Cargo los datos
			int accion = 0;
			proxy.cargarStEntidad(entidad,pEntidad->id(),false,false,pEntidad->esJugador(),pEntidad->nombreEntidad(),pEntidad->pixelActual().x,pEntidad->pixelActual().y,pEntidad->posicionActual().x,pEntidad->posicionActual().y,pEntidad->pixelSiguiente().x,pEntidad->pixelSiguiente().y,pEntidad->posicionActual().x,pEntidad->posicionActual().y,pEntidad->direccion(),pEntidad->esUltimoMovimiento(),accion,pEntidad->nombreJugador());

			// Los envio a través del proxy
			if( proxy.enviarEntidadIndividual(entidad,idMiJugador) == false ) return false;
		}
	}

	return true; 
}

// Para que lo use el hilo de configuración
void ModeloFactory::crearJugador(ModeloNivel* modeloNivel,ProxyModeloEntidad::stEntidad& stEntidad,SocketServidor* pSocket,std::string nombreJugador,std::string mote,int id){

	ModeloFactory::stModeloJuegoElegido juego = this->getCopiaJuegoElegido();
	ParserYaml::stEntidad entidadJugador = ParserYaml::getInstance().buscarStEntidad(juego.listaEntidades,nombreJugador);
	ParserYaml::stProtagonista protagonista = ParserYaml::getInstance().buscarStProtagonista(juego.escenario,nombreJugador);

	// Valores tomados desde la entidad
	int alto = entidadJugador.altoBase;
	int ancho = entidadJugador.anchoBase;

	// Valores tomados desde el escenario
	int anchoEscenario = juego.escenario.tamanioX;
	int altoEscenario = juego.escenario.tamanioY;
	int velocidad = juego.configuracion.velocidadPersonaje;

	// Para que empiece en una posicion aleatoria sin conflictos
	srand(time(NULL));
	int min = ZONA_VISIBLE/2;
	int maxY = juego.escenario.tamanioY - ZONA_VISIBLE/2;
	int maxX = juego.escenario.tamanioX - ZONA_VISIBLE/2;
	int outputX = min + (rand() % (int)(maxX - min + 1));		
	int outputY = min + (rand() % (int)(maxY - min + 1));
	Posicion pos;
	pos.x = outputX;
	pos.y = outputY;
	while (modeloNivel->posicionOcupada(pos)) {		
		outputX = min + (rand() % (int)(maxX - min + 1));	
		outputY = min + (rand() % (int)(maxY - min + 1));		
		pos.x = outputX;
		pos.y = outputY;		
	}	

	// Creo el proxy para esta entidad jugador
	ProxyModeloEntidad* pProxyEntidad = new ProxyModeloEntidad();
	pProxyEntidad->setSocketServidor(pSocket);

	// Creo la entidad
	ModeloEntidad* pJugador = new ModeloEntidad(alto,ancho,velocidad,pos,true,altoEscenario,anchoEscenario,entidadJugador.fps,pProxyEntidad,id,entidadJugador.nombre,mote); 

	// Obtengo los datos de la stEntidad para luego pasarsela al cliente
	stEntidad = pJugador->stEntidad();

	// Agrego la entidad al nivel
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

		// Valores tomados desde la entidad definida
		int x = entidadDef.x;
		int y = entidadDef.y;
		Posicion pos;
		pos.x = x;
		pos.y = y;
		
		// Valores tomados desde la entidad
		int alto = entidad.altoBase;
		int ancho = entidad.anchoBase;
		int velocidad = 0;

		// Valores tomados desde el escenario elegido
		int anchoEscenario = juego.escenario.tamanioX;
		int altoEscenario = juego.escenario.tamanioY;

		// Creo el proxy para esta entidad
		ProxyModeloEntidad* pProxyEntidad = new ProxyModeloEntidad();
		pProxyEntidad->setSocketServidor(pSocket);

		// Voy guardando todos los ID's que se crean por cada entidad en uan lista, para luego pasarle esta a cada cliente así puede numerar de la misma forma a todas las entidades vista.
		// De esta forma cada EntidadModelo y cada EntidadVista van a tener el mismo ID
		int nuevoID = Ticket::getInstance().pedirNumero();
		this->juegoElegido.listaIdEntidades.push_back(nuevoID);	// Puedo escribirlo directamente porque a esta altura no hay hilos (no hace falta usar el mutex)

		// Creo la entidad y la agrego al nivel
		std::string nombreJugador("Entidad_Sin_Duenio");
		ModeloEntidad* pEntidad = new ModeloEntidad(alto,ancho,velocidad,pos,false,altoEscenario,anchoEscenario,entidad.fps,pProxyEntidad,nuevoID,nombreEntidad,nombreJugador);
		modeloNivel.agregarEntidad(pEntidad);

	}
	return void();
}


// Envia al cliente todos los archivos necesarios para el funcionamiento del juego
bool ModeloFactory::enviarArchivosDeConfiguracion(SocketServidor* pServidor,int idSocketCliente){
	bool exito = true;
	LectorDirectorios lector;	// Para obtener todos los nombres de los archivos
	std::vector<std::string> listaArchivos;
	double tiempoInicial = Temporizador::getInstance().obtenerTics();

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

	double tiempoFinal = Temporizador::getInstance().obtenerTics();
	double tiempoTranscurrido =  ( tiempoFinal - tiempoInicial ) / 1000;
	std::cout << "Tiempo para envio de archivos: " << tiempoTranscurrido << " segundos. " << std::endl;

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
	if( pServidor->enviarIndividual(s,idSocketCliente) == false ) return false;
	
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

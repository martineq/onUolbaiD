#include "VistaFactory.h"

VistaFactory::VistaFactory(void){

}

VistaFactory::~VistaFactory(void){

}

bool VistaFactory::crearNivel(VistaNivel& vistaNivel,VistaLoop& vistaLoop,ControladorEvento* evento,SocketCliente* pSocket){

	// Me conecto al servidor
	if( this->conectarSocket(pSocket) == false ) return false;

	// Recibo los archivos desde el servidor
	if( this->recibirArchivos(pSocket) == false ) return false;

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

	// Recibo datos desde el Servidor
	if( this->recibirEscenario(juegoYaml.escenarios,pSocket) == false ) return false;
	if( this->recibirProtagonista(pSocket) == false ) return false;
	if( this->recibirOtrosJugadores(vistaNivel,pSocket) == false ) return false;

	// Creo los elementos de la Vista
	if( this->crearElementosVista(vistaNivel,vistaLoop,pSocket) == false ) return false;

	// Creo los elementos del Controlador
	if( this->crearElementosControlador(vistaNivel,vistaLoop,evento,pSocket) == false ) return false;

	return true;
}

bool VistaFactory::conectarSocket(SocketCliente* pSocket){

	// Ver si conectarSocket() va a recibir el puerto y el IP desde consola o de un archivo (¿De cuál sería?). Por ahora está desde consola

	// Tomo el puerto
	std::cout << "Ingrese el puerto donde se encuentra el servidor (Enter para 444)" << std::endl;
	std::string entradaTexto;
	getline(std::cin,entradaTexto);
	if( entradaTexto.empty() == true ) entradaTexto.assign("444");
	std::cout << "Puerto ingresado: "<<entradaTexto <<" "<< std::endl;
	std::stringstream str(entradaTexto);
	int puerto;
	str >> puerto;	// Lo paso a int

	// Tomo el ip
	std::cout << "Ingrese el host al cual desea conectarse (Enter para \"localhost\")" << std::endl;
	entradaTexto.clear();
	getline(std::cin,entradaTexto);
	if (entradaTexto.empty()==true) entradaTexto.assign("localhost");
	std::cout << "Ingreso: |"<<entradaTexto.c_str() <<"| "<< std::endl;

	// Me conecto al servidor
	if( pSocket->iniciarCliente(entradaTexto.c_str(),puerto) == false ){
		std::cerr << "Error al iniciar la conexion cliente." << std::endl;
		Log::getInstance().log(1,__FILE__,__LINE__,"Error al iniciar la conexion cliente.");
		return false;
	}else{
		pSocket->setEnvioDirecto();
	}

	return true;
}

// Recibe del servidor todos los archivos necesarios para el funcionamiento del juego
bool VistaFactory::recibirArchivos(SocketCliente* pSocket){

	// Recibo los archivos de configuracion
	if( this->recibirListaDeArchivos(DIRECTORIO_IMG,pSocket) == false) return false;

	// Recibo los archivos de imagenes
	if( this->recibirListaDeArchivos(DIRECTORIO_CONFIG,pSocket) == false) return false;

	return true;
}

bool VistaFactory::recibirListaDeArchivos(const char* directorioElegido,SocketCliente* pSocket){

	std::string cadenaRecibida;
	if( this->recibirCadenaSerializada(cadenaRecibida,pSocket) == false ) return false;
	
	// Hidrato el vector de strings y recibo cada archivo
	int cantidadDeArchivos = 0;
	Serializadora s(&cadenaRecibida);
	cantidadDeArchivos = s.getInt();
	for ( int i=0 ; i < cantidadDeArchivos ; i++ ){
		std::string rutaDestino(s.getString());
		if ( pSocket->recibirArchivo(rutaDestino.c_str()) == false) return false; // Recibo el archivo binario
	}

	return true;
}

bool VistaFactory::recibirEscenario(std::list<ParserYaml::stEscenario>& listaEscenarios,SocketCliente* pSocket){

	std::string cadenaRecibida;
	if( this->recibirCadenaSerializada(cadenaRecibida,pSocket) == false ) return false;
	
	// Comienzo a hidratar. Hidrato el nombre de escenario
	Serializadora s(&cadenaRecibida);
	std::string nombreEscenario = s.getString();
	this->asignarEscenarioElegido(nombreEscenario,listaEscenarios); // A partir del nombre recibido, asigno el escenario

	// Hidrato la lista de ID's serializados
	this->juegoElegido.listaIdEntidades.clear();
	int cantidadDeIds = s.getInt();
	for ( int i=0 ; i < cantidadDeIds ; i++ ){
		this->juegoElegido.listaIdEntidades.push_back(s.getInt());
	}

	return true; 
}

void VistaFactory::asignarEscenarioElegido(std::string nombreEscenario,std::list<ParserYaml::stEscenario>& listaEscenarios){
	
	for (std::list<ParserYaml::stEscenario>::iterator it=listaEscenarios.begin() ; it != listaEscenarios.end(); it++ ){
		if( (*it).nombre.compare(nombreEscenario) == 0 ){
			this->juegoElegido.escenario = (*it);
			return void();
		}
	}
	
	return void();
}

bool VistaFactory::recibirProtagonista(SocketCliente* pSocket){
	// TODO: *** Refactorizar de acuerdo al TP2. Esta es la contraparte del ModeloFactory::crearJugador() ***
	// Implementar toda la comunicación con el Servidor para decirle el protagonista elegido, el nombre de usuario y
	// luego de obtener una respuesta positiva del servidor devolver el protagonista elegido. (Por ahora devuelvo el primero)
	
	// >>> No instancio al jugador acá, sólo cargo los datos para luego instanciarlo
	// Supuestamente uso: juegoElegido.escenario.protagonistas,juegoElegido.idJugador,juegoElegido.protagonista ver si hace falta esto

	this->juegoElegido.protagonista = this->juegoElegido.escenario.protagonistas.front();
	
	return true; // return false si hay error de sockets
}

// Instancia a todos los jugadores que no son controlados por este cliente
bool VistaFactory::recibirOtrosJugadores(VistaNivel& vistaNivel,SocketCliente* pSocket){

	std::string cadenaRecibida;
	if( this->recibirCadenaSerializada(cadenaRecibida,pSocket) == false ) return false;
	
	// Hidrato la cantidad de personajes que me van a mandar
	Serializadora s(&cadenaRecibida);
	int cantidadOtrosJugadores = s.getInt();

	// Recibo los datos de los jugadores, a través de un proxy
	ProxyModeloEntidad proxy;
	proxy.setSocketCliente(pSocket);
	ProxyModeloEntidad::stEntidad entidad;
	for ( unsigned int i=0 ; i<cantidadOtrosJugadores ; i++ ){ 
		if( proxy.recibirEntidadIndividual(entidad) == false ) return false;
		this->crearJugadorSinScroll(vistaNivel,entidad,pSocket);
	}

	return true; 
}

bool VistaFactory::recibirCadenaSerializada(std::string& cadenaRecibida,SocketCliente* pSocket){
	unsigned int tamanioRecibido = 0;
	char* cadenaRaw = NULL;

	// Recibo desde el Servidor datos serializados en una cadena de chars
	if( pSocket->recibir(&cadenaRaw,tamanioRecibido) == false ) return false;
	if( tamanioRecibido > 0 ){
		cadenaRecibida.assign(cadenaRaw,tamanioRecibido);
		delete[] cadenaRaw;
	}else{
		return false;	// Error al obtener archivos
	}

	return true;
}

bool VistaFactory::crearElementosVista(VistaNivel& vistaNivel,VistaLoop& vistaLoop,SocketCliente* pSocket){

	// Inicio y seteo de SDL
	if( ImageLoader::getInstance().iniciarSDL() == false ) return false;	
	SDL_Surface* pPantallaSDL = ImageLoader::getInstance().levantarPantalla(this->juegoElegido.pantalla.ancho,this->juegoElegido.pantalla.alto);
	vistaLoop.setPantalla(pPantallaSDL);

	// Seteo medidas de pantalla
	vistaNivel.setAltoPantalla(this->juegoElegido.pantalla.alto);
	vistaNivel.setAnchoPantalla(this->juegoElegido.pantalla.ancho);

	// Seteo el ProxyModeloEntidad
	ProxyModeloEntidad* pProxyEntidad = new ProxyModeloEntidad();
	pProxyEntidad->setSocketCliente(pSocket);
	vistaLoop.SetProxyModeloEntidad(pProxyEntidad);

	// Creo al protagonista y a las entidades (no creo a otros jugadores)
	this->crearJugadorConScroll(vistaNivel,pPantallaSDL,pSocket);
	this->crearEntidades(vistaNivel);

	return true;
}

void VistaFactory::crearJugadorConScroll(VistaNivel& vistaNivel,SDL_Surface* pantalla,SocketCliente* pSocket){

	std::string nombreProtagonista = this->juegoElegido.protagonista.entidad;
	ParserYaml::stEntidad entidadProtagonista = ParserYaml::getInstance().buscarStEntidad(this->juegoElegido.listaEntidades,nombreProtagonista);

	double tamanioX = (double)this->juegoElegido.escenario.tamanioX;
	double tamanioY = (double)this->juegoElegido.escenario.tamanioY;
	double x = (double)this->juegoElegido.protagonista.x;
	double y = (double)this->juegoElegido.protagonista.y;
	double alto = (double)entidadProtagonista.altoBase;
	double ancho = (double)entidadProtagonista.anchoBase;
	double posicionReferenciaX = (double)entidadProtagonista.pixelReferenciaX;
	double posicionReferenciaY = (double)entidadProtagonista.pixelReferenciaY;
	double fps = (double)entidadProtagonista.fps;
	double delay = (double)entidadProtagonista.delay;
	std::list<std::list<std::string>> listaAnimaciones = entidadProtagonista.imagenes;

	VistaEntidad* pJugador = new VistaEntidad(x,y,alto,ancho,posicionReferenciaX,posicionReferenciaY,fps,delay,listaAnimaciones,true,tamanioX,tamanioY,this->juegoElegido.idJugador);
	VistaScroll* pScroll = new VistaScroll(x,y,this->juegoElegido.pantalla.alto,this->juegoElegido.pantalla.ancho,tamanioX,tamanioY,pantalla,this->juegoElegido.idJugador);	// Tomo el mismo x,y,velocidad que el personaje
	vistaNivel.agregarJugador(pJugador);
	vistaNivel.agregarScroll(pScroll);
	vistaNivel.agregarTamanioNivel(tamanioX,tamanioY);

	return void();
}

void VistaFactory::crearJugadorSinScroll(VistaNivel& vistaNivel,ProxyModeloEntidad::stEntidad& entidad,SocketCliente* pSocket){

	std::string nombreJugador = entidad.nombreNuevaEntidad;
	ParserYaml::stEntidad entidadJugador = ParserYaml::getInstance().buscarStEntidad(this->juegoElegido.listaEntidades,nombreJugador);

	double tamanioX = (double)this->juegoElegido.escenario.tamanioX;
	double tamanioY = (double)this->juegoElegido.escenario.tamanioY;
	double x = (double)entidad.pixelSiguienteX;
	double y = (double)entidad.pixelSiguienteY;
	double alto = (double)entidadJugador.altoBase;
	double ancho = (double)entidadJugador.anchoBase;
	double posicionReferenciaX = (double)entidadJugador.pixelReferenciaX;
	double posicionReferenciaY = (double)entidadJugador.pixelReferenciaY;
	double fps = (double)entidadJugador.fps;
	double delay = (double)entidadJugador.delay;
	std::list<std::list<std::string>> listaAnimaciones = entidadJugador.imagenes;

	VistaEntidad* pJugador = new VistaEntidad(x,y,alto,ancho,posicionReferenciaX,posicionReferenciaY,fps,delay,listaAnimaciones,true,tamanioX,tamanioY,this->juegoElegido.idJugador);
	vistaNivel.agregarJugador(pJugador);

	return void();
}

void VistaFactory::crearEntidades(VistaNivel& vistaNivel){

	std::list<ParserYaml::stEntidadDefinida> entidadesDef = this->juegoElegido.escenario.entidadesDefinidas;
	std::list<int>idEntidadesDef = this->juegoElegido.listaIdEntidades;

	for (std::list<ParserYaml::stEntidadDefinida>::iterator it=entidadesDef.begin() ; it != entidadesDef.end(); it++ ){	

		ParserYaml::stEntidadDefinida entidadDef = (*it);
		std::string nombreEntidad = entidadDef.entidad;
		ParserYaml::stEntidad entidad = ParserYaml::getInstance().buscarStEntidad(this->juegoElegido.listaEntidades,nombreEntidad);

		double tamanioX = (double)this->juegoElegido.escenario.tamanioX;
		double tamanioY = (double)this->juegoElegido.escenario.tamanioY;
		double x = (double)entidadDef.x;
		double y = (double)entidadDef.y;
		double alto = (double)entidad.altoBase;
		double ancho = (double)entidad.anchoBase;
		double posicionReferenciaX = (double)entidad.pixelReferenciaX;
		double posicionReferenciaY = (double)entidad.pixelReferenciaY;
		double fps = (double)entidad.fps;
		double delay = (double)entidad.delay;
		std::list<std::list<std::string>> listaAnimaciones = entidad.imagenes;

		VistaEntidad* pEntidad = new VistaEntidad(x,y,alto,ancho,posicionReferenciaX,posicionReferenciaY,fps,delay,listaAnimaciones,false,tamanioX,tamanioY,idEntidadesDef.front());
		vistaNivel.agregarEntidad(pEntidad);
		idEntidadesDef.pop_front();	// Una vez que usé el ID lo tiro para tener acceso al próximo
	}

	return void();
}

bool VistaFactory::crearElementosControlador(VistaNivel& vistaNivel,VistaLoop& vistaLoop,ControladorEvento* evento,SocketCliente* pSocket){

	// Seteo el ID del jugador en el Evento
	evento->setIdJugador(this->juegoElegido.idJugador);

	// Creo el Scroll
	this->crearControladorScroll(evento);
	
	// Creo el Proxy
	this->crearProxyControladorEvento(evento,pSocket);

	// Vinculo el VistaScroll con el ControladorScroll
	this->vincularScroll(vistaNivel,evento);

	return true;
}

void VistaFactory::crearControladorScroll(ControladorEvento* evento){
	int x = this->juegoElegido.protagonista.x;
	int y = this->juegoElegido.protagonista.y;
	int anchoEscenario = this->juegoElegido.escenario.tamanioX;
	int altoEscenario = this->juegoElegido.escenario.tamanioY;

	ControladorScroll* pScroll = new ControladorScroll(this->juegoElegido.pantalla.ancho,this->juegoElegido.pantalla.alto,anchoEscenario,altoEscenario,this->juegoElegido.configuracion.margenScroll,x,y);
	evento->setControladorScroll(pScroll, this->juegoElegido.escenario.tamanioX, this->juegoElegido.escenario.tamanioY);

	return void();
}

void VistaFactory::crearProxyControladorEvento(ControladorEvento* evento,SocketCliente* pSocket){

	ProxyControladorEvento* pProxyEvento = new ProxyControladorEvento();
	pProxyEvento->setSocketCliente(pSocket);
	evento->setProxyEvento(pProxyEvento);

	return void();
}

void VistaFactory::vincularScroll(VistaNivel& vistaNivel,ControladorEvento* evento){

	ControladorScroll* pCtrlScroll = evento->getControladorScroll();
	VistaScroll* pVistaScroll = vistaNivel.getScroll();

	pCtrlScroll->agregarObservador(pVistaScroll);

	return void();
}

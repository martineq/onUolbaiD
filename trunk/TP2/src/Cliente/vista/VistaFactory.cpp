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
	stVistaJuegoElegido juegoElegido;
	juegoElegido.listaEntidades = juegoYaml.entidades;
	juegoElegido.pantalla = juegoYaml.pantalla;
	juegoElegido.configuracion = juegoYaml.configuracion;
	juegoElegido.escenario = this->elegirEscenario(juegoYaml.escenarios,pSocket);
	juegoElegido.protagonista = this->elegirProtagonista(juegoElegido.escenario.protagonistas,juegoElegido.idJugador,pSocket);

	// Creo los elementos de la Vista
	if( this->crearElementosVista(juegoElegido,vistaNivel,vistaLoop,pSocket) == false ) return false;

	// Creo los elementos del Controlador
	if( this->crearElementosControlador(juegoElegido,vistaNivel,vistaLoop,evento,pSocket) == false ) return false;

	return true;
}

bool VistaFactory::conectarSocket(SocketCliente* pSocket){

	// TODO: Ver si conectarSocket() va a recibir el puerto y el IP desde consola o de un archivo (¿De cuál sería?). Por ahora está desde consola

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
	std::string cadena;
	unsigned int tamanioRecibido = 0;
	char* cadenaRaw = NULL;

	// Recibo el vector de strings serializado en una cadena de chars
	if( pSocket->recibir(&cadenaRaw,tamanioRecibido) == false ) return false;
	if( tamanioRecibido > 0 ){
		cadena.assign(cadenaRaw,tamanioRecibido);
		delete[] cadenaRaw;
	}else{
		// "Error al obtener archivos"
		return false;
	}

	// Hidrato el vector de strings y recibo cada archivo
	int cantidadDeArchivos = 0;
	Serializadora s(&cadena);
	cantidadDeArchivos = s.getInt();
	for ( int i=0 ; i < cantidadDeArchivos ; i++ ){
		std::string rutaDestino(s.getString());
		// Log::getInstance().log(3,__FILE__,__LINE__,"El cliente recibe :",  rutaDestino);
		if ( pSocket->recibirArchivo(rutaDestino.c_str()) == false) return false; // Recibo el archivo binario
	}

	return true;
}


ParserYaml::stEscenario VistaFactory::elegirEscenario(std::list<ParserYaml::stEscenario>& listaEscenarios,SocketCliente* pSocket){
	ParserYaml::stEscenario escenario = listaEscenarios.front();
	
	// TODO: Implementar. Ver si el escenario siempre va a poder ser el 1ro de la lista o si el Servidor me dice cual tengo que elegir

	return escenario;
}

ParserYaml::stProtagonista VistaFactory::elegirProtagonista(std::list<ParserYaml::stProtagonista>& listaProtagonistas,int& idJugador,SocketCliente* pSocket){
// TODO: *** Refactorizar de acuerdo al TP2. Esta es la contraparte del ModeloFactory::crearJugador() ***

	ParserYaml::stProtagonista protagonista = listaProtagonistas.front();
	
	// TODO: Implementar toda la comunicación con el Servidor para decirle el protagonista elegido, el nombre de usuario y
	// luego de obtener una respuesta positiva del servidor devolver el protagonista elegido. (Por ahora devuelvo el primero)

	return protagonista;
}

bool VistaFactory::crearElementosVista(stVistaJuegoElegido& juego,VistaNivel& vistaNivel,VistaLoop& vistaLoop,SocketCliente* pSocket){

	if( ImageLoader::getInstance().iniciarSDL() == false ) return false;	

	vistaNivel.setAltoPantalla(juego.pantalla.alto);
	vistaNivel.setAnchoPantalla(juego.pantalla.ancho);

	SDL_Surface* pPantallaSDL = ImageLoader::getInstance().levantarPantalla(juego.pantalla.ancho,juego.pantalla.alto);
	vistaLoop.setPantalla(pPantallaSDL);

	ProxyModeloEntidad* pProxyEntidad = new ProxyModeloEntidad();
	pProxyEntidad->setSocketCliente(pSocket);
	vistaLoop.SetProxyModeloEntidad(pProxyEntidad);

	this->crearJugadorConScroll(juego,vistaNivel,pPantallaSDL,pSocket);
	this->crearEntidades(juego,vistaNivel);

	return true;
}

void VistaFactory::crearJugadorConScroll(stVistaJuegoElegido& juego, VistaNivel& vistaNivel,SDL_Surface* pantalla,SocketCliente* pSocket){

	std::string nombreProtagonista = juego.protagonista.entidad;
	ParserYaml::stEntidad entidadProtagonista = ParserYaml::getInstance().buscarStEntidad(juego.listaEntidades,nombreProtagonista);

	double tamanioX = (double)juego.escenario.tamanioX;
	double tamanioY = (double)juego.escenario.tamanioY;
	double x = (double)juego.protagonista.x;
	double y = (double)juego.protagonista.y;
	double alto = (double)entidadProtagonista.altoBase;
	double ancho = (double)entidadProtagonista.anchoBase;
	double posicionReferenciaX = (double)entidadProtagonista.pixelReferenciaX;
	double posicionReferenciaY = (double)entidadProtagonista.pixelReferenciaY;
	double fps = (double)entidadProtagonista.fps;
	double delay = (double)entidadProtagonista.delay;
	std::list<std::list<std::string>> listaAnimaciones = entidadProtagonista.imagenes;

	VistaEntidad* pJugador = new VistaEntidad(x,y,alto,ancho,posicionReferenciaX,posicionReferenciaY,fps,delay,listaAnimaciones,true,tamanioX,tamanioY,juego.idJugador);
	VistaScroll* pScroll = new VistaScroll(x,y,juego.pantalla.alto,juego.pantalla.ancho,tamanioX,tamanioY,pantalla,juego.idJugador);	// Tomo el mismo x,y,velocidad que el personaje
	vistaNivel.agregarJugador(pJugador);
	vistaNivel.agregarScroll(pScroll);
	vistaNivel.agregarTamanioNivel(tamanioX,tamanioY);

	return void();
}

void VistaFactory::crearEntidades(stVistaJuegoElegido& juego, VistaNivel& vistaNivel){

	std::list<ParserYaml::stEntidadDefinida> entidadesDef = juego.escenario.entidadesDefinidas;

	for (std::list<ParserYaml::stEntidadDefinida>::iterator it=entidadesDef.begin() ; it != entidadesDef.end(); it++ ){	

		ParserYaml::stEntidadDefinida entidadDef = (*it);
		std::string nombreEntidad = entidadDef.entidad;
		ParserYaml::stEntidad entidad = ParserYaml::getInstance().buscarStEntidad(juego.listaEntidades,nombreEntidad);

		double tamanioX = (double)juego.escenario.tamanioX;
		double tamanioY = (double)juego.escenario.tamanioY;
		double x = (double)entidadDef.x;
		double y = (double)entidadDef.y;
		double alto = (double)entidad.altoBase;
		double ancho = (double)entidad.anchoBase;
		double posicionReferenciaX = (double)entidad.pixelReferenciaX;
		double posicionReferenciaY = (double)entidad.pixelReferenciaY;
		double fps = (double)entidad.fps;
		double delay = (double)entidad.delay;
		std::list<std::list<std::string>> listaAnimaciones = entidad.imagenes;

		VistaEntidad* pEntidad = new VistaEntidad(x,y,alto,ancho,posicionReferenciaX,posicionReferenciaY,fps,delay,listaAnimaciones,false,tamanioX,tamanioY,juego.idJugador);
		vistaNivel.agregarEntidad(pEntidad);

	}

	return void();
}

bool VistaFactory::crearElementosControlador(stVistaJuegoElegido& juego,VistaNivel& vistaNivel,VistaLoop& vistaLoop,ControladorEvento* evento,SocketCliente* pSocket){

	// Seteo el ID del jugador en el Evento
	evento->setIdJugador(juego.idJugador);

	// Creo el Scroll
	this->crearControladorScroll(juego,evento);
	
	// Creo el Proxy
	this->crearProxyControladorEvento(evento,pSocket);

	// Vinculo el VistaScroll con el ControladorScroll
	this->vincularScroll(vistaNivel,evento);

	return true;
}

void VistaFactory::crearControladorScroll(stVistaJuegoElegido& juego,ControladorEvento* evento){
	int x = juego.protagonista.x;
	int y = juego.protagonista.y;
	int anchoEscenario = juego.escenario.tamanioX;
	int altoEscenario = juego.escenario.tamanioY;

	ControladorScroll* pScroll = new ControladorScroll(juego.pantalla.ancho,juego.pantalla.alto,anchoEscenario,altoEscenario,juego.configuracion.margenScroll,x,y);
	evento->setControladorScroll(pScroll);

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

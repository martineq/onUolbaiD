#include "VistaFactory.h"

VistaFactory::VistaFactory(void){

}

VistaFactory::~VistaFactory(void){

}

bool VistaFactory::crearNivel(VistaNivel& vistaNivel,ControladorEvento* evento,SocketCliente* pSocket,SDL_Surface** pPantallaDestino, ProxyModeloEntidad** pProxyDestino,std::string mote,std::string personaje){

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

	if( ImageLoader::getInstance().iniciarSDL() == false ) return false;
	SDL_Surface* pPantallaSDL = ImageLoader::getInstance().levantarPantalla(this->juegoElegido.pantalla.ancho,this->juegoElegido.pantalla.alto);

	// Recibo datos desde el Servidor
	if( this->recibirEscenario(juegoYaml.escenarios,pSocket) == false ) return false;
	//	this->menuSeleccionUsuarioPersonaje(mote,personaje);
	if( this->recibirProtagonista(pSocket,mote,personaje) == false ) return false;
	if( this->recibirOtrosJugadores(vistaNivel,pSocket) == false ) return false;

	pSocket->setEnvioIndirecto();

	// Creo los elementos de la Vista
	if( this->crearElementosVista(pPantallaSDL,vistaNivel,pSocket,pPantallaDestino,pProxyDestino) == false ) return false;

	// Creo los elementos del Controlador
	if( this->crearElementosControlador(vistaNivel,evento,pSocket) == false ) return false;

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

	double tiempoInicial = Temporizador::getInstance().obtenerTics();

	// Recibo los archivos de configuracion
	if( this->recibirListaDeArchivos(DIRECTORIO_IMG,pSocket) == false) return false;

	// Recibo los archivos de imagenes
	if( this->recibirListaDeArchivos(DIRECTORIO_CONFIG,pSocket) == false) return false;

	double tiempoFinal = Temporizador::getInstance().obtenerTics();
	double tiempoTranscurrido =  ( tiempoFinal - tiempoInicial ) / 1000;
	std::cout << "Tiempo para recepcion de archivos: " << tiempoTranscurrido << " segundos. " << std::endl;

	return true;
}

bool VistaFactory::recibirListaDeArchivos(const char* directorioElegido,SocketCliente* pSocket){

	Serializadora s;
	if( pSocket->recibir(s) == false ) return false;
	
	// Hidrato el vector de strings y recibo cada archivo
	int cantidadDeArchivos = 0;
	cantidadDeArchivos = s.getInt();
	for ( int i=0 ; i < cantidadDeArchivos ; i++ ){
		std::string rutaDestino(s.getString());
		if ( pSocket->recibirArchivo(rutaDestino.c_str()) == false) return false; // Recibo el archivo binario
	}
	return true;
}

bool VistaFactory::recibirEscenario(std::list<ParserYaml::stEscenario>& listaEscenarios,SocketCliente* pSocket){

	Serializadora s;
	if( pSocket->recibir(s) == false ) return false;

	// Comienzo a hidratar. Hidrato el nombre de escenario
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

// Recibe los datos del protagonista elegido y los setea, pero no lo crea (se hace luego, en crearNivel() )
bool VistaFactory::recibirProtagonista(SocketCliente* pSocket,std::string nombreUsuario,std::string nombrePersonaje){

	// Serializo los nombres de usuario y protagonista, luego lo envio al servidor
	Serializadora s;
	s.addString(nombreUsuario);
	s.addString(nombrePersonaje);
	if( pSocket->enviar(s) == false ) return false;

	// Recibo al protagonista, y dejo cargado los datos para su posterior creación
	ProxyModeloEntidad::stEntidad entidad;
	ProxyModeloEntidad proxy;
	proxy.setSocketCliente(pSocket);
	if( proxy.recibirEntidadIndividual(entidad) == false ) return false;	// Si hubo error de sockets me voy
	this->juegoElegido.entidadJugador = entidad;

	return true;
}

// Puedo usar esto si lo necesito. Creo no va a hacer falta
void VistaFactory::menuSeleccionUsuarioPersonaje(std::string& nombreUsuario,std::string& nombrePersonaje){

	// El cliente elije su nombre
	std::cout << "Elija el nombre de usuario: " << std::endl;
	getline (std::cin,nombreUsuario);

	// El cliente elije su personaje
	std::list<ParserYaml::stProtagonista> listaProtagonistas = this->juegoElegido.escenario.protagonistas;
	std::cout << "Seleccion de personaje: " << std::endl;
	bool yaEligio = false;

	while( yaEligio == false){
		for (std::list<ParserYaml::stProtagonista>::iterator it=listaProtagonistas.begin() ; (it != listaProtagonistas.end()) && (yaEligio == false) ; it++ ){
			std::string opc;
			std::cout << "Elije el personaje: "<< (*it).entidad << " ? (s) para confirmar, otra tecla para rechazar" << std::endl;
			getline (std::cin,opc);
			if( opc.compare("s") == 0 || opc.compare("S") == 0 ){
				std::cout << "Se eligio el personaje: "<< (*it).entidad << std::endl;
				nombrePersonaje = (*it).entidad;
				yaEligio = true;
			}
		}
	}

	return void();
}

// Instancia a todos los jugadores que no son controlados por este cliente
bool VistaFactory::recibirOtrosJugadores(VistaNivel& vistaNivel,SocketCliente* pSocket){

	Serializadora s;
	if( pSocket->recibir(s) == false ) return false;

	// Hidrato la cantidad de personajes que me van a mandar
	int cantidadOtrosJugadores = s.getInt();

	// Recibo los datos de los jugadores, a través de un proxy
	ProxyModeloEntidad proxy;
	proxy.setSocketCliente(pSocket);
	ProxyModeloEntidad::stEntidad entidad;
	for ( unsigned int i=0 ; i<cantidadOtrosJugadores ; i++ ){ 
		if( proxy.recibirEntidadIndividual(entidad) == false ) return false;
		this->crearJugadorSinScroll(vistaNivel,entidad);
	}

	return true; 
}

bool VistaFactory::crearElementosVista(SDL_Surface* pPantallaSDL, VistaNivel& vistaNivel,SocketCliente* pSocket, SDL_Surface** pPantallaDestino, ProxyModeloEntidad** pProxyDestino){

	// Inicio y seteo de SDL
	//vistaLoop.setPantalla(pPantallaSDL);
	(*pPantallaDestino) = pPantallaSDL;

	// Seteo medidas de pantalla
	vistaNivel.setAltoDePantallaEnPixel(this->juegoElegido.pantalla.alto);
	vistaNivel.setAltoDePantallaEnPixel(this->juegoElegido.pantalla.ancho);

	// Seteo el ProxyModeloEntidad
	ProxyModeloEntidad* pProxyEntidad = new ProxyModeloEntidad();
	pProxyEntidad->setSocketCliente(pSocket);
	//vistaLoop.SetProxyModeloEntidad(pProxyEntidad);
	(*pProxyDestino) = pProxyEntidad;

	// Creo al protagonista y a las entidades (no creo a otros jugadores)
	this->crearJugadorConScroll(vistaNivel,pPantallaSDL);
	this->crearEntidadesNoJugadores(vistaNivel);

	return true;
}

void VistaFactory::crearJugadorConScroll(VistaNivel& vistaNivel,SDL_Surface* pantalla){
 
	std::string nombreProtagonista = this->juegoElegido.entidadJugador.nombreEntidad;
	ParserYaml::stEntidad entidadProtagonista = ParserYaml::getInstance().buscarStEntidad(this->juegoElegido.listaEntidades,nombreProtagonista);
	
	// Valores tomados desde el protagonista selecionado (y cargado) anteriormente
	double x = (double)this->juegoElegido.entidadJugador.posicionSiguienteX;
	double y = (double)this->juegoElegido.entidadJugador.posicionSiguienteY;
	int id = this->juegoElegido.entidadJugador.id;
	// TODO: Faltan actualizar estos valores:
	//this->juegoElegido.entidadJugador.actualizacionMapa;
	//this->juegoElegido.entidadJugador.direccion;
	//this->juegoElegido.entidadJugador.esUltimoMovimiento;
	//this->juegoElegido.entidadJugador.entidadCongelada;  <<< En este caso es == false

	// Valores tomados desde la entidad
	double alto = (double)entidadProtagonista.altoBase;
	double ancho = (double)entidadProtagonista.anchoBase;
	double posicionReferenciaX = (double)entidadProtagonista.pixelReferenciaX;
	double posicionReferenciaY = (double)entidadProtagonista.pixelReferenciaY;
	double fps = (double)entidadProtagonista.fps;
	double delay = (double)entidadProtagonista.delay;
	std::string nombre = entidadProtagonista.nombre;
	std::list<std::list<std::string>> listaAnimaciones = entidadProtagonista.imagenes;

	// Valores tomados desde el escenario
	double tamanioX = (double)this->juegoElegido.escenario.tamanioX;
	double tamanioY = (double)this->juegoElegido.escenario.tamanioY;

	VistaEntidad* pJugador = new VistaEntidad(x,y,alto,ancho,posicionReferenciaX,posicionReferenciaY,fps,delay,listaAnimaciones,true,tamanioX,tamanioY,id,nombre);
	VistaScroll* pScroll = new VistaScroll(x,y,this->juegoElegido.pantalla.alto,this->juegoElegido.pantalla.ancho,tamanioX,tamanioY,pantalla,id);	// Tomo el mismo x,y,velocidad que el personaje
	vistaNivel.agregarJugador(pJugador);
	vistaNivel.agregarScroll(pScroll);
	vistaNivel.agregarTamanioNivel(tamanioX,tamanioY);

	return void();
}

void VistaFactory::crearJugadorSinScroll(VistaNivel& vistaNivel,ProxyModeloEntidad::stEntidad& entidad){

	std::string nombreJugador = entidad.nombreEntidad;
	ParserYaml::stEntidad entidadJugador = ParserYaml::getInstance().buscarStEntidad(this->juegoElegido.listaEntidades,nombreJugador);

	// Valores tomados desde el proxy
	int id = entidad.id;
	double x = (double)entidad.posicionSiguienteX;
	double y = (double)entidad.posicionSiguienteY;	
	//entidad.direccion				// <<< TODO: Para el primer seteo ¿hace falta? Si hace falta, implementarlo.
	//entidad.esUltimoMovimiento	// <<< Para el primer seteo ¿hace falta? Si hace falta, implementarlo.

	// Valores tomados desde la entidad
	double alto = (double)entidadJugador.altoBase;
	double ancho = (double)entidadJugador.anchoBase;
	double posicionReferenciaX = (double)entidadJugador.pixelReferenciaX;
	double posicionReferenciaY = (double)entidadJugador.pixelReferenciaY;
	double fps = (double)entidadJugador.fps;
	double delay = (double)entidadJugador.delay;
	std::list<std::list<std::string>> listaAnimaciones = entidadJugador.imagenes;
	std::string nombre = entidadJugador.nombre;

	// Valores tomados desde el escenario elegido
	double tamanioX = (double)this->juegoElegido.escenario.tamanioX;
	double tamanioY = (double)this->juegoElegido.escenario.tamanioY;

	VistaEntidad* pJugador = new VistaEntidad(x,y,alto,ancho,posicionReferenciaX,posicionReferenciaY,fps,delay,listaAnimaciones,true,tamanioX,tamanioY,id,nombre);
	//vistaNivel.agregarEntidad(pJugador);
	vistaNivel.agregarOtroJugador(pJugador);
	return void();
}

void VistaFactory::crearEntidadesNoJugadores(VistaNivel& vistaNivel){

	std::list<ParserYaml::stEntidadDefinida> entidadesDef = this->juegoElegido.escenario.entidadesDefinidas;
	std::list<int>idEntidadesDef = this->juegoElegido.listaIdEntidades;

	for (std::list<ParserYaml::stEntidadDefinida>::iterator it=entidadesDef.begin() ; it != entidadesDef.end(); it++ ){	

		ParserYaml::stEntidadDefinida entidadDef = (*it);
		std::string nombreEntidad = entidadDef.entidad;
		ParserYaml::stEntidad entidad = ParserYaml::getInstance().buscarStEntidad(this->juegoElegido.listaEntidades,nombreEntidad);

		// Valores tomados desde la entidad definida
		double x = (double)entidadDef.x;
		double y = (double)entidadDef.y;

		// Valores tomados desde la entidad
		double alto = (double)entidad.altoBase;
		double ancho = (double)entidad.anchoBase;
		double posicionReferenciaX = (double)entidad.pixelReferenciaX;
		double posicionReferenciaY = (double)entidad.pixelReferenciaY;
		double fps = (double)entidad.fps;
		double delay = (double)entidad.delay;
		std::list<std::list<std::string>> listaAnimaciones = entidad.imagenes;
		std::string nombre = entidad.nombre;

		// Valores tomados desde el escenario elegido
		double tamanioX = (double)this->juegoElegido.escenario.tamanioX;
		double tamanioY = (double)this->juegoElegido.escenario.tamanioY;

		// Valores tomados desde el servidor, cargados posteriormente en una variable
		int id = idEntidadesDef.front();

		VistaEntidad* pEntidad = new VistaEntidad(x,y,alto,ancho,posicionReferenciaX,posicionReferenciaY,fps,delay,listaAnimaciones,false,tamanioX,tamanioY,id,nombre);
		vistaNivel.agregarEntidad(pEntidad);

		idEntidadesDef.pop_front();	// Una vez que usé el ID lo destruyo para tener acceso al próximo
	}

	return void();
}

bool VistaFactory::crearElementosControlador(VistaNivel& vistaNivel,ControladorEvento* evento,SocketCliente* pSocket){

	// Seteo el ID del jugador en el Evento
	evento->setIdJugador(this->juegoElegido.entidadJugador.id);

	// Creo el Scroll
	this->crearControladorScroll(evento);
	
	// Creo el Proxy
	this->crearProxyControladorEvento(evento,pSocket);

	// Vinculo el VistaScroll con el ControladorScroll
	this->vincularScroll(vistaNivel,evento);

	return true;
}

void VistaFactory::crearControladorScroll(ControladorEvento* evento){
	
	// Valores tomados desde el protagonista selecionado (y cargado) anteriormente
	int x = this->juegoElegido.entidadJugador.posicionSiguienteX;
	int y = this->juegoElegido.entidadJugador.posicionSiguienteY;

	// Valores tomados desde el escenario elegido
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

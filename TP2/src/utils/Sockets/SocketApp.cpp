#include "SocketApp.h"

SocketApp::SocketApp(void){
	this->miSocket = INVALID_SOCKET;	// Corresponde a inicialar el socket
}

SocketApp::~SocketApp(void){

}

// Inicia la estructura winsock
bool SocketApp::iniciarAplicacion(void){

	std::cout << "Iniciando winsock... ";
	Log::getInstance().log(3,__FILE__,__LINE__,"Iniciando winsock... " );
	if (WSAStartup(MAKEWORD(VERSION_WINSOCK_REQUERIDA,0), &(this->infoDeSocket))==0){
		// Chequea si la mayor versión es por lo menos VERSION_WINSOCK_REQUERIDA
		if (LOBYTE(this->infoDeSocket.wVersion) >= VERSION_WINSOCK_REQUERIDA){
			std::cout << "iniciado.\n";
			Log::getInstance().log(3,__FILE__,__LINE__, "iniciado.");
		}else{
			std::cerr << "Version de winsock requerida no soportada!";
			Log::getInstance().log(3,__FILE__,__LINE__, "Version de winsock requerida no soportada!");
			return false;
		}
	}else{
		std::cerr << "Comienzo fallido!\n";
		Log::getInstance().log(3,__FILE__,__LINE__, "Comienzo fallido!");
		return false;
	}

	return true;
}

// Finaliza y limpia Winsock
bool SocketApp::finalizarAplicacion(void){
	if (this->miSocket!=INVALID_SOCKET){ 
		if (WSACleanup()!=0){
			Log::getInstance().log(3,__FILE__,__LINE__, "limpieza fallida!");
			return false;
		}   
	}
	Log::getInstance().log(3,__FILE__,__LINE__, "listo.");
	return true;
}	

// Crea el socket para su posterior uso
bool SocketApp::abrir(void){

	//if(this->iniciarAplicacion() == false) return false;
	
	std::cout << "Creando el socket... ";
	Log::getInstance().log(3,__FILE__,__LINE__,"Creando el socket... " );
	if ((this->miSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET){
		std::cerr << "No se pudo crear el socket.\n";
		Log::getInstance().log(1,__FILE__,__LINE__,"No se pudo crear el socket." );
		return false;
	}
	std::cout << "creado.\n";
	Log::getInstance().log(1,__FILE__,__LINE__,"Conexion creada" );

	std::cout << "Conexion creada \n";

	return true;
}

// Cierra el socket
bool SocketApp::cerrar(void){

	std::cout << "Cerrando Conexion. \n";

	if (this->miSocket!=INVALID_SOCKET){ 
		closesocket(this->miSocket); // Cierro el socket
	}else{
		//Log::getInstance().log(3,__FILE__,__LINE__, "No se pudo cerrar el socket!");
		return false;
	}

	return true;
}	

// Devuelve el número de IP del nombre de servidor pasado por parámetro
// Si no puede resolver, devuelve cero
unsigned long SocketApp::buscarIpDeHost(const char *nombreHost){
	HOSTENT *pHostent;

	// Obtiene la estructura hostent para el hostname:
	if (!(pHostent = gethostbyname(nombreHost))){
		std::cerr << "no se puede resolver el nombre de host." << std::endl;
		Log::getInstance().log(3,__FILE__,__LINE__, "no se puede resolver el nombre de host.");
		return -1;
	}

	// Extrae la dirección IP principal de la estructura hostent:
	if (pHostent->h_addr_list && pHostent->h_addr_list[0]){
		return *reinterpret_cast<unsigned long*>(pHostent->h_addr_list[0]);
	}else{
		return -1;
	}

	return -1;
}

// Obtiene un string con IP:Puerto
std::string SocketApp::obtenerDescripcionDeHost(const sockaddr_in &direccionSocket){
	std::ostringstream stream;
	stream << inet_ntoa(direccionSocket.sin_addr) << ":" << ntohs(direccionSocket.sin_port);
	return stream.str();
}

// Setea familia, puerto e IP
void SocketApp::llenarDireccionDeSocket(sockaddr_in *pDireccionSocket, int puerto){
	pDireccionSocket->sin_family = AF_INET;			// Setea IPv4 
	pDireccionSocket->sin_port = htons(puerto);		// Setea el puerto
	pDireccionSocket->sin_addr.S_un.S_addr = INADDR_ANY;
}

// Setea familia, puerto y encuentra el IP
bool SocketApp::llenarDireccionDeSocket(sockaddr_in *pDireccionSocket, int puerto, const char* nombreHost){	
	pDireccionSocket->sin_family = AF_INET;				// Setea IPv4 
	pDireccionSocket->sin_port = htons(puerto);			// Setea el puerto
	unsigned long ipHost = buscarIpDeHost(nombreHost);
	if ( ipHost == -1 ) return false;
	pDireccionSocket->sin_addr.S_un.S_addr = ipHost;	// Setea la dirección IP
	return true;
}

void SocketApp::setSocket(SOCKET socket){
	this->miSocket = socket;
}

int SocketApp::miRecv(char *buf,int longitud,int flags){

	int valSel = this->selectLectura(0);
	if ( valSel > 0 ){
		 return recv(this->miSocket,buf,longitud,flags);
	}else{
		std::cerr <<"Error de socket: Timeout mientras se recibia."<<std::endl;
		Log::getInstance().log(3,__FILE__,__LINE__, "Error de socket: Timeout mientras se recibia.");
		return valSel;
	}
	return valSel;
}

int SocketApp::miSend(const char *buf,int longitud,int flags){

	int valSel = this->selectEscritura(0);
	if ( valSel > 0 ){
		return send(this->miSocket,buf,longitud,flags);
	}else{
		std::cerr <<"Error de socket Timeout mientras se enviaba."<<std::endl;
		Log::getInstance().log(3,__FILE__,__LINE__, "Error de socket Timeout mientras se enviaba.");
		return false;
	}
}

// Wrapper para el recv() de winsock, con agregado de funciones
// Si se reciben mas de <longitud> bytes, no se tendran en cuenta
bool SocketApp::recvFull(char *buf,int longitud,int flags){

   int totalAcumulado = 0, bytesRecibidos = 0;
   while ( (totalAcumulado < longitud) && ((bytesRecibidos = this->miRecv(buf+totalAcumulado,longitud-totalAcumulado,0)) > 0)) {
	   totalAcumulado += bytesRecibidos;
   }

   // Si salió por ser bytesRecibidos igual o menor a cero
	if (bytesRecibidos==0){	
		std::cerr <<"Error de socket mientras se recibia."<<std::endl;
		Log::getInstance().log(3,__FILE__,__LINE__, "Error de socket mientras se recibia"); //, ID:", this->getId());
		return false; 
	}else{
		if (bytesRecibidos==SOCKET_ERROR){
			Log::getInstance().log(3,__FILE__,__LINE__, "Error de socket mientras se recibia"); //. ID:", this->getId());
			return false;
		}
	}

	return true;
}

// Wrapper para el send() de winsock, con agregado de funciones
bool SocketApp::sendFull(const char *buf,int longitud,int flags){
	
	std::vector<char> buffer;					// Buffer que se usará para el envio
	const char* posFinal = buf + longitud;		// Calculo la posición final de buf
	buffer.insert(buffer.end(),buf,posFinal);	// Mando el char* al vector<char> que uso de buffer

	// Itera mientras tenga datos para enviar en el buffer
	while ( buffer.empty() == false ){
		int bytesEnviados = this->miSend(&buffer[0],(int)buffer.size(),flags);
		if (bytesEnviados==0){	// Esto no tendría que pasar
			std::cerr <<"Error de socket mientras se enviaba."<<std::endl;
			Log::getInstance().log(3,__FILE__,__LINE__, "Error de socket mientras se enviaba.");
			return false; 
		}else{
			if (bytesEnviados==SOCKET_ERROR){ // Caso típico: se desconecta el cable de conexión
				std::cerr <<"Error de socket mientras se enviaba."<<std::endl;
				Log::getInstance().log(3,__FILE__,__LINE__, "Error de socket mientras se enviaba.");
				return false;
			}else{
				if (bytesEnviados > 0){  // Borro del buffer los datos que se enviaron bien
					buffer.erase(buffer.begin(),buffer.begin()+bytesEnviados);
				}
			}
		}
	}

	return true;
}

// Envía la cadena de chars apuntada por <*pBuffer>, de tamaño <tamanio>, al Socket asociado <socket>
// Devuelve true si el envío fue exitoso y false en caso de error de envío
bool SocketApp::enviar(const char *pBuffer,unsigned int tamanio){
	unsigned int longitud = tamanio;	// Se puso en un principio para asegurar el tipo de variable

	// Envio la longitud del archivo
	if (this->sendFull( reinterpret_cast<char*>(&longitud), sizeof (longitud) , 0) == false) return false;
	if (this->sendFull(pBuffer,tamanio,0) == false) return false;
	return true;
}

// Recibe una cadena de chars del Socket asociado <socket>
// Si el envío fue exitoso devuelve true, junto el puntero válido a una cadena en <pBuffer> instanciada dinámicamente (en el heap), y el <tamanio> recibido
// En caso de error devuelve false y un <tamanio> = 0
bool SocketApp::recibir(char **pBuffer,unsigned int& tamanio){
	// Recibo la longitud de la cadena de datos
	unsigned int longitud;
	if( this->recvFull( reinterpret_cast<char*>(&longitud), sizeof(longitud), 0) == false ){
		tamanio = 0;
		return false;
	}

	// Creo el buffer y recibo los datos
	(*pBuffer) = new char[longitud]; 
	if( this->recvFull( *pBuffer,longitud, 0) == false ){ // Recibo los datos en tempBuffer
		delete[] (*pBuffer);
		tamanio = 0;
		return false;	
	}
	tamanio = longitud;

	return true;
}

// Hace el enlazado (bind) del socket
bool SocketApp::enlazarConexion(int puerto){
	
	// Struct que se usa para cargar los datos de la dirección, puerto, etc.
	sockaddr_in	sockAddr = {0};

	// Enlazando el socket
	std::cout << "Enlazando el socket (bind)... ";
	Log::getInstance().log(3,__FILE__,__LINE__,"Enlazando el socket (bind)... " );
	this->llenarDireccionDeSocket(&sockAddr, puerto);
	if (bind(this->miSocket, reinterpret_cast<sockaddr*>(&sockAddr), sizeof(sockAddr))!=0){
		std::cerr << "No se pudo enlazar el socket del servidor.\n";
		Log::getInstance().log(3,__FILE__,__LINE__,"No se pudo enlazar el socket del servidor." );
		return false;
	}
	std::string txt("enlazado. (" + this->obtenerDescripcionDeHost(sockAddr)+")");
	std::cout << txt <<std::endl;
	Log::getInstance().log(3,__FILE__,__LINE__, txt);
	return true;
}

// Pone el socket del servidor en modo de escucha, para luego poder aceptar clientes
bool SocketApp::escuchar(void){
	
	std::cout << "Poniendo el socket en modo de escucha... ";
	Log::getInstance().log(3,__FILE__,__LINE__,"Poniendo el socket en modo de escucha... " );
	if (listen(this->miSocket, SOMAXCONN)!=0){
		std::cerr << "No se pudo poner el socket en modo de escucha.\n";
		Log::getInstance().log(3,__FILE__,__LINE__,"No se pudo poner el socket en modo de escucha." );
		return false;
	}
	std::cout << "listo.\n";
	Log::getInstance().log(3,__FILE__,__LINE__,"listo." );
	return true;
}

// Inicio el socket de un cliente y lo agrego a mi lista de clientes
bool SocketApp::aceptarCliente(SOCKET& socket){

	// Creo un struct de dirección de socket para el cliente, lo requiere a función accept()
	sockaddr_in direccionSocketCliente;
	int	tamanioDireccionSocketCliente = sizeof(direccionSocketCliente);

	// Acepto la conexion
	std::cout << "Esperando por conexion entrante... \n";
	Log::getInstance().log(3,__FILE__,__LINE__,"Esperando por conexion entrante... " );

	socket = accept(this->miSocket, reinterpret_cast<sockaddr*>(&direccionSocketCliente), &tamanioDireccionSocketCliente);
 
	// Chequea si se acepto la conexión
	if (socket==INVALID_SOCKET){
		Log::getInstance().log(3,__FILE__,__LINE__,"La funcion aceptar clientes del servidor ha fallado." );
		return false;
	}else{
		Log::getInstance().log(3,__FILE__,__LINE__, "aceptada.");
	}

	// Imprime la descripción (IP:port) del cliente conectado
	std::string txt("Cliente conectado con " + this->obtenerDescripcionDeHost(direccionSocketCliente) + ".");
	std::cout << txt;
	Log::getInstance().log(3,__FILE__,__LINE__, txt);
	return true;
}

bool SocketApp::selectEscritura(int microsegundos){

	struct timeval tv; // Variable que puede usarse como último parámetro de la función select() para setear el tiempo de espera
	int valorSelect = 0;
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(this->miSocket,&fds);
	tv.tv_sec = 0; // Seteo los segundos de espera
	tv.tv_usec = microsegundos; // Seteo los microsegundos de espera

	if ( microsegundos > 0 ){
		valorSelect = select(NULL,NULL,&fds,NULL,&tv);
	}else{
		valorSelect = select(NULL,NULL,&fds,NULL,NULL); // Con el último NULL espera infinito, bloqueandose hasta que venga algo. Sino defino el tiempo con &tv.
	}

	if ( valorSelect > 0 ){
		return true;
	}else{
		return false;
	}

}

bool SocketApp::selectLectura(int microsegundos){

	struct timeval tv; // Variable que puede usarse como último parámetro de la función select() para setear el tiempo de espera
	int valorSelect = 0;
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(this->miSocket,&fds);
	tv.tv_sec = 0; // Seteo los segundos de espera
	tv.tv_usec = microsegundos; // Seteo los microsegundos de espera

	if ( microsegundos > 0 ){
		valorSelect = select(NULL,&fds,NULL,NULL,&tv);
	}else{
		valorSelect = select(NULL,&fds,NULL,NULL,NULL); // Con el último NULL espera infinito, bloqueandose hasta que venga algo. Sino defino el tiempo con &tv.
	}

	if ( valorSelect > 0 ){
		return true;
	}else{
		return false;
	}

}

// Conecta con el servidor, luego envía y recibe un mensaje
bool SocketApp::conectar(const char* nombreHost, int puerto){
	sockaddr_in	sockAddr = {0};				// Estructura que guarda versoin de IP, puerto y dirección IP

	// Busca el hostname y llena la estructura sockaddr_in:
	std::string txt("Buscando el nombre de host " + (std::string)nombreHost + "... ");
	std::cout << txt;
	Log::getInstance().log(3,__FILE__,__LINE__,txt );
	if ( this->llenarDireccionDeSocket(&sockAddr, puerto, nombreHost) == false ){
		Log::getInstance().log(3,__FILE__,__LINE__, "Error en la direccion de socket.");
		return false;
	}
	std::cout << "encontrado.\n";
	Log::getInstance().log(3,__FILE__,__LINE__, "encontrado.");

	// Conecta al servidor
	txt.assign("Intentando conectarse a " + (std::string)inet_ntoa(sockAddr.sin_addr) + ":" );
	std::cout << txt;
	Log::getInstance().log(3,__FILE__,__LINE__, txt,puerto);
	if (connect( this->miSocket, reinterpret_cast<sockaddr*>(&sockAddr), sizeof(sockAddr))!=0){ // Conecta al servidor
		std::cerr << "No se pudo conectar.\n";
		Log::getInstance().log(3,__FILE__,__LINE__, "No se pudo conectar.");
		return false;
	}
	std::cout << "conectado.\n";
	Log::getInstance().log(3,__FILE__,__LINE__,"conectado." );

	return true;
}	

bool SocketApp::enviarArchivo(const char *rutaOrigen){

	// Calculo la longitud y cargo el archivo en una variable
	unsigned long int longitud; 
	std::ifstream archivoEntrada;
	archivoEntrada.open (rutaOrigen, std::ios::binary ); 
	if( archivoEntrada.is_open() ){;} // printf("Archivo abierto.\n");
    archivoEntrada.seekg (0, std::ios::end); 
    longitud = archivoEntrada.tellg(); 
    archivoEntrada.seekg (0, std::ios::beg); 
    char *pBuffer = new char [longitud]; 
    archivoEntrada.read (pBuffer, longitud); 
    archivoEntrada.close(); 

	// Envio la longitud del archivo al cliente
	if ( this->enviar(reinterpret_cast<char*>(&longitud), sizeof (longitud) ) == false) return false;

	// Envio el archivo
	unsigned long int offset, bytesEnviados = 0, bloque = TAMANIO_BLOQUE; 
	for(offset = 0; bloque == TAMANIO_BLOQUE; offset += TAMANIO_BLOQUE){ 
		if (longitud - offset < TAMANIO_BLOQUE) bloque = longitud - offset; 
		if ( this->enviar(pBuffer+offset,bloque) == false ) return false;
		bytesEnviados += bloque;
	}

	delete[] pBuffer; 
	return true;
}

bool SocketApp::recibirArchivo(const char *rutaDestino){

	// Recibo la longitud del archivo
	unsigned long int longitud;
	std::ofstream salida(rutaDestino,std::ios::binary); 

	unsigned int tam; // En esta función solo la uso para poder usar recibir()
	char* cadena = NULL;
	if( this->recibir(&cadena,tam)==true ){
		if (tam<=0){ std::cout<<"Error al recibir archivo"; return false;}
		longitud = *((unsigned long int*)cadena);
		delete[] cadena;
	}else{
		return false;
	}

	char *pbuf = new char [longitud]; 
	// Recibo el archivo
	unsigned long int ofs, bytesRecibidos = 0, block = TAMANIO_BLOQUE; 
    for(ofs = 0; block == TAMANIO_BLOQUE; ofs += TAMANIO_BLOQUE){ 
        if (longitud - ofs < TAMANIO_BLOQUE) block = longitud - ofs; 
		if (this->recibir(&cadena,tam) == false ){
			delete[] pbuf;  // En el caso de false
			return false;
		}
		memcpy(pbuf+ofs,cadena,block);
		delete[] cadena;
		bytesRecibidos += block;
    }
    salida.write(pbuf,longitud); 
    salida.close(); 
    delete[] pbuf; 
	return true;
}

#include "ConexionCliente.h"

ConexionCliente::ConexionCliente(void){
	this->id = Ticket::getInstance().pedirNumero();
	this->mutexEsIndividual.lockEscritura(__FILE__,__LINE__);
	this->esIndividual = true;									// La conexión arranca siendo individual, luego se puede poner masiva en caso en caso de ser una conexion perteneciente a un servidor
	this->mutexEsIndividual.unlock(__FILE__,__LINE__);
}

ConexionCliente::~ConexionCliente(void){

}

bool ConexionCliente::iniciarAplicacion(void){
	return this->socketApp.iniciarAplicacion();
}

bool ConexionCliente::finalizarAplicacion(void){
	return this->socketApp.finalizarAplicacion();
}	

bool ConexionCliente::abrir(void){
	return this->socketApp.abrir();
}

bool ConexionCliente::cerrar(void){
	return this->socketApp.cerrar();
}

void ConexionCliente::cerrarActividad(void){
	this->hiloEntrada.detenerActividad();
	this->hiloSalida.detenerActividad();	
	this->hiloEntrada.join();
	this->hiloSalida.join();
}	

void ConexionCliente::iniciarRecepcion(std::list<std::string>* colaEntradaMasiva,Mutex* mutexColaEntradaMasiva, std::list<long>* clientesMasivosConError){
	this->hiloEntrada.correrConexion(iniciarParametrosRun('E',colaEntradaMasiva,mutexColaEntradaMasiva,clientesMasivosConError));
}

void ConexionCliente::iniciarEnvio(void){
	this->hiloSalida.correrConexion(iniciarParametrosRun('S',NULL,NULL,NULL));
}

int ConexionCliente::getId(void){
	return this->id;
}

void ConexionCliente::setEsIndividual(void){
	this->mutexEsIndividual.lockEscritura(__FILE__,__LINE__);
	this->esIndividual = true;
	this->mutexEsIndividual.unlock(__FILE__,__LINE__);

}

void ConexionCliente::setMasiva(void){
	this->mutexEsIndividual.lockEscritura(__FILE__,__LINE__);
	this->esIndividual = false;
	this->mutexEsIndividual.unlock(__FILE__,__LINE__);
}

bool ConexionCliente::getEsIndividual(void){
	bool estado;
	this->mutexEsIndividual.lockLectura(__FILE__,__LINE__);
	estado = this->esIndividual;
	this->mutexEsIndividual.unlock(__FILE__,__LINE__);
	return estado;
}

// Conecta con el servidor, luego envía y recibe un mensaje
bool ConexionCliente::conectar(const char* nombreHost, int puerto){
	return this->socketApp.conectar(nombreHost,puerto);
}

bool ConexionCliente::enviarDirecto(const char *pBuffer,unsigned int tamanio){
	return this->socketApp.enviar(pBuffer,tamanio);
}

bool ConexionCliente::recibirDirecto(char **pBuffer,unsigned int& tamanioRecibido){
	return this->socketApp.recibir(pBuffer,tamanioRecibido);
}

bool ConexionCliente::enviar(const char *pBuffer,unsigned int tamanio){

	// Chequeo que el hilo se encuentre funcionando
	if ( this->hiloSalida.estaActivo() == false) return false;

	std::string str(pBuffer,tamanio);
	this->mutexColaSalida.lockEscritura(__FILE__,__LINE__);
	this->colaSalida.push_back(str);
	this->mutexColaSalida.unlock(__FILE__,__LINE__);
	return true;
}

bool ConexionCliente::recibir(char **pBuffer,unsigned int& tamanioRecibido){
	
	// Chequeo que el hilo se encuentre funcionando
	if ( this->hiloEntrada.estaActivo() == false) return false;

	std::string str;
	str.clear();
	this->mutexColaEntrada.lockEscritura(__FILE__,__LINE__); // uso lockEscritura() porque hace pop_front()
	if (this->colaEntrada.empty()==false){
		str = this->colaEntrada.front();
		this->colaEntrada.pop_front();
	}
	this->mutexColaEntrada.unlock(__FILE__,__LINE__);

	if ( str.empty()==false){
		// Creo el buffer y recibo los datos
		(*pBuffer) = new char[str.size()];   // No le doy espacio al caracter nulo del final que hay en str.c_str()
		memcpy(*pBuffer,str.c_str(),str.size());
		tamanioRecibido = (unsigned int)str.size();
		return true;
	}else{
		(*pBuffer) = NULL;
		tamanioRecibido = 0;
		return true;
	}

}

bool ConexionCliente::enviarArchivo(const char *rutaOrigen){
	return this->socketApp.enviarArchivo(rutaOrigen);
}

bool ConexionCliente::recibirArchivo(const char *rutaDestino){
	return this->socketApp.recibirArchivo(rutaDestino);
}

void ConexionCliente::setSocket(SOCKET socket){
	this->socketApp.setSocket(socket);
	return void();
}

// Inicialo los parámetros necesarios para HiloConexión
// El parámetro <opcion> indica el tipo de cola que usará el hilo: 'E' para cola de entrada y 'S' para cola de salida
HiloConexion::stParametrosRun ConexionCliente::iniciarParametrosRun(char opcion,std::list<std::string>* colaEntradaMasiva,Mutex* mutexColaEntradaMasiva, std::list<long>* clientesMasivosConError){

	HiloConexion::stParametrosRun parametros;

	parametros.idCliente = this->id;
	parametros.opcion = opcion;
	parametros.pSocket = &(this->socketApp);
	parametros.pEsIndividual = &(this->esIndividual);
	parametros.pColaEntradaMasiva = colaEntradaMasiva;
	parametros.pIdMasivoConError = clientesMasivosConError;
	parametros.pMutexMasivo = mutexColaEntradaMasiva;
	parametros.pMutexEsIndividual = &(this->mutexEsIndividual);
	if( opcion == 'E' ){
		parametros.pCola = &(this->colaEntrada);
		parametros.pMutexCola = &(this->mutexColaEntrada);
	}else if( opcion == 'S' ){
		parametros.pCola = &(this->colaSalida);
		parametros.pMutexCola = &(this->mutexColaSalida);
	}else{
		parametros.pCola = NULL;
		parametros.pMutexCola = NULL;
	}

	return parametros;
}
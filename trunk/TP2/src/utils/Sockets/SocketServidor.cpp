#include "SocketServidor.h"

SocketServidor::SocketServidor(void){
	this->mutexConexionClientes.lockEscritura(__FILE__,__LINE__);
	this->conexionClientes.clear();
	this->mutexConexionClientes.unlock(__FILE__,__LINE__);
}

SocketServidor::~SocketServidor(void){
	this->desconectar();
}

// Cierra todos los sockets y por último cierra el winsock
bool SocketServidor::desconectar(void){

	// Cierro los sockets de los clientes
	for ( int i=0 ; i < this->tamanioConexionClientes() ; i++ ){
		ConexionCliente* cliente = this->getConexionCliente(i);
		cliente->cerrarActividad();
		if (cliente->cerrar() == false){
			std::cout<<"Error al cerrar clientes desde el servidor. \n";
			Log::getInstance().log(3,__FILE__,__LINE__,"Error al cerrar clientes desde el servidor.");
			delete cliente;
			return false;
		}else{
			delete cliente;
		}
		
	}

	this->mutexConexionClientes.lockEscritura(__FILE__,__LINE__);
	this->conexionClientes.clear();
	this->mutexConexionClientes.unlock(__FILE__,__LINE__);

	// Cierro el socket del Servidor
	if (this->miConexion.cerrar() == false ) return false;
	if (this->miConexion.finalizarAplicacion() == false ) return false;

	return true;
}

// Busca en el vector de conexiones un cliente por su ID y devuelve la posición en donde se encuentra en el vector
// En caso de no encontrarlo, se devuelve un índice inválido (-1).
// Usa una búsqueda secuencial. Acá supongo que siempre vamos a tener una baja cantidad de clientes, n << 1000, por ejemplo.
long SocketServidor::buscarCliente(long idCliente){
	long indice = -1;
	for ( int i=0 ; i < this->tamanioConexionClientes() ; i++ ){
		if( this->getConexionCliente(i)->getId() == idCliente) indice = i;
	}
	if (indice == -1) Log::getInstance().log(3,__FILE__,__LINE__,"No se encontró al cliente buscado: ",(int)idCliente );
	return indice;
}

// Cargo en una lista los clientes que tuvieron errores al recibir (si es que hubieron clientes con errores)
// Y luego elimino los clientes que tuvieron esos errores
// Devuelve true si se procesó al menos un cliente
// Devuelve false si no hubo ningún cliente procesado
bool SocketServidor::procesarClientesMasivosConError(void){

	bool huboActualizacion = false;
	std::list<long> masivosConError;
	masivosConError.clear();
	//unsigned int tamanio = 0; // Si uso swap esta variable no la necesito

	// Cargo en una lista los clientes con error
	this->mutexMasivo.lockEscritura(__FILE__,__LINE__);
	masivosConError.swap(this->clientesMasivosConError);
	this->mutexMasivo.unlock(__FILE__,__LINE__);

	// Elimino a los clientes con error
	if (masivosConError.empty() == false){
		huboActualizacion = true;
		for ( unsigned int i=0 ; i < masivosConError.size() ; i++ ){	
			long idTemp = masivosConError.front();
			masivosConError.pop_front();
			if(this->eliminarCliente(idTemp) == false){
				std::cout<<"Error Fatal. No se puede eliminar Cliente. \n";
				Log::getInstance().log(3,__FILE__,__LINE__,"Error Fatal. No se puede eliminar Cliente. " );
			}
			this->insertarClienteConError(idTemp);
		}
	}

	return huboActualizacion;
}

// Envía el archivo indicado en la ruta <rutaOrigen> al cliente indicado con <idCliente>
// El cliente indicado tiene que estar en modo Individual para que pueda recibir el archivo
// Devuelve true en caso de éxito al enviar y false en cualquier otro caso
bool SocketServidor::archivoEnviarIndividual(const char *rutaOrigen,long idCliente){
	//Log::getInstance().log(3,__FILE__,__LINE__,"Enviando archivo individual: ",std::string(rutaOrigen) );
	//Log::getInstance().log(3,__FILE__,__LINE__,"A cliente nro : ", idCliente );

	long indice = this->buscarCliente(idCliente);
	if ( indice >= 0 ){
		if (this->getConexionCliente(indice)->getEsIndividual() == true){
			if (this->getConexionCliente(indice)->enviarArchivo(rutaOrigen) == false){
				Log::getInstance().log(3,__FILE__,__LINE__,"Error al enviar un archivo desde el servidor." );
				std::cout<<"Error al enviar un archivo desde el servidor. \n";
				if(this->eliminarCliente(idCliente) == false){
					std::cout<<"Error Fatal. No se puede eliminar Cliente. \n";
					Log::getInstance().log(3,__FILE__,__LINE__,"Error Fatal. No se puede eliminar Cliente. " );
				}
				this->insertarClienteConError(idCliente);
				return false;
			}
		}else{
			Log::getInstance().log(3,__FILE__,__LINE__,"El cliente no es individual" );
			return NULL;
		}
	}
	return true;
}

// Recibe el archivo indicado al cliente indicado
// El cliente indicado tiene que estar en modo Individual para que pueda enviar el archivo al servidor
// Devuelve true en caso de éxito al recibir el archivo y false en cualquier otro caso
// NOTA: Por ahora esta función no se tendría que usar. Queda disponible para el futuro
bool SocketServidor::archivoRecibirIndividual(const char *rutaDestino,long idCliente){
	long indice = this->buscarCliente(idCliente);
	if ( indice < 0 ) return false;
	if (this->getConexionCliente(indice)->getEsIndividual() == true){
		if (this->getConexionCliente(indice)->recibirArchivo(rutaDestino) == false){
			Log::getInstance().log(3,__FILE__,__LINE__,"Error al recibir un archivo desde el servidor." );
			std::cout<<"Error al recibir un archivo desde el servidor. \n";
			if(this->eliminarCliente(idCliente) == false){
				std::cout<<"Error Fatal. No se puede eliminar Cliente. \n";
				Log::getInstance().log(3,__FILE__,__LINE__,"Error Fatal. No se puede eliminar Cliente. " );
			}
			this->insertarClienteConError(idCliente);
			return false;
		}
	}else{
		Log::getInstance().log(3,__FILE__,__LINE__,"El cliente no es individual" );
		return false;
	}
	return true;
}

void SocketServidor::insertarClienteConError(long idCliente){
	this->todosLosClientesConError.push_back(idCliente);
	return void();
}

ConexionCliente* SocketServidor::getConexionCliente(int indice){
	ConexionCliente* conexionTemp;
	this->mutexConexionClientes.lockLectura(__FILE__,__LINE__);
	conexionTemp = this->conexionClientes[indice];
	this->mutexConexionClientes.unlock(__FILE__,__LINE__);
	return conexionTemp;
}

long SocketServidor::tamanioConexionClientes(void){
	long tamanio;
	this->mutexConexionClientes.lockLectura(__FILE__,__LINE__);
	tamanio = this->conexionClientes.size();
	this->mutexConexionClientes.unlock(__FILE__,__LINE__);
	return tamanio;
}

// Prepara al servidor para aceptar clientes. Se debe hacer una sola vez
bool SocketServidor::inciarServidor(int puerto){
	
	bool ok;

	ok = this->miConexion.iniciarAplicacion();
	if (ok==false)return false;

	ok = this->miConexion.abrir();
	if (ok==false)return false;
	
	ok = this->miConexion.enlazarConexion(puerto);
	if (ok==false)return false;
	
	ok = this->miConexion.escuchar();
	if (ok==false)return false;

	return true;
}

// Acepta a un cliente que quiera conectarse al servidor
// Si la conexión fue exitosa devuelve el ID de la conexión. En otro caso devuelve un valor menor a 0
// En caso de Time Out devuelve el valor ACEPTAR_TIMEOUT
// En caso erróneo devuelve el valor ACEPTAR_ERROR
int SocketServidor::aceptarCliente(){

	ConexionCliente* cliente = new ConexionCliente;

	// Usa el select() para no quedar bloqueado por el accept(). Con esto solo hago accept sii hay un cliente que quiere conectarse
	if( this->miConexion.selectLectura() == false ) return ACEPTAR_TIMEOUT;

	bool aceptoOk = this->miConexion.aceptarCliente(cliente);

	if ( aceptoOk == false ){
		delete cliente;
		return ACEPTAR_ERROR;
	}else{
		this->mutexConexionClientes.lockEscritura(__FILE__,__LINE__);
		this->conexionClientes.push_back(cliente);
		this->mutexConexionClientes.unlock(__FILE__,__LINE__);
		
		cliente->iniciarRecepcion(&(this->colaEntradaMasiva),&(this->mutexMasivo),&(this->clientesMasivosConError)); // Le asigno la cola común a todos los clientes y su respectivo mutex
		cliente->iniciarEnvio();

		Log::getInstance().log(3,__FILE__,__LINE__,"[SERVIDOR]Cliente aceptado, ID_CLI:",cliente->getId());
		return cliente->getId();
	}
}

// Elimina al cliente del listado que tiene el servidor, desconectándose del mismo
bool SocketServidor::eliminarCliente(long idCliente){
	Log::getInstance().log(3,__FILE__,__LINE__,"Eliminando el cliente : ", idCliente );
	long indice = this->buscarCliente(idCliente);

	// Sólo actuo si el ID es válido
	if ( indice >= 0 ){

		// Detengo la actividad de los hilos y los cierro
		this->getConexionCliente(indice)->cerrarActividad();

		// Cierro la conexion del cliente
		if(this->getConexionCliente(indice)->cerrar() == false){
			std::cout << "No se pudo cerrar conexion\n";
			Log::getInstance().log(3,__FILE__,__LINE__, "No se pudo cerrar conexion");
			return false;
		}
		
		// Borro la instancia de cliente
		delete this->getConexionCliente(indice);

		// Borro el puntero correspondiente al cliente
		this->mutexConexionClientes.lockEscritura(__FILE__,__LINE__);
		this->conexionClientes.erase(this->conexionClientes.begin()+indice);
		this->mutexConexionClientes.unlock(__FILE__,__LINE__);
	}

	return true;
}

// Devuelve una lista con los ID's de los clientes que tuvieron errores de conexión (los cuales ya fueron eliminados)
// El listado incluye tanto clientes "Individuales" como "Masivos"
// En la lista se devuelven los ID's obtenidos desde la última vez que se llamó al método. 
// La primera vez que se llame al método devolverá los ID's obtenidos desde la creación del servidor
std::list<long> SocketServidor::getNuevosClientesErroneos(void){

	std::list<long> tempErroneos = this->todosLosClientesConError;
	this->todosLosClientesConError.clear();

	return tempErroneos;
}

// Setea al cliente para que se use la cola de entrada/salida individual del cliente.
// El cliente por defecto es individual
// En este modo sólo se podrán usar los metodos de envio/recepción de datos "Individuales"
// Devuelve true en caso de haber realizado exitosamente la tarea y false en caso de no encontrarse el id del cliente
bool SocketServidor::setClienteIndividual(long idCliente){
	long indice = this->buscarCliente(idCliente);
	if ( indice < 0 ) return false;
	this->getConexionCliente(indice)->setEsIndividual();
	return true;
}

// Para setear el modo en que se comporta la recpción/envío de mensajes de un cliente
// Setea al cliente para que se use la cola de entrada común a todos los clientes "Masivos"
// En este modo sólo se podrán usar los metodos de envio/recepción de datos "Masivos"
// Devuelve true en caso de haber realizado exitosamente la tarea y false en caso de no encontrarse el id del cliente
bool SocketServidor::setClienteMasivo(long idCliente){
	long indice = this->buscarCliente(idCliente);
	if ( indice < 0 ) return false;
	this->getConexionCliente(indice)->setMasiva();
	return true;
}

// Envía los datos de la Serializadora <s>
// El cliente indicado tiene que estar en modo Individual para que pueda enviar los datos, en caso contrario se obvia el cliente
// Devuelve true en caso de éxito al enviar
// Devuelve false en caso de error de conexión, eliminando al cliente.
bool SocketServidor::enviarIndividual(Serializadora s,int idCliente){
	std::string* pStr = s.getSerializacion();
	if( this->enviarIndividualChar(pStr->c_str(),pStr->size(),idCliente) == false ){
		delete pStr;
		return false;
	}else{
		delete pStr;
		return true;
	}
	return true;
}

// Envía los datos del <pBuffer> de un tamaño en bytes <tamanio> al cliente indicado con <idCliente>
// El cliente indicado tiene que estar en modo Individual para que pueda enviar los datos, en caso contrario se obvia el cliente
// Devuelve true en caso de éxito al enviar
// Devuelve false en caso de error de conexión, eliminando al cliente.
bool SocketServidor::enviarIndividualChar(const char *pBuffer,unsigned int tamanio,long idCliente){
	long indice = this->buscarCliente(idCliente);
	if ( indice >= 0 ){
		if (this->getConexionCliente(indice)->getEsIndividual() == true){
			if (this->getConexionCliente(indice)->enviarDirecto(pBuffer,tamanio) == false){
					std::cout<<"Error al enviar datos desde el servidor. \n";
					Log::getInstance().log(3,__FILE__,__LINE__,"Error al enviar datos desde el servidor. " );
					if(this->eliminarCliente(idCliente) == false){
						std::cout<<"Error Fatal. No se puede eliminar Cliente. \n";
						Log::getInstance().log(3,__FILE__,__LINE__,"Error Fatal. No se puede eliminar Cliente. " );
					}
					std::cout<<"TIENE ERROR!!! \n";
					this->insertarClienteConError(idCliente);
					return false;
			}
		}else{
			Log::getInstance().log(3,__FILE__,__LINE__,"El cliente no es individual" );
		}
	}

	return true;
}

// Envía los datos de la Serializadora <s> a todos los clientes existentes que se encuentren en modo Masivo
// Los clientes "individuales" se obvian
// Devuelve true en caso de éxito al enviar a todos los clientes que deben recibir el mensaje y false en cualquier otro caso
bool SocketServidor::enviarMasivo(Serializadora s){
	std::string* pStr = s.getSerializacion();
	if( this->enviarMasivoChar(pStr->c_str(),pStr->size()) == false ){
		delete pStr;
		return false;
	}else{
		delete pStr;
		return true;
	}
	return true;
}

// Envía los datos del <pBuffer> de un tamaño en bytes <tamanio> a todos los clientes existentes que se encuentren en modo Masivo
// Los clientes "individuales" se obvian
// Devuelve true en caso de éxito al enviar a todos los clientes que deben recibir el mensaje y false en cualquier otro caso
bool SocketServidor::enviarMasivoChar(const char *pBuffer,unsigned int tamanio){
	bool todosOk = true;
	
	for ( int i=0 ; i < this->tamanioConexionClientes() ; i++ ){
		//std::cout<<"Miro al cliente ("<< this->getConexionCliente(i)->getId() <<") \n";
		if (this->getConexionCliente(i)->getEsIndividual() == false){
			//std::cout<<"El cliente ("<< this->getConexionCliente(i)->getId() <<") en masivo, se le enviaran datos\n";
			if (this->getConexionCliente(i)->enviar(pBuffer,tamanio) == false){
				std::cout<<"Error al enviar datos desde el servidor. \n";
				Log::getInstance().log(3,__FILE__,__LINE__,"Error al enviar datos desde el servidor. " );
				long id = this->getConexionCliente(i)->getId();
				if(this->eliminarCliente(id) == false){
						std::cout<<"Error Fatal. No se puede eliminar Cliente. \n";
						Log::getInstance().log(3,__FILE__,__LINE__,"Error Fatal. No se puede eliminar Cliente. " );
				}else{
					this->insertarClienteConError(id);
				}
				todosOk = false;
			}
		}
	}

	return todosOk;
}

// Recibe los datos del cliente indicado con <idCliente>, a través de la <cadenaRecibida>
// El cliente indicado tiene que estar en modo Individual para que pueda enviar los datos al servidor
// Devuelve true, junto con la <cadenaRecibida> en caso de éxito al recibir
// En caso de no tener ningun mensaje recibido del cliente indicado se devuelve true, junto con un tamaño de <cadenaRecibida> = 0
// En caso de indicar un cliente que no existe o que su estado no es "individual" se devuelve true junto con un tamaño de <cadenaRecibida> = 0
// Devuelve false en caso de error en la conexión
bool SocketServidor::recibirIndividual(std::string& cadenaRecibida,int idCliente){
	int tamanioRecibido = 0;
	char* cadenaRaw = NULL;

	// Recibo desde el Servidor datos serializados en una cadena de chars
	if( this->recibirIndividualChar(&cadenaRaw,tamanioRecibido,idCliente) == false ) return false;
	
	if( tamanioRecibido > 0 ){
		cadenaRecibida.assign(cadenaRaw,tamanioRecibido);
		delete[] cadenaRaw;
	}else{
		if( tamanioRecibido == 0 ){
			// No hay mensaje recibido
			cadenaRecibida.clear(); // Emulo ponerlo en cero
		}else{
			// El cliente no es individual, entonces no recibo nada. // Separo el caso por si quiero implementarlo
			cadenaRecibida.clear(); // Emulo ponerlo en cero
		}
	}

	return true;
}

// Recibe los datos del cliente indicado con <idCliente>, a traves de <pbuffer> y su tamaño a través de <tamanioRecibido>
// El cliente indicado tiene que estar en modo Individual para que pueda enviar los datos al servidor
// Devuelve true, junto con la cadena recibida e instanciada en memoria (con new) en <pbuffer> y el <tamanioRecibido> en caso de éxito al recibir
// En caso de no tener ningun mensaje recibido del cliente indicado se devuelve true, junto con un tamanio = 0
// En caso de indicar un cliente que no existe o que su estado no es "individual" se devuelve true junto con un tamaño negativo (-1)
// Devuelve false en caso de error en la conexión
bool SocketServidor::recibirIndividualChar(char** pbuffer,int& tamanioRecibido,long idCliente){
	// Chequeo existencia
	long indice = this->buscarCliente(idCliente);
		if ( indice >= 0 ){
			// Chequeo que sea individual
		if (this->getConexionCliente(indice)->getEsIndividual() == true){
			unsigned int tamanio = tamanioRecibido;
			if( this->getConexionCliente(indice)->recibirDirecto(pbuffer,tamanio) == false){
				std::cout<<"Error al recibir datos desde el servidor. \n";
				Log::getInstance().log(3,__FILE__,__LINE__,"Error al recibir datos desde el servidor. " );
				if(this->eliminarCliente(idCliente) == false){
					std::cout<<"Error Fatal. No se puede eliminar Cliente. \n";
					Log::getInstance().log(3,__FILE__,__LINE__,"Error Fatal. No se puede eliminar Cliente. " );
				}
				this->insertarClienteConError(idCliente);
				tamanioRecibido = 0;
				return false;
			}else{
				tamanioRecibido = tamanio;
			}	
		}else{		
			Log::getInstance().log(3,__FILE__,__LINE__,"El cliente no es individual" );
			tamanioRecibido = -1;
		}	
	}

	return true;
}

// Recibe el primero de todos los mensajes de la cola de entrada común a todos los clientes "Masivos"
// La cadena se recibe a través de la <cadenaRecibida>
// Solo se recibirán mensajes de clientes que se encuentren en modo Masivo
// Devuelve true si nadie tuvo errores de conexion al recibir en modo "masivo"
// Devuelve false si algún cliente "masivo" tuvo errores de conexion al recibir. Se puede chequear quien fue con getNuevosClientesErroneos()
bool SocketServidor::recibirMasivo(std::string& cadenaRecibida){
	int tamanioRecibido = 0;
	char* cadenaRaw = NULL;

	// Recibo desde el Servidor datos serializados en una cadena de chars
	if( this->recibirMasivoChar(&cadenaRaw,tamanioRecibido) == false ) return false;
	
	if( tamanioRecibido > 0 ){
		cadenaRecibida.assign(cadenaRaw,tamanioRecibido);
		delete[] cadenaRaw;
	}else{
		cadenaRecibida.clear(); // Emulo ponerlo en cero
	}

	return true;
}

// Recibe el primero de todos los mensajes de la cola de entrada común a todos los clientes "Masivos"
// La cadena se recibe a través de <pbuffer> y su tamaño a través de <tamanioRecibido>
// Solo se recibirán mensajes de clientes que se encuentren en modo Masivo
// Siempre (sin importar el valor del return) se devuelve la cadena recibida e instanciada en memoria (con new) y su <tamanioRecibido>
// En el caso de no haber ningún mensaje, se recibe <tamanioRecibido> = 0
// Devuelve true si nadie tuvo errores de conexion al recibir en modo "masivo"
// Devuelve false si algún cliente "masivo" tuvo errores de conexion al recibir.
bool SocketServidor::recibirMasivoChar(char** pbuffer,int& tamanioRecibido){

	bool todosOk = true;
	if (this->procesarClientesMasivosConError() == true) todosOk = false;  // Si se porceso algún cliente con error, entonces ya no están todos los clientes ok

	std::string str;
	str.clear();
	this->mutexMasivo.lockEscritura(__FILE__,__LINE__);
	if (this->colaEntradaMasiva.empty()==false){
		str = this->colaEntradaMasiva.front();
		this->colaEntradaMasiva.pop_front();
	}
	this->mutexMasivo.unlock(__FILE__,__LINE__);

	if ( str.empty()==false){
		// Creo el buffer y recibo los datos
		(*pbuffer) = new char[str.size()];   // No le doy espacio al caracter nulo del final que hay en str.c_str()
		memcpy(*pbuffer,str.c_str(),str.size());
		tamanioRecibido = str.size();
	}else{
		(*pbuffer) = NULL;
		tamanioRecibido = 0;
	}

	return todosOk;
}

// Envía todos los archivos indicados en la lista de paths, al cliente <idCliente>
// Devuelve true si todos los archivos se enviaron, y false si algún o algunos archivos no se pudieron enviar, eliminando al cliente
// En caso de error del cliente, el mismo será eliminado y notificado en la lista de clientes con error
bool SocketServidor::enviarArchivosIndividual(std::list<std::string> rutaDeArchivosParaEnviar,long idCliente){

	bool todoOk = true;
	int tamanio = rutaDeArchivosParaEnviar.size();

	for ( int i=0 ; i < tamanio ; i++ ){
		std::string ruta(rutaDeArchivosParaEnviar.front());
		rutaDeArchivosParaEnviar.pop_front();
		if (this->archivoEnviarIndividual(ruta.c_str(),idCliente)==false) todoOk = false;
	}

	return todoOk;
}

// Recibe todos los archivos indicados en la lista de paths, desde el cliente <idCliente>
// Devuelve true si todos los archivos se recibieron, y false si algún o algunos archivos no se pudieron recibir eliminando al cliente
// En caso de error del cliente, el mismo será eliminado y notificado en la lista de clientes con error
bool SocketServidor::recibirArchivosIndividual(std::list<std::string> rutaDeArchivosParaRecibir,long idCliente){

	bool todoOk = true;
	int tamanio = rutaDeArchivosParaRecibir.size();

	for ( int i=0 ; i < tamanio ; i++ ){
		std::string ruta(rutaDeArchivosParaRecibir.front());
		rutaDeArchivosParaRecibir.pop_front();
		if (this->archivoRecibirIndividual(ruta.c_str(),idCliente)==false) todoOk = false;
	}

	return todoOk;
}

#include "HiloConfiguracion.h"

HiloConfiguracion::HiloConfiguracion(void){
	this->detenerActividad();		// El hilo arranca sin actividad
	this->configuracionFinalizada = false;
}

HiloConfiguracion::~HiloConfiguracion(void){

}

void* HiloConfiguracion::run(void* parametrosRun){
	stParametrosConfiguracion* parametros = ((stParametrosConfiguracion*)parametrosRun);
	this->rutina(parametros);
	return NULL;
}

// Acá activo el hilo y hago el start
void HiloConfiguracion::correrConfiguracion(stParametrosConfiguracion parametrosRun){
	this->mutexCorriendo.lockEscritura(__FILE__,__LINE__);
	this->corriendo = true;
	this->mutexCorriendo.unlock(__FILE__,__LINE__);
	this->parametrosRun = parametrosRun;
	this->start(&(this->parametrosRun)); 
	return void();
}

// + Se encarga se enviar y recibir datos y archivos al cliente a través del Servidor, para dejar listo al jugador para entrar al ciclo de juego. Una vez hecha su tarea el hilo finaliza
void HiloConfiguracion::rutina(stParametrosConfiguracion* parametrosConfiguracion){

	return void();
}

// Envia al cliente todos los archivos necesarios para el funcionamiento del juego
bool HiloConfiguracion::enviarArchivosDeConfiguracion(SocketServidor* pServidor){
	bool exito = true;
	LectorDirectorios lector;	// Para obtener todos los nombres de los archivos
	std::vector<std::string> listaArchivos;

	// Envio los archivos de configuracion
	listaArchivos = lector.leerDirectorio(DIRECTORIO_IMG);
	if( !this->enviarListaDeArchivos(listaArchivos,pServidor)) {
		Log::getInstance().log(1,__FILE__,__LINE__,"El Servidor no pudo enviar todos los archivos de imagenes al cliente con ID ",this->getId());
		exito = false;
	}
	
	// Envio los archivos de imagenes
		listaArchivos = lector.leerDirectorio(DIRECTORIO_CONFIG);
	if( this->enviarListaDeArchivos(listaArchivos,pServidor) == false)  {
		Log::getInstance().log(1,__FILE__,__LINE__,"El Servidor no pudo enviar todos los archivos de imagenes al cliente con ID ",this->getId());
		exito = false;
	}

	return exito;
}

bool HiloConfiguracion::enviarListaDeArchivos(std::vector<std::string> vector,SocketServidor* pServidor){

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
	if( pServidor->enviarIndividual(pStr->c_str(),pStr->size(),this->getId()) == false ){
		delete pStr;
		return false;
	}else{
		delete pStr;
	}

	// Envio todos los archivos 
	pServidor->enviarArchivosIndividual(rutaDeArchivosParaEnviar,this->getId());

	return true;
}

void HiloConfiguracion::detenerActividad(void){
	this->mutexCorriendo.lockEscritura(__FILE__,__LINE__);
	this->corriendo = false;
	this->mutexCorriendo.unlock(__FILE__,__LINE__);
	return void();
}

bool HiloConfiguracion::estaActivo(void){
	bool resultado;
	this->mutexCorriendo.lockLectura(__FILE__,__LINE__);
	resultado = this->corriendo;
	this->mutexCorriendo.unlock(__FILE__,__LINE__);
	return resultado;
}

void HiloConfiguracion::finalizarConfiguracion(void){
	this->mutexConfiguracionFinalizada.lockEscritura(__FILE__,__LINE__);
	this->configuracionFinalizada = true;
	this->mutexConfiguracionFinalizada.unlock(__FILE__,__LINE__);
	return void();
}

bool HiloConfiguracion::estaConfiguracionFinalizada(void){
	bool resultado;
	this->mutexConfiguracionFinalizada.lockLectura(__FILE__,__LINE__);
	resultado = this->configuracionFinalizada;
	this->mutexConfiguracionFinalizada.unlock(__FILE__,__LINE__);
	return resultado;
}

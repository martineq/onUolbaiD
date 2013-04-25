#include "Mutex.h"


Mutex::Mutex(){
	pthread_mutex_init(&mutex,NULL);
}


Mutex::~Mutex(){
	pthread_mutex_destroy(&mutex);
}


int Mutex::lock(std::string datosDebug){
	std::string debug = datosDebug;		// Sólo para fines de debug, por si cae en una excepción en este método
	return pthread_mutex_lock(&mutex);
}


int Mutex::unlock(std::string datosDebug){
	std::string debug = datosDebug;		// Sólo para fines de debug, por si cae en una excepción en este método
	return pthread_mutex_unlock(&mutex);
}


int Mutex::lock(void){
	return pthread_mutex_lock(&mutex);
}


int Mutex::unlock(void){
	return pthread_mutex_unlock(&mutex);
}


int Mutex::lock(std::string archivo, int linea){
	std::stringstream msg;
	msg <<"lock() en: "<< Log::getInstance().obtenerNombreDesdeRuta(archivo) << " (" << linea << ")";
	if (ESTADO_IMPRIMIR_INFO_MUTEX == SI_IMPRIMIR_INFO_MUTEX){
		std::cout << msg.str() << std::endl;
		Log::getInstance().log(3,__FILE__,__LINE__,msg.str());
	}
	return this->lock(msg.str());
}


int Mutex::unlock(std::string archivo, int linea){
	std::stringstream msg;
	msg <<"unlock() en: "<< Log::getInstance().obtenerNombreDesdeRuta(archivo) << " (" << linea << ")";
	if (ESTADO_IMPRIMIR_INFO_MUTEX == SI_IMPRIMIR_INFO_MUTEX){
		std::cout << msg.str() << std::endl;
		Log::getInstance().log(3,__FILE__,__LINE__,msg.str());
	}
	return this->unlock(msg.str());
}


pthread_mutex_t& Mutex::getMutex(){
	return this->mutex;
}

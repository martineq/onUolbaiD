#include "Mutex.h"

Mutex::Mutex(){
	pthread_rwlock_init(&mutex, NULL);
}

Mutex::~Mutex(){
	pthread_rwlock_destroy(&mutex);
}

// Sólo para fines de debug, por si cae en una excepción al usar el mutex
std::string Mutex::reporte(std::string archivo, int linea){
	std::stringstream msg;
	msg <<"Uso mutex en: "<< Log::getInstance().obtenerNombreDesdeRuta(archivo) << " (" << linea << ")";
	if (ESTADO_IMPRIMIR_INFO_MUTEX == SI_IMPRIMIR_INFO_MUTEX){
		std::cout << msg.str() << std::endl;
		Log::getInstance().log(3,__FILE__,__LINE__,msg.str());
	}
	return msg.str();
}

int Mutex::lockEscritura(std::string archivo, int linea){
	std::string debug = this->reporte(archivo,linea); 
	return pthread_rwlock_wrlock(&mutex);
}

int Mutex::lockLectura(std::string archivo, int linea){
	std::string debug = this->reporte(archivo,linea); 
	return pthread_rwlock_rdlock(&mutex);
}

int Mutex::unlock(std::string archivo, int linea){
	std::string debug = this->reporte(archivo,linea); 
	return pthread_rwlock_unlock(&mutex);
}


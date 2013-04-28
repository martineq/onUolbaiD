#pragma once

#include <pthread.h>
#include "../Constantes/Constantes.h"
#include "../Log/Log.h"

class Mutex{

	private:
		pthread_rwlock_t mutex;
		std::string reporte(std::string archivo, int linea);

	public:
		Mutex();
		virtual ~Mutex();

		int lockEscritura(std::string archivo, int linea);
		int lockLectura(std::string archivo, int linea);
		int unlock(std::string archivo, int linea);

};
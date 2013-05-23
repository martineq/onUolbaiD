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

		int lockEscritura(std::string __file__, int __line__);
		int lockLectura(std::string __file__, int __line__);
		int unlock(std::string __file__, int __line__);

};
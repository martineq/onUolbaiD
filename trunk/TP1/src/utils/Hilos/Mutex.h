#pragma once

#include <pthread.h>
#include "../Constantes/Constantes.h"
#include "../Log/Log.h"

class Mutex{

	private:
		pthread_mutex_t mutex;
		int lock(std::string datosDebug);
		int unlock(std::string datosDebug);
		
		// Este get nunca lo usamos, si hace falta lo podemos hacer público
		pthread_mutex_t& getMutex();

	public:
		Mutex();
		virtual ~Mutex();

		// Los clásicos lock() y unlock()
		int lock(void);
		int unlock(void);

		// Estos lock() y unlock() reciben por parámetro siempre lo mismo:  lock(__FILE__,__LINE__);
		// Es para fines de debug pudiendo conocer, en caso de algún error, dónde se generó el conflicto.
		int lock(std::string archivo, int linea);
		int unlock(std::string archivo, int linea);

};
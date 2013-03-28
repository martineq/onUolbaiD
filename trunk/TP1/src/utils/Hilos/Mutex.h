#pragma once

#include <pthread.h>
#include "../Constantes/Constantes.h"
#include "../Log/Log.h"

class Mutex{

	private:
		pthread_mutex_t mutex;
		int lock(std::string datosDebug);
		int unlock(std::string datosDebug);
		
		// Este get nunca lo usamos, si hace falta lo podemos hacer p�blico
		pthread_mutex_t& getMutex();

	public:
		Mutex();
		virtual ~Mutex();

		// Los cl�sicos lock() y unlock()
		int lock(void);
		int unlock(void);

		// Estos lock() y unlock() reciben por par�metro siempre lo mismo:  lock(__FILE__,__LINE__);
		// Es para fines de debug pudiendo conocer, en caso de alg�n error, d�nde se gener� el conflicto.
		int lock(std::string archivo, int linea);
		int unlock(std::string archivo, int linea);

};
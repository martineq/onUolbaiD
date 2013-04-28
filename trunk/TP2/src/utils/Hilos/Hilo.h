#ifndef HILO_H_
#define HILO_H_

#include <iostream>
#include <pthread.h>
#include <winsock.h>  // Para usar InterlockedIncrement()

class Hilo {

	public:
		struct stParametro {
			void* punteroThis;
			void* parametro;
		};

		virtual void* run(void* parametro) = 0;
		int start(void* arg);
		void* join();
		Hilo();
		virtual ~Hilo();
		int getId(void);

	private:
		
		static void* rutina(void* parametro);
		pthread_t thread;

		// Para generar ID's Automáticos
		static long contador;
		long id;


};

#endif /* THREAD_H_ */

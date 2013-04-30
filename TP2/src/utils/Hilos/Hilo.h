#pragma once

#include <iostream>
#include <pthread.h>
#include <winsock.h>  // Para usar InterlockedIncrement()

class Hilo {

	private:
		struct stParametro {
			void* punteroThis;
			void* parametro;
		};
		pthread_t thread;

		// Para generar ID's Automáticos
		static long contador;
		long id;

		static void* rutina(void* parametro);

	public:
		Hilo();
		virtual ~Hilo();

		virtual void* run(void* parametro) = 0;
		int start(void* arg);
		void* join();
		int getId(void);

};

#pragma once

#include <iostream>
#include <pthread.h>
#include <winsock.h>  // Para usar InterlockedIncrement()


class Hilo{

	private:

		struct stParametro {
			void* punteroThis;
			void* parametro;
		};

		pthread_t thread;	
		static void* rutina(void* parametro);

		// Para generar ID's Automáticos
		static long contador;
		int id;

	public:

		Hilo();
		virtual ~Hilo();
		
		// Comienza el hilo, correrá el código implementado en run()
		int start(void* arg);
		
		// Espero a que termine el hilo
		void* join();

		// Método a implementar por la clase que herede de Hilo
		virtual void* run(void* parametro) = 0;
		
		// Para obtener el ID asignado automáticamente al hilo. Sólo para fines de debug, si es necesario.
		int getId(void);
};
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

		// Para generar ID's Autom�ticos
		static long contador;
		int id;

	public:

		Hilo();
		virtual ~Hilo();
		
		// Comienza el hilo, correr� el c�digo implementado en run()
		int start(void* arg);
		
		// Espero a que termine el hilo
		void* join();

		// M�todo a implementar por la clase que herede de Hilo
		virtual void* run(void* parametro) = 0;
		
		// Para obtener el ID asignado autom�ticamente al hilo. S�lo para fines de debug, si es necesario.
		int getId(void);
};
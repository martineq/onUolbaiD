#pragma once

#include <iostream>
#include <pthread.h>
#include "../Ticket/Ticket.h"

class Hilo {

	private:
		struct stParametro {
			void* punteroThis;
			void* parametro;
		};
		pthread_t thread;
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

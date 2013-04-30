#pragma once

#include <SDL.h>

typedef unsigned int uint;

class Timer{

    private:
		unsigned int startTicks;		// Tiempo al comienzo
		unsigned int pausedTicks;		// Tiempo al pausar
		bool paused;
		bool started;

    public:
		Timer();

		// Acciones
		void start();
		void stop();
		void pause();
		void unpause();

		// Obbtner el tiempo del timer
		unsigned int get_ticks();

		// Chequear status del timer
		bool is_started();
		bool is_paused();
};

#pragma once

#include "../Timer/Timer.h"

class Temporizador{

	private:
		static Temporizador* _instancia;
		Timer fps;
		Temporizador();

	public:
		static Temporizador* getInstancia();
		void start();
		void stop();
		uint get_ticks();
		void cerrar();
		virtual ~Temporizador();
};
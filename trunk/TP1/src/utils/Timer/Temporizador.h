#pragma once

#include "../Timer/Timer.h"

class Temporizador {


private:
	Temporizador();

	static Temporizador* _instancia;

	Timer fps;

public:
	static Temporizador* getInstancia();
	void start();
	void stop();
	uint get_ticks();
	void cerrar();

	virtual ~Temporizador();
};
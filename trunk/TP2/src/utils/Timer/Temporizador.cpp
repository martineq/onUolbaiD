#include "Temporizador.h"

Temporizador* Temporizador::_instancia = NULL;

Temporizador::Temporizador() {

}

Temporizador::~Temporizador() {

}

Temporizador* Temporizador::getInstancia() {
	if (_instancia == NULL) {
		_instancia = new Temporizador();
	}
	return _instancia;
}

void Temporizador::start() {
	this->fps.start();
}

void Temporizador::stop() {
	this->fps.stop();
}

uint Temporizador::get_ticks() {
	return this->fps.get_ticks();
}

void Temporizador::cerrar(){
	if (_instancia != NULL) {
		delete _instancia;
	}
}

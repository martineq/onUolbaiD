#include "ModeloJuego.h"

ModeloJuego::ModeloJuego() {
}

ModeloJuego::~ModeloJuego() {

}

bool ModeloJuego::iniciar() {
	return this->_modeloFactory.crearModeloNivel(this->_modeloNivel);
}

bool ModeloJuego::loop() {
	return this->_modeloLoop.loop(this->_modeloNivel);
}

void ModeloJuego::destruirEntidades(){
	this->_modeloNivel.destruirListas();
}
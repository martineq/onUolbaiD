#include "UIState.h"

UIState::UIState() {

	this->mousex = 0;
	this->mousey = 0;
	this->mousedown = 0;

	/*this->hotitem = 0;
	this->activeitem = 0;

	this->kbditem = 0;
	this->keyentered = 0;
	this->keymod = 0;
	this->keychar = 0;

	this->lastwidget = 0;

	this->mensajeBarraDeEstado = "jejejejeje";*/
}

UIState& UIState::getInstancia() {
	static UIState _instancia;
	return _instancia;
}

UIState::~UIState() {;}

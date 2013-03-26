#include "UIState.h"

UIState::UIState() {
	this->mousex = 0;
	this->mousey = 0;
	this->mousedown = 0;
}

UIState& UIState::getInstancia() {
	static UIState _instancia;
	return _instancia;
}

UIState::~UIState() {;}

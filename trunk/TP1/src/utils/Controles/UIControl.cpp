#include "UIControl.h"

UIControl::UIControl() {
	this->id = 0;
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
}

UIControl::UIControl(int id, int x, int y, int w, int h) {
	this->id = id;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

int UIControl::regionhit(int x, int y, int w, int h) {
	if (UIState::getInstancia().mousex < x ||
		UIState::getInstancia().mousey < y ||
		UIState::getInstancia().mousex >= x + w ||
		UIState::getInstancia().mousey >= y + h)
			return 0;
	return 1;
}

void UIControl::setManejador(int event_id, void (*pfuncion1)()) {
	this->manejadores[event_id] = pfuncion1;
}

void UIControl::manejarEvento(int event_id){
	this->manejadores[event_id]();
}

UIControl::~UIControl() {}

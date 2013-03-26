#ifndef UISTATE_H_
#define UISTATE_H_

#include <string>

class UIState {
private:
	UIState();
public:
	int mousex;
	int mousey;
	int mousedown;

	int hotitem;
	int activeitem;

	int kbditem;
	int keyentered;
	int keymod;
	int keychar;

	int lastwidget;

	std::string mensajeBarraDeEstado;

	virtual ~UIState();
	
	static UIState& getInstancia();
};

#endif /* UISTATE_H_ */

#ifndef UICONTROL_H_
#define UICONTROL_H_
#include "UIState.h"

#define EVENT_ONCLICK 0;

class UIControl {

private:
	void (*manejadores[5])();  // Array de punteros a funciones

protected:
	int id;
	int x;
	int y;
	int w;
	int h;
	int fontSize;
	int regionhit(int x, int y, int w, int h);

public:
	UIControl();
	int getId() { return id; }
	int getX() { return x; }
	int getY() { return y; }
	int getW() { return w; }
	int getH() { return h; }

	void setFontSize(int fontSize) { this->fontSize = fontSize; }
	int getFontSize() { return this->fontSize; }

	void setX(int x) { this->x = x;}
	void setY(int y) { this->y = y;}
	void setW(int w) { this->w = w;}
	void setH(int h) { this->h = h;}

	UIControl(int id, int x, int y, int w, int h);
	virtual ~UIControl();

	// A mejorar
	void manejarEvento(int event_id);
	void setManejador(int event_id, void (*pfuncion1)());
};

#endif /* UICONTROL_H_ */

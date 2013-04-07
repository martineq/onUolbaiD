#ifndef ANIMACION_H_
#define ANIMACION_H_
#include <vector>
#include <list>
#include <map>
#include <string>
#include "SDLutil.h"
#include "ImageLoader.h"


class VistaAnimacion {

private:
	vector<SDLutil*> superficies;
	int periodo;
	double ancho;
	double alto;
	int indice;	
	double x;
	double y;
	double intervaloActualizacion;
	bool automatica;
	double tiempoEspera;
	double tiempoSprite;
	
public:
	VistaAnimacion(list<string> & sprites, int periodo, double ancho, double alto, bool automatica, int fps);
	SDLutil* get(int index);
	int getTamanio();
	int getPeriodo();
	void setPantalla(SDL_Surface* pantalla);
	bool graficar(int index, double x, double y);
	void graficar(double x,double y);
	void graficar();
	void incrementarIndice();
	bool esperarTiempo();

	virtual ~VistaAnimacion();
};



#endif /* ANIMAMACION_H_ */

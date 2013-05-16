#pragma once

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
	int indiceAnterior;
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
	bool graficar(double x,double y, char visibilidad);
	bool graficar(char visibilidad);
	bool animacionFinalizada();
	void incrementarIndice();
	bool esperarTiempo();
	void setX(double x);
	void setY(double y);

	virtual ~VistaAnimacion();
};


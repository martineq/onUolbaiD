#pragma once

#include "Proxy.h"
#include "../../Servidor/modelo/ModeloEntidad.h"
class ProxyEntidad: public Proxy
{
private:
	int id;
	std::string nombre;
	double x;
	double y;
	int tileX;
	int tileY;
	bool esJugador;
	int codigoDireccion;
	int codigoAccion;	

public:
	ProxyEntidad(void);	
	ProxyEntidad(ModeloEntidad* entidad);
	string* serialize();
	bool hydrate(string* source);
	void actualizar(class Observable* s);
    ~ProxyEntidad(void);
};

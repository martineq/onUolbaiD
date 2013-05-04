#pragma once

#include "../Observador/Observador.h"
#include "../Observador/Observable.h"
#include "../Serializacion/Serializable.h"
#include "../Constantes/Constantes.h"


class Proxy: public Observador, public Observable, public Serializable
{
protected:
	std::string tipoProxy;
	bool actualizado;

public:
	bool getActualizado() { return actualizado ; }
	void setActualizado(bool actu) { actualizado = actu; }
	
	//Para observable
	void cambiarEstado(){ notificarObservadores(); }

	//Para observador
	virtual void actualizar(class Observable* s) = 0;

	virtual std::string* serialize() = 0;
	virtual bool hydrate(std::string* source) = 0;
	virtual int getSize() = 0;

	~Proxy(void){ };
};

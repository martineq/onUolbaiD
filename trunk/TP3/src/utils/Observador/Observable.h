#pragma once

#include <list>
#include "Observador.h"

// Clase abstracta para elementos que deseen ser observados por uno
// o muchos objetos que implementen la Interfaz <Observador>
class Observable{

	std::list<Observador *> listaObservadores;

public:
	virtual ~Observable(){}
	void agregarObservador(Observador *obs){
		listaObservadores.push_back(obs);
	}
	virtual void cambiarEstado() = 0;

protected:
	void notificarObservadores(){
		for (std::list<Observador *>::iterator it=listaObservadores.begin() ; it != listaObservadores.end(); it++ ){
			(*it)->actualizar(this);
		}
	}

};


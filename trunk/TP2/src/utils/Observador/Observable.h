#pragma once

#include <list>
#include "Observador.h"

// Clase abstracta para elementos que deseen ser observados por uno
// o muchos objetos que implementen la Interfaz <Observador>
class Observable{

	std::list<Observador *> listaObservadores;
	int claseHijo;  // Uso opcional. Para que los observadores de clases distintas puedan identificar que clase es.

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

public:
	// Uso opcional. Lo debería usar el constructor de la clase que hereda es esta.
	void setClaseHijo(int clase){this->claseHijo = clase;}
	
	// Uso opcional. Para que los observadores de clases distintas puedan identificar que clase es.
	int getClaseHijo(void){return this->claseHijo;}

};


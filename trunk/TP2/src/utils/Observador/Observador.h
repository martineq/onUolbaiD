#pragma once

// Interfaz para elementos que deseen ser observadores, de un objeto <Observable>
class Observador{
public:
	virtual void actualizar(class Observable* s) = 0;
	virtual ~Observador(){}
};

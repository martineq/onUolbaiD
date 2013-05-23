#pragma once

// Interfaz para observadores y observables que necesiten tener id para reconocerse
class Identificable {
	public:
		virtual int id() = 0;
		
		virtual ~Identificable() { }
};

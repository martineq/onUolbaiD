#pragma once

#include <SDL.h>

class Temporizador{

	private: 
		Temporizador();
		Temporizador(const Temporizador&);
		Temporizador& operator =(const Temporizador&);
	
		unsigned int ticInicial;		// Tiempo al comienzo
		unsigned int ticPausado;		// Tiempo al pausar
		bool pausado;
		bool comenzado;

    public:
		virtual ~Temporizador();
		static Temporizador& getInstance();

		// Acciones
		void comenzar();
		void parar();
		void pausar();
		void sacarPausa();
		void crearDelay(int milisegundos);

		// Obtner el tiempo del Temporizador
		unsigned int obtenerTics();

		// Chequear status del Temporizador
		bool estaComenzado();
		bool estaPausado();
};

inline Temporizador& Temporizador::getInstance(){
	static Temporizador objecto;
	return objecto;
}
#pragma once

#include <SDL.h>

class Temporizador{

	private: 
		Temporizador();
		Temporizador(const Temporizador&);
		Temporizador& operator =(const Temporizador&);
	
		unsigned long ticInicial;		// Tiempo al comienzo
		unsigned long ticPausado;		// Tiempo al pausar
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
		void crearDelay(long milisegundos);

		// Obtner el tiempo del Temporizador
		unsigned long obtenerTics();

		// Chequear status del Temporizador
		bool estaComenzado();
		bool estaPausado();
};

inline Temporizador& Temporizador::getInstance(){
	static Temporizador objecto;
	return objecto;
}
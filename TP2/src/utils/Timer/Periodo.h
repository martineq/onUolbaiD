#pragma once
#include "../Timer/Timer.h"

class Periodo{

	private:
		Timer timer;
		bool esperandoPeriodo;
		uint tiempoInicio;
		uint segundos;

	public:
		Periodo();
		bool estaEsperandoPeriodo() { return this->esperandoPeriodo; }
		bool estaCumplido();
		void finalizar();
		void iniciar(int cantSegundos);

		virtual ~Periodo();
};

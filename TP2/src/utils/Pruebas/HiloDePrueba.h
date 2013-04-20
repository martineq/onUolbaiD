#pragma once

#include <sstream>
#include "../Hilos/Hilo.h"

class HiloDePrueba: public Hilo{

	private:
		void* run(void* parametro); // Método privado que tengo que implementar por heredar de la calse <Hilo>

	public:
		HiloDePrueba(void);
		~HiloDePrueba(void);
		

};

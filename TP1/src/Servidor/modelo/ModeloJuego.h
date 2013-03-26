#pragma once

#include "./ModeloFactory.h"
#include "./ModeloNivel.h"
#include "./ModeloLoop.h"

class ModeloJuego{
	
	private:
		ModeloFactory modeloFactory;
		ModeloNivel modeloNivel;
		ModeloLoop modeloLoop;

	public:
		ModeloJuego(void);
		~ModeloJuego(void);

};

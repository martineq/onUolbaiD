#pragma once

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>

class FinalJ{

	public:
	
		struct stEnem{
			int x;
			int y;
			double atq;
		
		};

		struct stPje{
			std::string id;
			int x;
			int y;
			double energia;
			int ciclos;
			int recorrido;
			bool murio;
			bool gano;

			bool operator<(const stPje& otro) const{
				return ( (*this).recorrido < otro.recorrido );
			}

		};
		
		struct stDatos{
			int tam;
			std::list<stEnem> enemigos;
			std::list<stPje> pDisponibles;
		};

		void leerArchivos(stDatos& datos);
		void procesar(stDatos& datos);
		void listar(stDatos& datos);

		void atacar(stDatos& datos, int x, int y, double atq);

		FinalJ(void);
		~FinalJ(void);

		void resolver();
};

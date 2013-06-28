#pragma once

#include <iostream>
#include <sstream>
#include <list>
#include <math.h>
#include "ESArchivoCpp.h"

class FinalC{

	private:
		
		struct stRec{
			std::string id;
			double x;
			double y;
			double alto;
			double ancho;
		};

		struct stCir{
			std::string id;
			double x;
			double y;
			double r;
		};

		struct stDatos{
			std::list<stRec> dispersores;
			std::list<stCir> tejos;
		};

		struct stResultado{
			std::string idTejo;
			std::string idDispersor;
			double distancia;
		};

		void leerArchivoDispersores(stDatos &datos);
		void leerArchivoTejos(stDatos &datos);
		void procesarChoques(stDatos &datos);

	public:
		FinalC(void);
		~FinalC(void);

		void resolver(void);

};


#pragma once

#include <list>

class ModeloDrop{

	public:

		struct stDatoItem{
			// Para todos los items
			int alto;
			int ancho;
			int velocidad;
			int altoEscenario;
			int anchoEscenario;
			int fps;
			void* pSocket;
			std::string nombreEntidad;
		};

		struct stDatoGolem{
			// Adicional para el icono Golem
			int altoGolem;
			int anchoGolem;
			int fpsGolem;
			int anchoEscenarioGolem;
			int altoEscenarioGolem;
		};

		struct stDatosDrop{
			std::list<stDatoItem> listaDatosItems;
			stDatoGolem datosGolem;
		};

	public:
		ModeloDrop();
		~ModeloDrop(void);

};

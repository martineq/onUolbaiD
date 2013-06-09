#pragma once

#include "ModeloItem.h"
#include "../../utils/Ticket/Ticket.h"

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

	private:
		stDatosDrop datos;

		ModeloItem* crearItem(ModeloDrop::stDatoItem datoItem, Posicion pos);

	public:
		ModeloDrop(ModeloDrop::stDatosDrop datos);
		~ModeloDrop(void);

		ModeloItem* drop(Posicion pos);

};

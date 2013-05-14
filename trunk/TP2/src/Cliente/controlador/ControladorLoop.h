#pragma once

#include <vector>
#include "../vista/VistaNivel.h"
#include "../vista/VistaEntidad.h"
#include "../vista/VistaChat.h"
#include "DetectorEventos.h"
#include "ControladorEvento.h"

class ControladorLoop{
	private:
		DetectorEventos detector;
		ControladorEvento evento;
		VistaChat* vistaChat;

public:
		ControladorLoop();
		virtual ~ControladorLoop();
		void loop(VistaNivel* nivel);		
		bool getQuit();
		ControladorEvento* getControladorEvento();
		void asignarChat(VistaChat* vistaChat);
};

#pragma once

#include "./HiloConfiguracion.h"
#include "../Hilos/Hilo.h"
#include "../Hilos/Mutex.h"
#include "../Sockets/SocketServidor.h"
#include "../Temporizador/Temporizador.h"

class HiloReceptor: public Hilo{

	private:
		HiloConfiguracion::stParametrosConfiguracion parametrosRun;
		bool corriendo;
		Mutex mutexCorriendo;
		std::vector<HiloConfiguracion*> clientesEnConfiguracion;

		void* run(void* parametro); // Se invoca a "this->start" (heredada de la clase Hilo) para que se use el run con hilo

		// Métodos dentro del run
		void rutina(HiloConfiguracion::stParametrosConfiguracion* parametrosEntrada);
		void cerrarHiloConfiguracion(int idVectorHiloConfiguracion);

	public:
		HiloReceptor(void);
		~HiloReceptor(void);

		// Inicio de actividad
		void correrRecepcion(HiloConfiguracion::stParametrosConfiguracion parametrosRun);

		// Verificación y finalización de actividad
		void detenerActividad(void);
		bool estaActivo(void);

};

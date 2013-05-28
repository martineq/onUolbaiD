#pragma once

#include "../Sockets/SocketServidor.h"
#include "../Hilos/Hilo.h"
#include "../Hilos/Mutex.h"
#include "../Serializacion/Serializadora.h"
#include "../Constantes/Constantes.h"
#include "../../Servidor/modelo/ModeloFactory.h"

class HiloConfiguracion: public Hilo{
	
	public:
		// Para usar hilos
		struct stParametrosConfiguracion{
			int idCliente;
			ModeloFactory* pModeloFactory;	// Se encarga de crear al jugador
			void* pServidor;				// Para el envío/recepción de datos
			void* pModeloNivel;				// Para notificar nuevo jugador, se usa dentro del ModeloFactory
			bool singlePlayer;				// Para saber si estoy en modo Single Player
		};

	private:
		stParametrosConfiguracion parametrosRun;
		bool corriendo;
		bool configuracionFinalizada;
		Mutex mutexCorriendo;
		Mutex mutexConfiguracionFinalizada;

		void* run(void* parametro); // Se invoca a "this->start" (heredada de la clase Hilo) para que se use el run con hilo

		// Métodos dentro del run
		void rutina(stParametrosConfiguracion* parametrosConfiguracion);
		void finalizarConfiguracion(void);

	public:
		HiloConfiguracion(void);
		~HiloConfiguracion(void);
		
		// Inicio de actividad
		void correrConfiguracion(stParametrosConfiguracion parametrosRun);
		
		// Verificación y finalización de actividad
		bool estaConfiguracionFinalizada(void);
		bool estaActivo(void);
		void detenerActividad(void);

};

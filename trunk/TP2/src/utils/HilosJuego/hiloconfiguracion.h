#pragma once

#include "../Sockets/SocketServidor.h"
#include "../Hilos/Hilo.h"
#include "../Hilos/Mutex.h"
#include "../Serializacion/Serializadora.h"
#include "../LectorDirectorios/LectorDirectorios.h"
#include "../Constantes/Constantes.h"

// TODO: Agregar las clases correspondientes


class HiloConfiguracion: public Hilo{

	public:
		// Para usar hilos
		struct stParametrosConfiguracion{
			void* pJuego;
			void* pMenu;
			int* pCantidadJugadores;
			Mutex* pMutexCantidadJugadores;
			SocketServidor* pServidor;		// Para el envío/recepción de datos
		};

	private:
		stParametrosConfiguracion parametrosRun;
		long idCliente; // TODO: Ver si hace falta
		bool corriendo;
		bool configuracionFinalizada;
		Mutex mutexCorriendo;
		Mutex mutexConfiguracionFinalizada;

		void* run(void* parametro); // Se invoca a "this->start" (heredada de la clase Hilo) para que se use el run con hilo
		
		// Métodos dentro del run
		void rutina(stParametrosConfiguracion* parametrosConfiguracion);
		void finalizarConfiguracion(void);
		bool enviarArchivosDeConfiguracion(void);
		bool enviarListaDeArchivos(std::vector<std::string> lista);

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

// TODO: PASO UNO >>> Modificar el código de este hilo según el modelo del juego. Hacer uso de los mutex necesarios para el uso de esas variables
// TODO: PASO DOS >>> Refactorizar rutina() en métodos mas pequeños
// TODO: PASO TRES >>> Antes que se usen los parámetros exteriores se debe preguntar si este hilo se encuentra en actividad, sino se debe salir inmediatamente (Importante: debe hacerse siempre)
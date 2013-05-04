#pragma once

#include "../Sockets/SocketServidor.h"
#include "../Hilos/Hilo.h"
#include "../Hilos/Mutex.h"
#include "../Serializacion/Serializadora.h"
#include "../LectorDirectorios/LectorDirectorios.h"
#include "../Constantes/Constantes.h"

class HiloConfiguracion: public Hilo{
	
	public:
		// Para usar hilos
		struct stParametrosConfiguracion{
			SocketServidor* pServidor;		// Para el env�o/recepci�n de datos
			void* pModeloJuego;
			void* pModeloFactory;
			int* pJugadoresConectados;
			Mutex* pMutexJugadoresConectados;
		};

	private:
		stParametrosConfiguracion parametrosRun;
		bool corriendo;
		bool configuracionFinalizada;
		Mutex mutexCorriendo;
		Mutex mutexConfiguracionFinalizada;

		void* run(void* parametro); // Se invoca a "this->start" (heredada de la clase Hilo) para que se use el run con hilo

		// M�todos dentro del run
		void rutina(stParametrosConfiguracion* parametrosConfiguracion);
		void finalizarConfiguracion(void);
		bool enviarArchivosDeConfiguracion(SocketServidor* pServidor,int idSocketCliente);
		bool enviarListaDeArchivos(std::vector<std::string> lista,SocketServidor* pServidor,int idSocketCliente);

	public:
		HiloConfiguracion(void);
		~HiloConfiguracion(void);
		
		// Inicio de actividad
		void correrConfiguracion(stParametrosConfiguracion parametrosRun);
		
		// Verificaci�n y finalizaci�n de actividad
		bool estaConfiguracionFinalizada(void);
		bool estaActivo(void);
		void detenerActividad(void);

};

// TODO: PASO UNO >>> Modificar el c�digo de este hilo seg�n el modelo del juego. Hacer uso de los mutex necesarios para el uso de esas variables
// TODO: PASO DOS >>> Refactorizar rutina() en m�todos mas peque�os
// TODO: PASO TRES >>> Antes que se usen los par�metros exteriores se debe preguntar si este hilo se encuentra en actividad, sino se debe salir inmediatamente (Importante: debe hacerse siempre)
// TODO: El ID del cliente ser� dado por el ID de socket que me de el SockeServidor al realizar el aceptar(), o sea "ModeloJugador->ID" = "SocketCliente->ID"
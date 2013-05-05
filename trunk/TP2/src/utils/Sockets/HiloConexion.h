#pragma once

#include <iostream>
#include <fstream> 
#include <string>
#include <list>
#include "../Constantes/Constantes.h"
#include "../Log/Log.h"
#include "../Hilos/Hilo.h"
#include "../Hilos/Mutex.h"
#include "./SocketApp.h"
#include "../Temporizador/Temporizador.h"

class HiloConexion: public Hilo{

	public:
		// Para usar hilos
		struct stParametrosRun{
			long idCliente;
			char opcion;
			SocketApp* pSocket;
			bool* pEsIndividual;
			std::list<std::string>* pCola;				// Este puntero puede ser de una cola de entrada o de salida
			std::list<std::string>* pColaEntradaMasiva;
			std::list<long>* pIdMasivoConError;
			Mutex* pMutexMasivo;
			Mutex* pMutexCola;
			Mutex* pMutexEsIndividual;
		};

	private:
		stParametrosRun parametrosRun;
		bool corriendo;
		Mutex mutexCorriendo;

		void* run(void* parametro); // Se invoca a "this->start" (heredada de la clase Hilo) para que se use el run con hilo

		// Métodos dentro del run
		void rutina(stParametrosRun* parametrosEntrada);
		void loopEntradaIndividual(stParametrosRun* parametrosEntrada);
		void loopEntradaMasivo(stParametrosRun* parametrosEntrada);
		void rutinaSalida(stParametrosRun* parametrosSalida);
		void loopSalidaIndividual(stParametrosRun* parametrosSalida);
		void loopSalidaMasivo(stParametrosRun* parametrosSalida);
		void delay(void);

	public:
		HiloConexion(void);
		~HiloConexion(void);

		// Inicio de actividad
		void correrConexion(HiloConexion::stParametrosRun parametrosRun);

		// Verificación y finalización de actividad
		void detenerActividad(void);		
		bool estaActivo(void);

};

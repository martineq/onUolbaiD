#pragma once

#include "../Hilos/Mutex.h"
#include "./HiloConexion.h"
#include "./SocketApp.h"

class ConexionCliente{

	private:
		SocketApp socketApp;						// Datos del socket
		long id;									// ID de la conexi�n
		bool esIndividual;							// Indica si los mensajes se reciben/envian en una cola individual (==true) o si van a una cola com�n a todas las conexiones (==false)
		static long ticket;							// Variable para obtener un valor de ID �nico. Es como un talonario de numeros	

		// Colas de datos
		std::list<std::string> colaEntrada;			// Cola de entrada de datos
		std::list<std::string> colaSalida;			// Cola de salida de datos
		
		// Hilos
		HiloConexion hiloEntrada;					// Hilo de entrada
		HiloConexion hiloSalida;					// Hilo de salida

		// Mutex
		Mutex mutexEsIndividual;				// Exclusi�n mutua para el booleano esIndividual
		Mutex mutexColaEntrada;						// Exclusi�n mutua para la cola de entrada
		Mutex mutexColaSalida;						// Exclusi�n mutua para la cola de salida

		HiloConexion::stParametrosRun iniciarParametrosRun(char opcion,std::list<std::string>* colaEntradaMasiva,Mutex* mutexColaEntradaMasiva, std::list<long>* clientesMasivosConError);

	public:
		ConexionCliente(void);
		~ConexionCliente(void);

		// Inicializaci�n y cierre de conexi�n (Usado por <Cliente>)
		bool iniciarAplicacion(void);
		bool finalizarAplicacion(void);
		bool abrir(void);
		bool cerrar(void);
		bool conectar(const char* nombreHost, int puerto);
	
		// Configuraci�n e identificaci�n de la conexi�n (Usado por <Servidor>)
		long getId(void);
		void setMasiva(void);
		void setEsIndividual(void);
		bool getEsIndividual(void);
		void setSocket(SOCKET socket);

		// Inicializaci�n y cierre de hilos (Usado por <Cliente> y <Servidor>)
		void iniciarRecepcion(std::list<std::string>* colaEntradaMasiva,Mutex* mutexColaEntradaMasiva, std::list<long>* clientesMasivosConError);
		void iniciarEnvio(void);
		void cerrarActividad(void);
		
		// Wrapper para tomar/recibir los datos que manejan los hilos (Usado por <Cliente> y <Servidor>)
		bool enviarDirecto(const char *pBuffer,unsigned int tamanio);
		bool recibirDirecto(char **pBuffer,unsigned int& tamanioRecibido);
		bool enviar(const char *pBuffer,unsigned int tamanio);
		bool recibir(char **pBuffer,unsigned int& tamanioRecibido);
		bool enviarArchivo(const char *rutaOrigen);
		bool recibirArchivo(const char *rutaDestino);

};

#pragma once

#include "./ConexionServidor.h"
#include "../Constantes/Constantes.h"
#include "../Serializacion/Serializadora.h"

class SocketServidor{

	private:
		int puerto;										// Puerto al que pertenece el servidor
		ConexionServidor miConexion;					// La conexión del servidor
		std::list<long> todosLosClientesConError;		// Listado de todos los clientes "masivos" que reportaron error de conexion. Acá aparecen los individuales y los masivos. Sin mutex, ya que no lo toca ningún hilo	
		std::vector<ConexionCliente*> conexionClientes;	// Vector de Conexion para todos los clientes		
		Mutex mutexConexionClientes;					// Exclusión mutua para la variable <conexionClientes>, ya que la misma podría a ser llamada por varios hilos a la vez (por ej aceptarCliente() eliminarCliente() )
		
		std::list<std::string> colaEntradaMasiva;		// Cola de entrada compartida de datos. Puede ser usada por varias instancias de <Conexion>. Controlado con mutexMasivo
		std::list<long> clientesMasivosConError;		// Listado de Clientes "masivos" que tengan error de conexion, la llenan los hilos al recibir masivo y el servidor luego los envia a la lista donde están todos. Controlado con mutexMasivo
		Mutex mutexMasivo;								// Exclusión mutua para la variable <colaEntradaMasiva> y <clientesMasivosConError>, se usa debido que la pueden usar varias conexiones a la vez

		bool desconectar(void);
		long buscarCliente(int idCliente);
		bool procesarClientesMasivosConError(void);
		bool archivoEnviarIndividual(const char *rutaOrigen,long idCliente);
		bool archivoRecibirIndividual(const char *rutaDestino,long idCliente);
		void insertarClienteConError(long idCliente);
		ConexionCliente* getConexionCliente(long indice);
		long tamanioConexionClientes(void);

		// Funciones de envio recepción con uso directo de char*
		bool enviarIndividualChar(const char *pBuffer,unsigned int tamanio,long idCliente);
		bool enviarMasivoChar(const char *pBuffer,unsigned int tamanio);
		bool recibirIndividualChar(char** pbuffer, int& tamanioRecibido,long idCliente);
		bool recibirMasivoChar(char** pbuffer, int& tamanioRecibido);

	public:
		SocketServidor(void);
		~SocketServidor(void);
		
		// Para iniciar el servidor. Se hace una sola vez
		bool inciarServidor(int puerto);

		// Para aceptar/eliminar clientes, identificar los clientes erróneos, renombrar el ID
		int aceptarCliente();
		bool eliminarCliente(int idCliente);
		std::list<long> getNuevosClientesErroneos(void);
		bool renombrarIdCliente(int idActual, int idNuevo);

		// Para setear el modo en que se comporta la recpción/envío de mensajes de un cliente
		bool setClienteIndividual(int idCliente);
		bool setClienteMasivo(int idCliente);

		// Para enviar/recibir. Integradas con la clase Serializadora
		bool enviarIndividual(Serializadora& s,int idCliente);
		bool enviarMasivo(Serializadora& s);
		bool recibirIndividual(Serializadora& s,int idCliente);
		bool recibirMasivo(Serializadora& s);

		// Para enviar/recibir archivos
		bool enviarArchivosIndividual(std::list<std::string> rutaDeArchivosParaEnviar,long idCliente);
		bool recibirArchivosIndividual(std::list<std::string> rutaDeArchivosParaRecibir,long idCliente);

};

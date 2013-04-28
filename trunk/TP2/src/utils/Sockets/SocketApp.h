#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <winsock.h>
#include "../Log/Log.h"

// Clase con todas la utilidades necesarias para el uso de Sockets
class SocketApp{

	private:
		// Datos del socket
		WSADATA infoDeSocket;						// Struct con información de Socket
		SOCKET miSocket;							// Socket asignado para la conexión del servidor

		// Funciones auxiliares
		static unsigned long buscarIpDeHost(const char *nombreHost);
		static std::string obtenerDescripcionDeHost(const sockaddr_in &sockAddr);
		static void llenarDireccionDeSocket(sockaddr_in *pDireccionSocket, int puerto);
		static bool llenarDireccionDeSocket(sockaddr_in *pDireccionSocket, int puerto, const char* nombreHost);
		int miRecv(char *buf,int longitud,int flags);
		int miSend(const char *buf,int longitud,int flags);
		bool recvFull(char *buf,int longitud,int flags);
		bool sendFull(const char *buf,int longitud,int flags);

	public:
		SocketApp(void);
		~SocketApp(void);

		// Inicialización y cierre de conexión
		bool iniciarAplicacion(void);
		bool finalizarAplicacion(void);
		bool abrir(void);
		bool cerrar(void);

		// Funciones varias
		void setSocket(SOCKET socket);
		bool selectEscritura(int microsegundos);
		bool selectLectura(int microsegundos);

		// Solo para Servidor
		bool enlazarConexion(int puerto);
		bool escuchar(void);
		bool aceptarCliente(SOCKET& socket);

		// Solo para Cliente
		bool conectar(const char* nombreHost, int puerto);
		bool enviar(const char *pBuffer,unsigned int tamanio);
		bool recibir(char **pBuffer,unsigned int& tamanio);
		bool enviarArchivo(const char *rutaOrigen);
		bool recibirArchivo(const char *rutaDestino);

};
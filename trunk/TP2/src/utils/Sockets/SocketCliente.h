#pragma once

#include "./ConexionCliente.h"

class SocketCliente {

	private:
		ConexionCliente miConexion;
		bool envioDirecto;

	public:
		SocketCliente(void);
		~SocketCliente(void);
		
		// Para iniciar el cliente. Se hace una sola vez
		bool iniciarCliente(const char* nombreHost, int puerto);

		// Cambio de la forma de envío de datos
		void setEnvioDirecto(void);
		void setEnvioIndirecto(void);

		// Para enviar/recibir
		bool enviar(const char *pBuffer,unsigned int tamanio);
		bool recibir(char **pBuffer,unsigned int& tamanioRecibido);
		bool enviarArchivo(const char *rutaOrigen);
		bool recibirArchivo(const char *rutaDestino);

};

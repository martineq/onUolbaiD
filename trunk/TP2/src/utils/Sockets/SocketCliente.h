#pragma once

#include "./ConexionCliente.h"
#include "../../utils/Serializacion/Serializadora.h"

class SocketCliente {

	private:
		ConexionCliente miConexion;
		bool envioDirecto;

		// Funciones de envio recepción con uso directo de char*
		bool enviarChar(const char *pBuffer,unsigned int tamanio);
		bool recibirChar(char **pBuffer,unsigned int& tamanioRecibido);

	public:
		SocketCliente(void);
		~SocketCliente(void);
		
		// Para iniciar el cliente. Se hace una sola vez
		bool iniciarCliente(const char* nombreHost, int puerto);

		// Cambio de la forma de envío de datos
		void setEnvioDirecto(void);
		void setEnvioIndirecto(void);

		// Para enviar/recibir
		bool enviar(Serializadora& s);
		bool recibir(Serializadora& s);
		bool enviarArchivo(const char *rutaOrigen);
		bool recibirArchivo(const char *rutaDestino);

};

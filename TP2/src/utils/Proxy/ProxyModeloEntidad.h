#pragma once

#include "../Sockets/SocketCliente.h"
#include "../Sockets/SocketServidor.h"
#include "../Serializacion/Serializadora.h"

class ProxyModeloEntidad{

	public:
		struct stEntidad{
			// Info para el proxy
			int id;				// Si el ID no se encuentra en el cliente quiere decir que es una nueva entidad, la debe agregar.
			std::string nombreEntidad;
			bool errorEnSocket; // No hace falta serializar este valor. Esta atributo lo setea el proxy cuando recibe datos (al hidratar). Si el socket me da errror seteo ac� en true, sino lo dejo en false
			bool entidadCongelada;
			bool esJugador;			
			// Datos para actualizar en la entidad
			double pixelAnteriorX;
			double pixelAnteriorY;
			int posicionAnteriorX;
			int posicionAnteriorY;
			double pixelSiguienteX;
			double pixelSiguienteY;
			int posicionSiguienteX;
			int posicionSiguienteY;
			int direccion;
			bool esUltimoMovimiento;
			int accion;
			std::string nombreJugador;
			std::string actualizacionMapa;  // La idea es serializar toda la actulizaci�n de la matriz y mandarlo por ac�. Lo pongo en un string porque el tama�o de la actualizaci�n es variable
			std::string nombreRemitente;
			std::string mensaje;
		};

	private:
		SocketCliente* pCliente;
		SocketServidor* pServidor;

	public:
		ProxyModeloEntidad(void);
		~ProxyModeloEntidad(void);

		// Para setear al principio
		void setSocketCliente(SocketCliente* pCliente);
		void setSocketServidor(SocketServidor* pServidor);

		// Para usar en el momento de configuraci�n. Debe estar seteado el modo Individual.
		bool enviarEntidadIndividual(ProxyModeloEntidad::stEntidad entidad,int id); // Lo usa el lado Servidor
		bool recibirEntidadIndividual(ProxyModeloEntidad::stEntidad& entidad);		// Lo usa el lado Cliente

		// Para usar en el momento de juego. Debe estar seteado el modo Masivo.
		bool enviarEntidad(ProxyModeloEntidad::stEntidad entidad);					// Lo usa el lado Servidor
		bool recibirEntidad(ProxyModeloEntidad::stEntidad& entidad);				// Lo usa el lado Cliente
		void serializar(Serializadora& s,ProxyModeloEntidad::stEntidad& entidad);
		void hidratar(Serializadora& s,ProxyModeloEntidad::stEntidad& entidad);

		bool enviarMatriz(std::string matrix,int id);
		bool recibirMatrix(std::string& matrix);

		int sizeEntidad(ProxyModeloEntidad::stEntidad);
		// Auxiliares
		static void cargarStEntidad(ProxyModeloEntidad::stEntidad& entidad,int id,bool errorEnSocket,bool entidadCongelada,bool esJugador,std::string nombreEntidad, double pixelAnteriorX,double pixelAnteriorY,int posicionAnteriorX,int posicionAnteriorY,double pixelSiguienteX,double pixelSiguienteY,int posicionSiguienteX,int posicionSiguienteY,int direccion,bool esUltimoMovimiento, int accion,std::string nombreJugador);
};

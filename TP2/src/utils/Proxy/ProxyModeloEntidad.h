#pragma once

#include "../Sockets/SocketCliente.h"
#include "../Sockets/SocketServidor.h"

class ProxyModeloEntidad{

	public:
		struct stEntidad{
			// Info para el proxy
			int id;				// Si el ID no se encuentra en el cliente quiere decir que es una nueva entidad, la debe agregar.
			bool errorEnSocket; // No hace falta serializar este valor. Esta atributo lo setea el proxy cuando recibe datos (al hidratar). Si el socket me da errror seteo acá en true, sino lo dejo en false
			bool eliminarEntidad;
			std::string nombreNuevaEntidad;

			// Datos para actualizar en la entidad
			double pixelSiguienteX;
			double pixelSiguienteY;
			int direccion;
			bool esUltimoMovimiento;
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

		// Para usar en el momento de configuración. Debe estar seteado el modo Individual.
		bool enviarEntidadIndividual(ProxyModeloEntidad::stEntidad entidad,int id); // Lo usa el lado Servidor
		bool recibirEntidadIndividual(ProxyModeloEntidad::stEntidad& entidad);		// Lo usa el lado Cliente

		// Para usar en el momento de juego. Debe estar seteado el modo Masivo.
		bool enviarEntidad(ProxyModeloEntidad::stEntidad entidad);					// Lo usa el lado Servidor
		bool recibirEntidad(ProxyModeloEntidad::stEntidad& entidad);				// Lo usa el lado Cliente
};


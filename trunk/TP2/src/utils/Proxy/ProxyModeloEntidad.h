#pragma once

#include "../Sockets/SocketCliente.h"
#include "../Sockets/SocketServidor.h"

class ProxyModeloEntidad{

	public:
		struct stEntidad{
			// Info para el proxy
			int id;
			bool errorEnSocket; // No hace falta serializar este valor. Esta atributo lo setea el proxy cuando recibe datos (al hidratar). Si el socket me da errror seteo acá en true, sino lo dejo en false
			bool eliminarEntidad;
			
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

		void setSocketCliente(SocketCliente* pCliente);
		void setSocketServidor(SocketServidor* pServidor);
		bool enviarEntidad(ProxyModeloEntidad::stEntidad entidad);
		bool recibirEntidad(ProxyModeloEntidad::stEntidad& entidad);
};

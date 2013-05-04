#pragma once

#include "../Sockets/SocketCliente.h"
#include "../Sockets/SocketServidor.h"

class ProxyModeloEntidad{
		
	public:
		struct stEntidad{
			int id;
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

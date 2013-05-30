#pragma once

#include "../Sockets/SocketCliente.h"
#include "../Sockets/SocketServidor.h"
#include "../Serializacion/Serializadora.h"

class ProxyModeloEntidad{

	public:
		struct stEntidad{
			bool errorEnSocket;

			// ModeloEntidad
			int id;
			std::string nombreEntidad;
			bool esJugador;
			int posicionX;
			int posicionY;
			double pixelX;
			double pixelY;
			bool esUltimoMovimiento;

			// ModeloJugador
			std::string nombreJugador;
			int escudo;
			bool estaCongelado;
			int magia;
			int vida;
			int rangoVision;
			std::string actualizacionMapa;
			int idRemitente;
			std::string mensaje;
			
			int accion;
			
			stEntidad() {
				this->errorEnSocket = false;
				
				// ModeloEntidad
				this->id = ID_FALSO;
				this->esJugador = false;
				this->posicionX = 0;
				this->posicionY = 0;
				this->pixelX = 0;
				this->pixelY = 0;
				this->esUltimoMovimiento = true;

				// ModeloJugador
				this->escudo = 0;
				this->estaCongelado = false;
				this->magia = 0;
				this->vida = 0;
				this->rangoVision = 0;
				this->idRemitente = ID_FALSO;

				this->accion = 0;
			}
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
		void serializar(Serializadora& s,ProxyModeloEntidad::stEntidad& entidad);
		void hidratar(Serializadora& s,ProxyModeloEntidad::stEntidad& entidad);

		bool enviarMatriz(std::string matrix,int id);
		bool recibirMatrix(std::string& matrix);

		int sizeEntidad(ProxyModeloEntidad::stEntidad);
		// Auxiliares
		static void cargarStEntidad(ProxyModeloEntidad::stEntidad& entidad,int id,bool errorEnSocket,bool entidadCongelada,bool esJugador,std::string nombreEntidad,double pixelSiguienteX,double pixelSiguienteY,int posicionSiguienteX,int posicionSiguienteY,bool esUltimoMovimiento, int accion,std::string nombreJugador,int idRemitente,std::string mensaje);
		static void cargarMatriz(ProxyModeloEntidad::stEntidad& entidad,std::string matriz);
};

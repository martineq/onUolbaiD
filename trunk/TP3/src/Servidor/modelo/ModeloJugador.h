#pragma once

#include <stdlib.h>
#include <list>
#include "Posicion.h"
#include "ModeloEntidad.h"
#include "EstadoNivel.h"
#include "ModeloMovimiento.h"
#include "VistaMovimiento.h"

typedef enum Accion { CAMINANDO, ATACANDO };

class ModeloJugador {
	private:
		Posicion _posicionInicial;
		Posicion _pixelInicial;
		std::string _nombreJugador;
		ModeloEntidad* _modeloEntidad;
		Accion _accion;
		bool _estaCongelado;
		EstadoNivel* _estadoNivel;
		ModeloJugador* _enemigo;
		ModeloMovimiento* _modeloMovimiento;
		VistaMovimiento* _vistaMovimiento;
		Mutex _mutex;

		ModeloJugador(const ModeloJugador &modeloJugador);

		ModeloJugador& operator=(const ModeloJugador &modeloJugador);
		
	public:
		ModeloJugador(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad, std::string nombreJugador);

		virtual ~ModeloJugador();

		Accion accion();

		void accion(Accion accion);

		bool estaCongelado();

		void estaCongelado(bool estaCongelado);

		std::string nombreJugador();

		void nombreJugador(std::string nombreJugador);

		ModeloEntidad* modeloEntidad();

		ProxyModeloEntidad::stEntidad stEntidad();

		void asignarEntidadesMoviles(Mutex* mutexEntidadesMoviles, std::list<ModeloEntidad*>* entidadesMoviles);

		void asignarEntidades(Mutex* mutexEntidades, std::multimap<std::pair<int, int>, ModeloEntidad*>* entidades);

		void atacar(ModeloJugador* enemigo);

		void cambiarEstado();

		void cargarMatriz(ProxyModeloEntidad::stEntidad& entidad);

		bool chequearConexion();

		void enviarEstado();

		void enviarMensaje(ModeloJugador* remitente, std::string mensaje);

		void lastimar(int danio);

		void mover(Posicion posicion);
};

#pragma once

#include <stdlib.h>
#include <list>
#include "../../utils/Constantes/Constantes.h"
#include "Posicion.h"
#include "ModeloEntidad.h"
#include "ModeloItem.h"
#include "EstadoNivel.h"
#include "ModeloMovimiento.h"
#include "VistaMovimiento.h"

class ModeloItem;

typedef enum Accion { CAMINANDO, ATACANDO };

class ModeloJugador {
	private:
		Accion _accion;
		int _escudo;
		bool _estaCongelado;
		bool _tieneMapa;
		int _magia;
		std::string _nombreJugador;
		Posicion _pixelInicial;
		Posicion _posicionInicial;
		bool _puedeRevivir;
		int _vida;
		bool _ingresoAlJuego;
		
		ModeloEntidad* _modeloEntidad;
		EstadoNivel* _estadoNivel;
		ModeloJugador* _enemigo;
		ModeloItem* _item;
		ModeloMovimiento* _modeloMovimiento;
		VistaMovimiento* _vistaMovimiento;
		Mutex _mutex;

		void atacarEnemigo();

		void recogerItem();

		ModeloJugador(const ModeloJugador &modeloJugador);

		ModeloJugador& operator=(const ModeloJugador &modeloJugador);
		
	public:
		ModeloJugador(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad, std::string nombreJugador);

		virtual ~ModeloJugador();

		Accion accion();

		void accion(Accion accion);

		bool estaCongelado();

		void estaCongelado(bool estaCongelado);

		int magia();

		std::string nombreJugador();

		void nombreJugador(std::string nombreJugador);

		ModeloEntidad* modeloEntidad();

		bool puedeRevivir();

		void puedeRevivir(bool puedeRevivir);

		ProxyModeloEntidad::stEntidad stEntidad();

		int vida();

		void asignarEntidadesMoviles(Mutex* mutexEntidadesMoviles, std::list<ModeloEntidad*>* entidadesMoviles);

		void asignarEntidades(Mutex* mutexEntidades, std::multimap<std::pair<int, int>, ModeloEntidad*>* entidades);

		void atacar(ModeloJugador* enemigo);

		void cambiarEstado();

		void cargarMatriz(ProxyModeloEntidad::stEntidad& entidad);

		bool chequearConexion();

		void consumirMagia(int magia);

		void consumirVida(int vida);

		void enviarEstado();

		void enviarMensaje(ModeloJugador* remitente, std::string mensaje);

		bool estaEnRangoVision(ModeloJugador* enemigo);

		void mover(Posicion posicion);

		void recogerItem(ModeloItem* item);

		void recuperarEscudo(int escudo);

		void recuperarMagia(int magia);

		void recuperarVida(int vida);
		
		bool ingresoAlJuego(void);

		void ingresarAlJuego(void);

		bool tieneMapa();

		void setTieneMapa(bool);

		EstadoNivel* getEstadoNivel();
};

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
class ListaItems;

typedef enum Accion { CAMINANDO, ATACANDO };

class ModeloJugador {
	private:
		int _altoNivel;
		int _anchoNivel;
		Accion _accion;
		bool _autonomo;
		int _escudo;
		bool _estaCongelado;
		bool _tieneMapa;
		int _magia;
		std::string _nombreJugador;
		Posicion _pixelInicial;
		Posicion _posicionInicial;
		int _vida;
		bool _ingresoAlJuego;
		DWORD _instanteUltimoCambioEstado;
		int _danioAtaque;
		
		ListaEntidades* _listaEntidades;
		ListaItems* _listaItems;
		ModeloEntidad* _modeloEntidad;
		EstadoNivel* _estadoNivel;
		ModeloJugador* _enemigo;
		ModeloItem* _item;
		ModeloMovimiento* _modeloMovimiento;
		VistaMovimiento* _vistaMovimiento;
		Mutex _mutex;

		void atacarEnemigo();

		void matar();

		void recogerItem();

		void revivir();

		ModeloJugador(const ModeloJugador &modeloJugador);

		ModeloJugador& operator=(const ModeloJugador &modeloJugador);
		
	public:
		ModeloJugador(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad, std::string nombreJugador, int vida, int magia, int ataque);

		virtual ~ModeloJugador();

		Accion accion();

		void accion(Accion accion);

		bool autonomo();

		void autonomo(bool autonomo);

		bool estaCongelado();

		void estaCongelado(bool estaCongelado);

		int magia();

		std::string nombreJugador();

		void nombreJugador(std::string nombreJugador);

		ModeloEntidad* modeloEntidad();

		ProxyModeloEntidad::stEntidad stEntidad();

		int vida();

		void asignarListaEntidades(ListaEntidades* listaEntidades);

		void asignarListaItems(ListaItems* listaItems);

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

		void danioAtaque(int danio);

		int danioAtaque(void);
};

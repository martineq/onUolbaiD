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

class ListaJugadores;
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
		bool _estaDesconectado;
		bool _tieneMapa;
		int _tieneHechizo;
		int _magia;
		int _maximoMagia;
		std::string _nombreJugador;
		Posicion _pixelInicial;
		Posicion _posicionInicial;
		int _vida;
		int _maximoVida;
		bool _ingresoAlJuego;
		DWORD _instanteCongelamiento;
		DWORD _instanteUltimoCambioEstado;
		int _danioAtaque;
		int _idDuenio;

		ListaJugadores* _listaEnemigos;
		ListaEntidades* _listaEntidades;
		ListaItems* _listaItems;
		ListaJugadores* _listaJugadores;
		ListaJugadores* _listaGolems;
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

		int coordenadaAlAzar(int media, int desvio, int cotaMinima , int cotaMaxima );

		ModeloJugador(const ModeloJugador &modeloJugador);

		ModeloJugador& operator=(const ModeloJugador &modeloJugador);
		
	public:
		ModeloJugador(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad, std::string nombreJugador, int maximoVida, int maximoMagia, int ataque, int idDuenio, int tipoEntidad);

		virtual ~ModeloJugador();

		Accion accion();

		void accion(Accion accion);

		bool autonomo();

		void autonomo(bool autonomo);

		bool estaCongelado();

		void estaCongelado(bool estaCongelado);

		bool estaDesconectado();

		void estaDesconectado(bool estaDesconectado);

		int magia();

		std::string nombreJugador();

		void nombreJugador(std::string nombreJugador);

		ModeloEntidad* modeloEntidad();

		ProxyModeloEntidad::stEntidad stEntidad();

		int vida();

		void asignarListaEnemigos(ListaJugadores* listaEnemigos);

		void asignarListaEntidades(ListaEntidades* listaEntidades);

		void asignarListaItems(ListaItems* listaItems);

		void asignarListaJugadores(ListaJugadores* listaJugadores);

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

		void setTieneHechizo(bool);

		EstadoNivel* getEstadoNivel();

		void danioAtaque(int danio);

		int danioAtaque(void);

		int idDuenio(void);

		int maximoVida(void);

		Posicion posicionGolem(void);
};

class ListaJugadores {
	private:
		ListaEntidades* _listaEntidades;
		std::list<ModeloJugador*> _jugadores;
		Mutex _mutex;
		
	public:
		ListaJugadores();

		virtual ~ListaJugadores();

		void agregarJugador(ModeloJugador* jugador);

		void asignarListaEntidades(ListaEntidades* listaEntidades);

		void destruirJugadores();

		ModeloJugador* obtenerJugador(int id);

		ModeloJugador* obtenerJugador(Posicion posicion);

		std::list<ModeloJugador*> obtenerJugadores();

		void removerJugador(ModeloJugador* jugador);
};

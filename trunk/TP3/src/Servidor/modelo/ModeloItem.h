#pragma once

#include <map>

#include "../../utils/Hilos/Mutex.h"
#include "ModeloEntidad.h"
#include "ModeloJugador.h"

class ModeloJugador;
class ListaJugadores;

class ModeloItem {
	private:
		ModeloEntidad* _modeloEntidad;
		bool _disponible;
		Mutex _mutex;

		ModeloItem(const ModeloItem &modeloItem);

		ModeloItem& operator=(const ModeloItem &modeloItem);

	public:
		ModeloItem(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloItem();

		bool disponible();

		void disponible(bool disponible);

		ModeloEntidad* modeloEntidad();

		ProxyModeloEntidad::stEntidad stEntidad();

		void enviarEstado();

		virtual bool inmediato() = 0;

		virtual void aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos) = 0;
};

class ListaItems {
	private:
		ListaEntidades* _listaEntidades;
		std::multimap<std::pair<int, int>, ModeloItem*> _items;
		Mutex _mutex;

	public:
		ListaItems();

		virtual ~ListaItems();

		void agregarItem(ModeloItem* item);

		void asignarListaEntidades(ListaEntidades* listaEntidades);

		void destruirItems();

		ModeloItem* obtenerItem(Posicion posicion);

		std::multimap<std::pair<int, int>, ModeloItem*> obtenerItems();

		void removerItem(ModeloItem* item);
};

class ModeloBotella : public ModeloItem {
	public:
		ModeloBotella(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloBotella();
		
		bool inmediato();

		void aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);
};

class ModeloCorazon : public ModeloItem {
	public:
		ModeloCorazon(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloCorazon();
		
		bool inmediato();

		void aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);
};

class ModeloEscudo : public ModeloItem {
	public:
		ModeloEscudo(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloEscudo();
		
		bool inmediato();

		void aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);
};

class ModeloLampara : public ModeloItem {
	public:
		ModeloLampara(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloLampara();
		
		bool inmediato();

		void aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);
};

class ModeloMapa: public ModeloItem {
	public:
		ModeloMapa(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloMapa();
		
		bool inmediato();

		void aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);
};

class ModeloZapato : public ModeloItem {
	public:
		ModeloZapato(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloZapato();
		
		bool inmediato();

		void aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);
};

class ModeloEspada : public ModeloItem {
	public:
		ModeloEspada(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloEspada();
		
		bool inmediato();

		void aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);
};

class ModeloHechizoHielo : public ModeloItem {
	private:
		int _altoNivel;
		int _anchoNivel;

	public:
		ModeloHechizoHielo(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloHechizoHielo();
		
		bool inmediato();

		void aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);
};

class ModeloBomba : public ModeloItem {
	private:
		int _altoNivel;
		int _anchoNivel;

	public:
		ModeloBomba(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloBomba();
		
		bool inmediato();

		void aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);
};

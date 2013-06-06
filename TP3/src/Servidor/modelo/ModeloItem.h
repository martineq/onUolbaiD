#pragma once

#include <map>

#include "../../utils/Hilos/Mutex.h"
#include "ModeloEntidad.h"
#include "ModeloJugador.h"
#include "../../utils/Proxy/ProxyModeloEntidad.h"

class ModeloJugador;
class ListaJugadores;

class ModeloItem {
	private:
		ModeloEntidad* _modeloEntidad;
		ModeloJugador* _jugador;
		ListaJugadores* _listaJugadores;
		ListaJugadores* _listaEnemigos;
		bool _activo;
		Mutex _mutex;

		ModeloItem(const ModeloItem &modeloItem);

		ModeloItem& operator=(const ModeloItem &modeloItem);

	protected:
		virtual bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos) = 0;

	public:
		ModeloItem(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad, int tipoEntidad);

		virtual ~ModeloItem();

		ModeloEntidad* modeloEntidad();

		ProxyModeloEntidad::stEntidad stEntidad();

		void activar();

		void asignarJugador(ModeloJugador* jugador);

		void asignarListaJugadores(ListaJugadores* listaJugadores);

		void asignarListaEnemigos(ListaJugadores* listaEnemigos);

		void cambiarEstado();

		bool disponible();

		void enviarEstado();

		virtual bool inmediato() = 0;
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
	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);

	public:
		ModeloBotella(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloBotella();
		
		bool inmediato();
};

class ModeloCorazon : public ModeloItem {
	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);
	
	public:
		ModeloCorazon(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloCorazon();
		
		bool inmediato();
};

class ModeloEscudo : public ModeloItem {
	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);

	public:
		ModeloEscudo(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloEscudo();
		
		bool inmediato();
};

class ModeloLampara : public ModeloItem {
	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);

	public:
		ModeloLampara(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloLampara();
		
		bool inmediato();
};

class ModeloMapa: public ModeloItem {
	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);

	public:
		ModeloMapa(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloMapa();
		
		bool inmediato();
};

class ModeloZapato : public ModeloItem {
	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);

	public:
		ModeloZapato(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloZapato();
		
		bool inmediato();
};

class ModeloEspada : public ModeloItem {
	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);

	public:
		ModeloEspada(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloEspada();
		
		bool inmediato();
};

class ModeloHechizoHielo : public ModeloItem {
	private:
		int _altoNivel;
		int _anchoNivel;

	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);

	public:
		ModeloHechizoHielo(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloHechizoHielo();
		
		bool inmediato();
};

class ModeloBomba : public ModeloItem {
	private:
		int _altoNivel;
		int _anchoNivel;
		DWORD _instanteActivacion;

	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);

	public:
		ModeloBomba(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloBomba();
		
		bool inmediato();
};

class ModeloGolem : public ModeloItem {

	private:
		// Valores tomados desde el ModeloFactory al instanciar
		int idGolem;
		std::string nombreEntidad;
		int alto;
		int ancho;
		int fps;
		int anchoEscenario;
		int altoEscenario;
		void* pSocketServidor;
		int mana;

		// Valores tomados a partir del jugador que lo invoca
		int velocidad;
		int danio;
		int vida;
		int idDuenio;
		Posicion pos;

		ModeloJugador* crearGolem();

	public:
		ModeloGolem(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloGolem();
		
		bool inmediato();

		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos);

		void cargarDatos(int idGolem, int alto, int ancho, int fps, int anchoEscenario, int altoEscenario, void* pSocketServidor);
};
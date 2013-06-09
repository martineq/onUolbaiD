#pragma once

#include <map>

#include "../../utils/Hilos/Mutex.h"
#include "ModeloEntidad.h"
#include "ModeloJugador.h"
#include "../../utils/Proxy/ProxyModeloEntidad.h"
#include "ModeloDrop.h"

class ModeloJugador;
class ListaJugadores;

class ModeloItem {
	private:
		ModeloEntidad* _modeloEntidad;
		ModeloJugador* _jugador;
		ListaJugadores* _listaJugadores;
		ListaJugadores* _listaEnemigos;
		ListaJugadores* _listaGolems;
		bool _activo;
		Mutex _mutex;

		ModeloItem(const ModeloItem &modeloItem);

		ModeloItem& operator=(const ModeloItem &modeloItem);

		static ModeloItem* crearItem(ModeloDrop::stDatoItem datoItem, ModeloDrop::stDatoGolem datosGolem, Posicion pos, ModeloDrop::stDatosDrop datosDrop);

	protected:
		virtual bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems) = 0;

	public:
		ModeloItem(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad, int tipoEntidad);

		virtual ~ModeloItem();

		ModeloEntidad* modeloEntidad();

		ProxyModeloEntidad::stEntidad stEntidad();

		void activar();

		void asignarJugador(ModeloJugador* jugador);

		void asignarListaJugadores(ListaJugadores* listaJugadores);

		void asignarListaEnemigos(ListaJugadores* listaEnemigos);

		void asignarListaGolems(ListaJugadores* listaGolems);

		void cambiarEstado();

		bool disponible();

		void enviarEstado();

		int vida();

		static ModeloItem* drop(ModeloDrop::stDatosDrop datos, Posicion pos);
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
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems);

	public:
		ModeloBotella(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloBotella();
};

class ModeloCorazon : public ModeloItem {
	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems);
	
	public:
		ModeloCorazon(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloCorazon();
};

class ModeloEscudo : public ModeloItem {
	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems);

	public:
		ModeloEscudo(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloEscudo();
};

class ModeloLampara : public ModeloItem {
	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems);

	public:
		ModeloLampara(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloLampara();
};

class ModeloMapa: public ModeloItem {
	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems);

	public:
		ModeloMapa(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloMapa();
};

class ModeloZapato : public ModeloItem {
	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems);

	public:
		ModeloZapato(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloZapato();
};

class ModeloEspada : public ModeloItem {
	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems);

	public:
		ModeloEspada(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloEspada();
};

class ModeloHechizoHielo : public ModeloItem {
	private:
		int _altoNivel;
		int _anchoNivel;

	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems);

	public:
		ModeloHechizoHielo(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloHechizoHielo();
};

class ModeloBomba : public ModeloItem {
	private:
		int _altoNivel;
		int _anchoNivel;
		DWORD _instanteActivacion;

	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems);

	public:
		ModeloBomba(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloBomba();
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
		ModeloDrop::stDatosDrop datosDrop;

		// Valores tomados a partir del jugador que lo invoca
		int velocidad;
		int vida;
		int danio;
		int idDuenio;
		Posicion pos;

		ModeloJugador* crearGolem();

	public:
		ModeloGolem(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloGolem();
		
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems);

		void cargarDatos(int idGolem, int alto, int ancho, int fps, int anchoEscenario, int altoEscenario, void* pSocketServidor, ModeloDrop::stDatosDrop datosDrop);
};

class ModeloBandera : public ModeloItem {
	protected:
		bool aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems);

	public:
		ModeloBandera(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloBandera();
};

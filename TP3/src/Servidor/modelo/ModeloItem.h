#pragma once

#include <map>

#include "../../utils/Hilos/Mutex.h"
#include "ModeloEntidad.h"
#include "ModeloJugador.h"

class ModeloJugador;

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

		virtual void aplicar(ModeloJugador* jugador) = 0;
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
		
		void aplicar(ModeloJugador* jugador);
};

class ModeloCorazon : public ModeloItem {
	public:
		ModeloCorazon(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloCorazon();
		
		void aplicar(ModeloJugador* jugador);
};

class ModeloEscudo : public ModeloItem {
	public:
		ModeloEscudo(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloEscudo();
		
		void aplicar(ModeloJugador* jugador);
};

class ModeloLampara : public ModeloItem {
	public:
		ModeloLampara(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloLampara();
		
		void aplicar(ModeloJugador* jugador);
};

class ModeloMapa: public ModeloItem {
	public:
		ModeloMapa(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloMapa();
		
		void aplicar(ModeloJugador* jugador);
};

class ModeloZapato : public ModeloItem {
	public:
		ModeloZapato(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloZapato();
		
		void aplicar(ModeloJugador* jugador);
};

class ModeloEspada : public ModeloItem {
	public:
		ModeloEspada(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloEspada();
		
		void aplicar(ModeloJugador* jugador);
};

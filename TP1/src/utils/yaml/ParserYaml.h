#pragma once

#include <fstream>
#include <list>
#include <yaml-cpp/yaml.h>
#include "../Constantes.h"
#include "../Log/Logger.h"

class ParserYaml{

private:

	////////////////////////////
	// Structs para la prueba //
	////////////////////////////
	struct Vec3 {
	   float x, y, z;
	};

	struct Power {
	   std::string name;
	   int damage;
	};

	struct Monster {
	   std::string name;
	   Vec3 position;
	   std::vector <Power> powers;
	};
public:
	///////////////////////
	// Structs del juego //
	///////////////////////
	struct stPantalla {
		int alto;
		int ancho;
		std::string fondo;
	};

	struct stParametros {
		int margenScroll;
		int velPersonaje;
	};

	struct stAnimacion {
		std::string nombre;
		int periodo;
		std::list <std::string> sprites;
	};

	struct stTipoPersonaje {
		std::string nombre;
		int alto;
		int ancho;
		std::list <stAnimacion> animaciones;
	};

	struct stTextura {
		std::string nombre;
		std::string ruta;
	};

	struct stEscalera {
		int alto;
		int ancho;
		int x;
		int y;
		std::string textura;
	};

	struct stPersonaje {
		std::string tipo;
		int x;
		int y;
	};

	struct stPlataforma {
		int alto;
		int ancho;
		int x;
		int y;
		std::string textura;
	};

	struct stNivel {
		int alto;
		int ancho;
		std::list <stEscalera> escaleras;
		std::list <stPersonaje> personajes;
		std::list <stPlataforma> plataformas;
	};

	struct stJuego {
		stPantalla pantalla;
		stParametros parametros;
		std::list <stTipoPersonaje> tiposPersonaje;
		std::list <stTextura> texturas;
		stNivel nivel;
	};

private:
	// Funciones para la prueba
	// Ya no se va a usar. Las dejo por las dudas en privado.
	void prueba(void);
	void cargaVec3(const YAML::Node& nodo, Vec3& v);
	void cargaPower(const YAML::Node& nodo, Power& power);
	void cargaMonster(const YAML::Node& nodo, Monster& monster);

	// Funciones para el juego
	void cargaStPantalla(const YAML::Node& nodo, stPantalla& pantalla);
	void cargaStParametros(const YAML::Node& nodo, stParametros& parametros);
	void cargaListaSprites(const YAML::Node& nodo, std::list <std::string>& sprites);
	void cargaListaAnimaciones(const YAML::Node& nodo, std::list <stAnimacion>& animaciones);
	void cargaListaTiposPersonaje(const YAML::Node& nodo, std::list <stTipoPersonaje>& tiposPersonaje);
	void cargaListaTexturas(const YAML::Node& nodo, std::list <stTextura>& texturas);
	void cargaStEscalera(const YAML::Node& nodo, stEscalera& escalera);
	void cargaStPersonaje(const YAML::Node& nodo, stPersonaje& personaje);
	void cargaStPlataforma(const YAML::Node& nodo, stPlataforma& plataforma);
	void cargaStNivel(const YAML::Node& nodo, stNivel& nivel);
	void cargaStJuego(const YAML::Node& nodo, stJuego& juego);

	void cargaJuegoDefault();
	void asignarJuegoDefault();
	bool chequeoArchivo(std::string ruta);
	bool existeTextura(std::string textura);
	bool existeTipoPersonaje(std::string tipoPersonaje);

	// Validación del juego
	void validacionDatos();
	void validaParametros(int anchoPjePpal);
	void validaTexturas();
	void validaPantalla();
	void validaTiposPersonajeConParametros();
	void validaNivelAnchoAlto();
	void validaNivelEscaleras();
	void validaNivelPersonajes();
	void validaNivelPlataformas();

	int leerYamlInt(const YAML::Node& nodo);
	std::string leerYamlString(const YAML::Node& nodo);

	stTipoPersonaje getStTipoPersonajeBak(string nombreTipoPersonaje);
	stPersonaje getStPersonajeBak(string nombrePersonaje);

	stJuego juego,bak;
	std::string fondo;

public:
	ParserYaml(void);
	~ParserYaml(void);
	ParserYaml::stJuego cargaJuego(void);
	static void imprimirValores(ParserYaml::stJuego& st);

}; // Fin clase ParserYaml

//	Prueba del parser YAML
//	ParserYaml pruebaYAML;
//	ParserYaml::stJuego st = pruebaYAML.cargaJuego(); // Este es el struct con todos los datos cargados
//	cout<<"Accedo a un dato del juego, por ej. \"nivel.personajes.back().tipo\": "<<st.nivel.personajes.back().tipo<<endl;

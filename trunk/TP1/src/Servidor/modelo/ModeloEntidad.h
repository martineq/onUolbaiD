#pragma once

#include <iostream>
#include <Windows.h>

#include "../../utils/Observador/Observable.h"
#include "../../utils/Hilos/Hilo.h"

typedef struct Posicion {
	int x;
	int y;

	Posicion() {
		this->x = 0;
		this->y = 0;
	}

	bool operator==(const Posicion &posicion) const {
		return ((this->x == posicion.x) && (this->y == posicion.y));
	}

	bool operator!=(const Posicion &posicion) const {
		return !(*this == posicion);
	}
} Posicion;

class ModeloEntidad : public Observable {
	private:
		class Movimiento : public Hilo {
			private:
				ModeloEntidad* _modeloEntidad;
				Posicion _posicionDestino;
				bool _ejecutando;

				void* run(void* parametro);

				Movimiento(const Movimiento &movimiento);

				Movimiento& operator=(const Movimiento &movimiento);

			public:
				Movimiento(ModeloEntidad* modeloEntidad, Posicion posicionDestino);

				virtual ~Movimiento();

				void detener();
		};

		static long _ultimoId;

		int _id;
		bool _esJugador;
		unsigned int _alto;
		unsigned int _ancho;
		unsigned int _velocidad;
		Posicion _posicionActual;
		Posicion _posicionSiguiente;
		Movimiento* _movimientoActual;

		ModeloEntidad(const ModeloEntidad &modeloEntidad);

		ModeloEntidad& operator=(const ModeloEntidad &modeloEntidad);

		//TODO: Borrar
		class VistaEntidad : public Observador {
			private:
				char _mapa[10][10];

			public:
				VistaEntidad() {
					unsigned int x = 0, y = 0;
					for (x = 0; x < 10; x++) {
						for (y = 0; y < 10; y++) {
							this->_mapa[x][y] = '-';
						}
					}
				}

				virtual ~VistaEntidad() {
				}

				void actualizar(Observable* s) {
					ModeloEntidad* modeloEntidad = (ModeloEntidad*)s;
					Posicion posicionActual = modeloEntidad->posicionActual();
					Posicion posicionSiguiente = modeloEntidad->posicionSiguiente();
					unsigned int x = 0, y = 0;

					this->_mapa[posicionActual.x][posicionActual.y] = '-';
					this->_mapa[posicionSiguiente.x][posicionSiguiente.y] = 'X';

					system("cls");
					for (y = 0; y < 10; y++) {
						for (x = 0; x < 10; x++) {
							std::cout << this->_mapa[x][y];
						}
						std::cout << std::endl;
					}
				}
		};

		//TODO: Borrar
		static void mover(ModeloEntidad* modeloEntidad, unsigned int x, unsigned int y) {
			Posicion posicionDestino;
			posicionDestino.x = x;
			posicionDestino.y = y;
			modeloEntidad->mover(posicionDestino);
		}

	public:
		//TODO: Borrar
		static void prueba() {
			Posicion posicionInicial;

			posicionInicial.x = 0;
			posicionInicial.y = 0;

			VistaEntidad vistaEntidad;
			ModeloEntidad modeloEntidad(1, 1, 200, posicionInicial, true);
			
			modeloEntidad.agregarObservador(&vistaEntidad);
			
			mover(&modeloEntidad, 9, 0);
			Sleep(1000);
			/*mover(&controladorEntidad, 0, 0);
			mover(&controladorEntidad, 0, 9);
			mover(&controladorEntidad, 0, 0);*/
			mover(&modeloEntidad, 9, 9);
			/*mover(&controladorEntidad, 0, 0);
			mover(&controladorEntidad, 4, 4);
			mover(&controladorEntidad, 9, 0);
			mover(&controladorEntidad, 0, 9);*/

			getchar();
		}

		ModeloEntidad(unsigned int alto, unsigned int ancho, unsigned int velocidad, Posicion posicion, bool esJugador);

		virtual ~ModeloEntidad();

		void cambiarEstado();

		int obtenerId() const;

		bool esJugador() const;

		unsigned int alto() const;

		unsigned int ancho() const;
		
		unsigned int velocidad() const;

		Posicion posicionActual() const;

		Posicion posicionSiguiente() const;

		void mover(Posicion posicion);

		bool operator==(const ModeloEntidad &modeloEntidad) const;
};

#pragma once

#include <iostream>
#include <Windows.h>

#include "../../utils/Observador/Observable.h"
#include "../../utils/Observador/Observador.h"

typedef struct {
	int x;
	int y;
} Posicion;

class ModeloEntidad : public Observable, public Observador {
	private:
		unsigned int _alto;
		unsigned int _ancho;
		unsigned int _velocidad;
		Posicion _posicionActual;
		Posicion _posicionSiguiente;

		//TODO: Borrar
		static void mover(ModeloEntidad* modeloEntidad, unsigned int x, unsigned int y) {
			Posicion posicionDestino;
			posicionDestino.x = x;
			posicionDestino.y = y;
			modeloEntidad->mover(posicionDestino);
		}

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

	public:
		//TODO: Borrar
		static void prueba() {
			Posicion posicionInicial;

			posicionInicial.x = 0;
			posicionInicial.y = 0;

			ModeloEntidad modeloEntidad(1, 1, 200, posicionInicial);
			VistaEntidad vistaEntidad;

			modeloEntidad.agregarObservador(&vistaEntidad);
	
			mover(&modeloEntidad, 9, 0);
			mover(&modeloEntidad, 0, 0);
			mover(&modeloEntidad, 0, 9);
			mover(&modeloEntidad, 0, 0);
			mover(&modeloEntidad, 9, 9);
			mover(&modeloEntidad, 0, 0);
			mover(&modeloEntidad, 4, 4);
			mover(&modeloEntidad, 9, 0);
			mover(&modeloEntidad, 0, 9);

			getchar();
		}

		ModeloEntidad(unsigned int alto, unsigned int ancho, unsigned int velocidad, Posicion posicion);

		virtual ~ModeloEntidad();

		unsigned int alto() const;

		unsigned int ancho() const;
		
		unsigned int velocidad() const;

		Posicion posicionActual() const;

		Posicion posicionSiguiente() const;

		void actualizar(Observable* s);

		void mover(Posicion posicionDestino);

		void cambiarEstado();

		bool operator==(const ModeloEntidad &modeloEntidad) const;
};

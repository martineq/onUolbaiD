#pragma once

#include <iostream>
#include <list>
#include <string>
#include <sstream>

#include "ESArchivoCpp.h"

class FinalF{

	private:

		struct stPosicion{
			int x;
			int y;

			bool operator==(const stPosicion& otro) const{
				return ( ((*this).x == otro.x) && ((*this).y == otro.y) );
			}

			stPosicion(){
				x=0;
				y=0;
			}
		};

		struct stObstaculo{
			stPosicion pos;
			int alto;
			int ancho;
		};

		struct stPersonaje{
			std::string id;
			stPosicion posIni;
			stPosicion posFin;
		};

		struct stNodo{
			stPosicion pos;
			int aDest;
			int aOrig;
			stNodo* padre;

			// Para usar el std::list::sort()
			bool operator<(const stNodo& otro) const {
				return( ( (*this).aOrig + (*this).aDest ) < ( otro.aOrig + otro.aDest ) );
			}

			// Para inicialar valores
			stNodo() {
				aDest = 0;
				aOrig = 0;
				padre = NULL;
			}

			void setPadre(stNodo* padre, int distancia){
				if (padre == NULL) {
					this->padre = NULL;
					this->aOrig = 0;
				}else if (( this->padre == NULL) || (this->aOrig > padre->aOrig + distancia)) {
					this->padre = padre;
					this->aOrig = this->padre->aOrig + distancia;
				}
			}
		};

		struct stDatos{
			int altoNivel;
			int anchoNivel;
			std::list<stObstaculo> obs;
			std::list<stPersonaje> pje;
			char* mapaTilesCerrados;
		};

		void leerArchivoObstaculos(stDatos &datos);
		void leerArchivoJugadores(stDatos &datos);
		void calcularCamino(stDatos& datos, std::list<stPosicion>& posiciones, stPosicion posIni, stPosicion posFin);
		bool agregarNodo(stDatos& datos, std::list<stNodo>& tilesAbiertos, stPosicion pos, stPosicion posDest, stNodo* padre, int distancia);

	public:
		FinalF(void);
		~FinalF(void);

		void resolver(void);
};

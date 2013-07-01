#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <list>


using namespace std;

typedef enum Direccion {V, H};

typedef struct {
	char id[100];
	float x;
	float y;
	float radio;
} tPozo;

typedef struct {
	char id[100];
	float x;
	float y;
	Direccion direccion;
} tTanque;

typedef struct {
	char id_pozo[100];
	char id_tanque[100];
	float distancia;
} tResultado;


bool colisionan(tTanque* tanque, tPozo* pozo) {
	if (tanque->direccion == H) {
		if (abs(tanque->y - pozo->y) <= pozo->radio)
			return true;
		else
			return false;
	} else {// tanque->direccion = V
		if (abs(tanque->x - pozo->x) <= pozo->radio)
			return true;
		else
			return false;
	}
}

float distancia(tTanque* tanque, tPozo* pozo) {
	if (tanque->direccion == H) {
		float dists_ys = abs(tanque->y - pozo->y);
		float circle_x = sqrt(pow(pozo->radio,2) - pow(dists_ys,2));

		return pozo->x - tanque->x - circle_x;
	} else { //tanque->direccion == V
		float dists_xs = abs(tanque->x - pozo->x);
		float circle_y = sqrt(pow(pozo->radio,2) - pow(dists_xs,2));

		return pozo->y - tanque->y - circle_y;
	}
}


bool sortPozoX(tPozo first, tPozo second) {
	if (first.x < second.x)
		return true;
	else
		return false;
}

bool sortPozoY(tPozo first, tPozo second) {
	if (first.y < second.y)
		return true;
	else
		return false;
}


void cargarPozos(list<tPozo>* pozos) {
	FILE *file = fopen(".//pozos.txt", "r");

	while (!feof(file)){
		tPozo pozo;
		fscanf(file, "%s %f %f %f ", &pozo.id, &pozo.x, &pozo.y, &pozo.radio);
		
		pozos->push_back(pozo);
	}

	fclose(file);
}

void cargarTanques(list<tTanque>* tanques){
	FILE* file = fopen(".//tanques.txt", "r");

	while (!feof(file)){
		tTanque tanque;
		char direccion;

		fscanf(file, "%s %f %f %c ", &tanque.id, &tanque.x, &tanque.y, &direccion);
		if (direccion == 'H')
			tanque.direccion = H;
		else // direccion == 'V'
			tanque.direccion = V;

		tanques->push_back(tanque);
	}

	fclose(file);
}

void procesar(list<tPozo>* pozos, list<tTanque>* tanques, list<tResultado>* resultados) {
	for (list<tTanque>::iterator it_tanque = tanques->begin(); it_tanque != tanques->end(); it_tanque++){

		//Si la direccion del tanque es horizontal ordeno los pozos por X y viceversa y de ahi sigo
		if ((*it_tanque).direccion == H){
			pozos->sort(sortPozoX);
			
			bool hundido = false;
			list<tPozo>::iterator it_pozo = pozos->begin();

			while ((!hundido) && (it_pozo != pozos->end())){
				if (!((*it_pozo).x + (*it_pozo).radio < (*it_tanque).x)){
					if(colisionan(&(*it_tanque), &(*it_pozo))){
						tResultado res;
						
						strcpy(res.id_tanque, (*it_tanque).id);
						strcpy(res.id_pozo, (*it_pozo).id);
						res.distancia = distancia(&(*it_tanque), &(*it_pozo));

						resultados->push_back(res);

						hundido = true;
					}
				}
				it_pozo++;
			}

		} else { // (*it_tanque).direccion == V
			pozos->sort(sortPozoY);
			
			bool hundido = false;
			list<tPozo>::iterator it_pozo = pozos->begin();

			while ((!hundido) && (it_pozo != pozos->end())){
				if (!((*it_pozo).y + (*it_pozo).radio < (*it_tanque).y)){
					if(colisionan(&(*it_tanque), &(*it_pozo))){
						tResultado res;
						
						strcpy(res.id_tanque, (*it_tanque).id);
						strcpy(res.id_pozo, (*it_pozo).id);
						res.distancia = distancia(&(*it_tanque), &(*it_pozo));

						resultados->push_back(res);

						hundido = true;
					}
				}
				it_pozo++;
			}
		}

	}

}


bool sortResultados(tResultado first, tResultado second){
	if (first.distancia < second.distancia)
		return true;
	else
		return false;
}

//----------
int main() {
	list<tPozo> pozos;
	list<tTanque> tanques;
	list<tResultado> resultados;

	cargarPozos(&pozos);
	cargarTanques(&tanques);

	procesar(&pozos, &tanques, &resultados);
	resultados.sort(sortResultados);

	for (list<tResultado>::iterator it = resultados.begin(); it != resultados.end(); it++)
		printf("%s\t%s\t%f\n", (*it).id_tanque, (*it).id_pozo, (*it).distancia);


	getchar();
	return 0;
}
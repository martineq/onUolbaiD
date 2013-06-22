#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <algorithm>

typedef struct {
	//std::string nombre;
	char nombre[100];
	int x_start;
	int x_end;
	int y_start;
	int y_end;
} tEscenario;

typedef struct {
	int x;
	int y;
} tAcontecimientos;

typedef struct {
	char nombre[100];
	int puntos;
} tResultado;


int cargarEscenario(std::list<tEscenario> *escenario) {
	FILE *file;
	file = fopen(".\\Escenario.txt","r");
	
	if (!file)
		return -1;

	char linea[100];

	while(!feof(file)) {
		fgets(linea,100,file);
		tEscenario elemento;
		strcpy(elemento.nombre, strtok(linea,";"));
		elemento.x_start = atoi(strtok(NULL,";"));
		elemento.x_end = atoi(strtok(NULL,";"));
		elemento.y_start = atoi(strtok(NULL,";"));
		elemento.y_end = atoi(strtok(NULL,";"));

		escenario->push_back(elemento);
	}

	fclose(file);

	return 0;
}

void inicializarResultados(std::list<tResultado> *resultados, std::list<tEscenario> escenario) {
	for (std::list<tEscenario>::iterator it = escenario.begin(); it != escenario.end(); it++) {
		tResultado res;
		strcpy(res.nombre,(*it).nombre);
		res.puntos = 0;
		resultados->push_back(res);
	}
}

bool inBox(tEscenario escenario, int x, int y) {
	if ((escenario.x_end >= x) && (escenario.x_start <= x) && (escenario.y_end >= y) && (escenario.y_start <= y))
		return true;
	else
		return false;
}

bool isThePlayer(tResultado res, char name[100]) {
	if (!strcmp(res.nombre,name))
		return true;
	else
		return false;
}

int actualizarResultados (std::list<tResultado> *resultados, tEscenario escenario) {
	std::list<tResultado>::iterator it = resultados->begin();
	bool found = false;

	while ((it != resultados->end()) && (!found)) {
		if (!strcmp((*it).nombre,escenario.nombre)) {
			(*it).puntos++;
			found = true;
		}
		it++;
	}

	return 0;
}

int procesarAcontecimientos(std::list<tEscenario> *escenario, std::list<tResultado> *resultados) {

	FILE *file = fopen(".\\Acontecimientos.txt","r");

	if (!file)
		return -1;

	char dato[100];
	int x;
	int y;
	while (!feof(file)) {
		fgets(dato,100,file);
		x = atoi(strtok(dato,";"));
		y = atoi(strtok(NULL,";"));

		for (std::list<tEscenario>::iterator it = escenario->begin(); it != escenario->end(); it++) {
			if (inBox((*it),x,y) == true)
				actualizarResultados(resultados, (*it));
		}

	}

	fclose(file);

	return 0;
	

}

bool compResultados(tResultado first, tResultado second) {
	if (first.puntos > second.puntos)
		return true;
	else
		return false;
}

//void mostrarResultados(std::list<tResultado> *resultados) {
//	
//	resultados->sort(compResultados);
//	for (std::list<tResultado>::iterator it = resultados->begin(); it != resultados->end(); it++) {
//		printf("%s = %d\n",(*it).nombre, (*it).puntos);
//	}
//}


int main() {
	std::list<tEscenario> escenario;
	//std::list<tAcontecimientos> acontecimientos;
	std::list<tResultado> resultados;

	cargarEscenario(&escenario);
	inicializarResultados(&resultados, escenario);
	procesarAcontecimientos(&escenario, &resultados);

	resultados.sort(compResultados);
	for (std::list<tResultado>::iterator it = resultados.begin(); it != resultados.end(); it++) {
		printf("%s = %d\n",(*it).nombre, (*it).puntos);
	}
	getchar();
	return 0;
}
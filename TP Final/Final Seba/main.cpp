#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <math.h>

using namespace std;

typedef struct {
	int x;
	int y;
	float ataque;
	int alcance;
} tEnemigo;


typedef struct {
	char id[100];
	int x;
	int y;
	float energia;
	float escudo;

	int ciclos;
	int celdas;

	bool vivo;
	bool gano;
	bool stuck;
} tPersonaje;


typedef struct {
	char id[100];
	int ciclos;
	int celdas;
} tResultado;


bool ordenarRes(tResultado first, tResultado second){
	return (first.celdas < second.celdas);
}


//---------
void cargarEnemigos(list<tEnemigo> *enemigos){
	FILE *file = fopen(".//enemigos.txt","r");


	while (!feof(file)){
		tEnemigo enem;
		fscanf(file, "%d %d %f %d ",  &enem.x, &enem.y, &enem.ataque, &enem.alcance);

		printf("%d %d %f %d\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", enem.x, enem.y, enem.ataque, enem.alcance);
		
		enemigos->push_back(enem);
	

	}

	fclose(file);


}

void cargarPersonajes(list<tPersonaje> *personajes){
	FILE *file = fopen(".//personajes.txt", "r");
	if (!file)
		printf("a");

	while (!feof(file)){
		tPersonaje pers;

		fscanf(file, "%s %d %d %f %f ", pers.id, &pers.x, &pers.y, &pers.energia, &pers.escudo);
		pers.ciclos = 0;
		pers.celdas = 0;
		pers.vivo = true;
		pers.gano = false;
		pers.stuck = false;
		
		printf("%s %d %d %f %f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", pers.id, pers.x, pers.y, pers.energia, pers.escudo);
		personajes->push_back(pers);

	}

	fclose(file);
}

bool personajesEnJuego(list<tPersonaje> *personajes){
	for (list<tPersonaje>::iterator it = personajes->begin(); it != personajes->end(); it++)
		if ((*it).vivo == true && (*it).gano == false && (*it).stuck == false)
			return true;

	return false;
}


void actualizarCiclos(list<tPersonaje> *personajes){
	for(list<tPersonaje>::iterator it = personajes->begin(); it != personajes->end(); it++)
		if ((*it).vivo == true && (*it).gano == false && (*it).stuck == false)
			(*it).ciclos++;
}

bool enRango(tEnemigo enemigo, tPersonaje personaje){
	if (personaje.x == enemigo.x){
		if (abs(personaje.y - enemigo.y) <= enemigo.alcance) {
			return true;
		}
	} else if (abs(personaje.x - enemigo.x) <= enemigo.alcance) {
		if (abs(personaje.y - enemigo.y) <= enemigo.alcance) {
			return true;
		}
	}

	return false;
}

void atacar(list<tEnemigo> *enemigos, list<tPersonaje> *personajes){
	for (list<tEnemigo>::iterator it_ene = enemigos->begin(); it_ene != enemigos->end(); it_ene++){
		for (list<tPersonaje>::iterator it_pers = personajes->begin(); it_pers != personajes->end(); it_pers++) {
			if ((*it_pers).vivo == true && (*it_pers).gano == false && (*it_pers).stuck == false){
				if (enRango((*it_ene), (*it_pers)) == true){
					if ((*it_ene).ataque > (*it_pers).escudo){
						float aux = (*it_ene).ataque - (*it_pers).escudo;

						(*it_pers).energia -= aux;

						if ((*it_pers).energia <= 0)
							(*it_pers).vivo = false;
					}
				}
			}
		}
	}
}

bool persStuck(tPersonaje *personaje, list<tEnemigo> *enemigos){
	bool rta = false;
	
	for (list<tEnemigo>::iterator it_ene = enemigos->begin(); it_ene != enemigos->end(); it_ene++){
		if (personaje->y == (*it_ene).y && personaje->x+1 == (*it_ene).x){
			rta = true;
			if (personaje->escudo >= (*it_ene).ataque){
				personaje->stuck = true;
			}
		}
	}

	return rta;
}


void avanzar(list<tEnemigo> *enemigos, list<tPersonaje> *personajes){
	for (list<tPersonaje>::iterator it_pers = personajes->begin(); it_pers != personajes->end(); it_pers++){
		if ((*it_pers).vivo == true && (*it_pers).gano == false && (*it_pers).stuck ==  false){
			if (persStuck(&(*it_pers),enemigos) == false){
				(*it_pers).celdas++;
				(*it_pers).x++;
				if ((*it_pers).x > 100)
					(*it_pers).gano = true;
			}

		}

	}
}

void obtenerResultados(list<tPersonaje> *personajes, list<tResultado> *resultados){
	for (list<tPersonaje>::iterator it = personajes->begin(); it != personajes->end(); it++){
		if ((*it).vivo == false){
			tResultado res;
			strcpy(res.id, (*it).id);
			res.celdas = (*it).celdas;
			res.ciclos = (*it).ciclos;

			resultados->push_back(res);
		}
	}
}


//--------

int main(){
	
	list<tEnemigo> enemigos;
	list<tPersonaje> personajes;
	list<tResultado> resultados;

	cargarEnemigos(&enemigos);
	cargarPersonajes(&personajes);

	
	int ciclo=0;
	while (personajesEnJuego(&personajes) == true){
		ciclo++;

		actualizarCiclos(&personajes);
		atacar(&enemigos, &personajes);
		avanzar(&enemigos, &personajes);
	}


	//printf("%d\n", enemigos.size());
	//printf("%d\n", personajes.size());

	obtenerResultados(&personajes, &resultados);
	resultados.sort(ordenarRes);

	printf("RESULTADOS\n");
	for (list<tResultado>::iterator it = resultados.begin(); it != resultados.end(); it++){
		printf("ID: %s Ciclos: %d Celdas %d\n", (*it).id, (*it).ciclos, (*it).celdas);
	}

	getchar();
	return 0;

}
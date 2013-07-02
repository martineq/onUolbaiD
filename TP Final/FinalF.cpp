#include "FinalF.h"

FinalF::FinalF(void){

}

FinalF::~FinalF(void){

}

void FinalF::resolver(void){

	stDatos datos;

	// Leo el archivo de Obstaculos
	this->leerArchivoObstaculos(datos);

	// Leo el archivo de Jugadores
	this->leerArchivoJugadores(datos);

	// Asigno el tamaño del nivel
	datos.altoNivel = 4;
	datos.anchoNivel = 4;

	// Calculo el camino mínimo para cada jugador
	for( std::list<stPersonaje>::iterator it = datos.pje.begin() ; it!=datos.pje.end() ; it++ ){
		std::list<stPosicion> posiciones; // Acá recolecto las posiciones del camino mínimo
		this->calcularCamino(datos,posiciones,(*it).posIni,(*it).posFin);
		std::cout << "El camino para el pesonaje " << (*it).id << " es:\n";
		for( std::list<stPosicion>::iterator it2 = posiciones.begin() ; it2!=posiciones.end() ; it2++ ){
			std::cout << "(" << (*it2).x << "," << (*it2).y << ") ";
		}
		std::cout << "\n";
	}

	return void();
}

void FinalF::leerArchivoObstaculos(stDatos &datos){
	ESArchivoCpp entrada("./archivos/FinalF_Entrada_Obstaculos.txt",true,true);
	std::string linea;
	while( entrada.leerLinea(linea) ){
		std::stringstream ssl(linea);
		std::string valor;
		int indice = 1;
		stObstaculo ob;
		while( std::getline(ssl,valor,',') ){
			std::stringstream ssv(valor);
			if( indice == 1 ) ssv >> ob.pos.x;
			if( indice == 2 ) ssv >> ob.pos.y;
			if( indice == 3 ) ssv >> ob.alto;
			if( indice == 4 ) ssv >> ob.ancho;
			indice++;
		}
		datos.obs.push_back(ob);
	}
	return void();
}

void FinalF::leerArchivoJugadores(stDatos &datos){
	ESArchivoCpp entrada("./archivos/FinalF_Entrada_Personajes.txt",true,true);
	std::string linea;
	while( entrada.leerLinea(linea) ){
		std::stringstream ssl(linea);
		std::string valor;
		int indice = 1;
		stPersonaje pj;
		while( std::getline(ssl,valor,',') ){
			std::stringstream ssv(valor);
			if( indice == 1 ) ssv >> pj.id.assign(ssv.str());
			if( indice == 2 ) ssv >> pj.posIni.x;
			if( indice == 3 ) ssv >> pj.posIni.y;
			if( indice == 4 ) ssv >> pj.posFin.x;
			if( indice == 5 ) ssv >> pj.posFin.y;
			indice++;
		}
		datos.pje.push_back(pj);
	}
	return void();
}

// Calcula el camino mínimo en un mapa toamndo en cuenta solo los obstaculos (a los otros jugadres los pasa por arriba)
// Supone:
// + Movimientos válidos (dentro del mapa)
// + El origen y el destino son distintos
// + El destino no está ocupado
// + Todos los obstáculos miden 1x1 (No se toma la medida del alto y ancho por ahora)
void FinalF::calcularCamino(stDatos& datos, std::list<stPosicion>& posiciones, stPosicion posIni, stPosicion posFin){

	datos.mapaTilesCerrados = new char[datos.altoNivel * datos.anchoNivel * sizeof(char)];
	for(unsigned long i=0 ; i<(datos.altoNivel * datos.anchoNivel * sizeof(char)) ; i++) datos.mapaTilesCerrados[i]=0;

	std::list<stNodo> tilesAbiertos;
	std::list<stNodo> tilesCerrados;
	stNodo* tileActual = NULL;
 
	this->agregarNodo(datos,tilesAbiertos,posIni,posFin,NULL,0);

	while (!tilesAbiertos.empty()) {

		// Paso el primer nodo abierto a la lista de cerrados
		tilesCerrados.push_back(tilesAbiertos.front());
		tilesAbiertos.pop_front();
		tileActual = &tilesCerrados.back();
		datos.mapaTilesCerrados[ (datos.anchoNivel * tileActual->pos.y) + tileActual->pos.x] = 1;

		// Si llegue a la posicion destino reconstruyo el camino
		if ( tileActual->pos == posFin ) {
			while (tileActual != NULL) {
				posiciones.push_front(tileActual->pos);
				tileActual = tileActual->padre;
			}

			delete[] datos.mapaTilesCerrados;
			return void();
		}

		stPosicion posicionAdyacente;
		bool posicionProcesada = false;

		// Posicion superior izquierda
		posicionAdyacente = tileActual->pos;
		posicionAdyacente.x -= 1;
		posicionAdyacente.y -= 1;
		posicionProcesada |= this->agregarNodo(datos, tilesAbiertos, posicionAdyacente, posFin, tileActual, 14);

		// Posicion superior
		posicionAdyacente = tileActual->pos;
		posicionAdyacente.y -= 1;
		posicionProcesada |= posicionProcesada |= this->agregarNodo(datos, tilesAbiertos, posicionAdyacente, posFin, tileActual, 10);

		// Posicion superior derecha
		posicionAdyacente = tileActual->pos;
		posicionAdyacente.x += 1;
		posicionAdyacente.y -= 1;
		posicionProcesada |= this->agregarNodo(datos, tilesAbiertos, posicionAdyacente, posFin, tileActual, 14);

		// Posicion izquierda
		posicionAdyacente = tileActual->pos;
		posicionAdyacente.x -= 1;
		posicionProcesada |= posicionProcesada |= this->agregarNodo(datos, tilesAbiertos, posicionAdyacente, posFin, tileActual, 10);

		// Posicion derecha
		posicionAdyacente = tileActual->pos;
		posicionAdyacente.x += 1;
		posicionProcesada |= posicionProcesada |= this->agregarNodo(datos, tilesAbiertos, posicionAdyacente, posFin, tileActual, 10);

		// Posicion inferior izquierda
		posicionAdyacente = tileActual->pos;
		posicionAdyacente.x -= 1;
		posicionAdyacente.y += 1;
		posicionProcesada |= this->agregarNodo(datos, tilesAbiertos, posicionAdyacente, posFin, tileActual, 14);

		// Posicion inferior
		posicionAdyacente = tileActual->pos;
		posicionAdyacente.y += 1;
		posicionProcesada |= posicionProcesada |= this->agregarNodo(datos, tilesAbiertos, posicionAdyacente, posFin, tileActual, 10);

		// Posicion inferior derecha
		posicionAdyacente = tileActual->pos;
		posicionAdyacente.x += 1;
		posicionAdyacente.y += 1;
		posicionProcesada |= this->agregarNodo(datos, tilesAbiertos, posicionAdyacente, posFin, tileActual, 14);

		// Ordeno la lista si se prceso alguna posicion
		if (posicionProcesada) tilesAbiertos.sort();
	}

	delete[] datos.mapaTilesCerrados;
}

bool FinalF::agregarNodo(stDatos& datos, std::list<stNodo>& tilesAbiertos, stPosicion pos, stPosicion posDest, stNodo* padre, int distancia){

	stNodo nodo;
	nodo.pos = pos;
	double dX = (double)nodo.pos.x - (double)posDest.x;
	double dY = (double)nodo.pos.y - (double)posDest.y;
	nodo.aDest = dX*dX + dY*dY;
	nodo.setPadre(padre,distancia);

	// Si la posicion esta fuera del nivel no la proceso
	if ((pos.x < 0) || (pos.x >= datos.anchoNivel) || (pos.y < 0) || (pos.y >= datos.altoNivel)) return false;
	
	// Si ya cerre el nodo salgo
	if (datos.mapaTilesCerrados[(datos.anchoNivel * pos.y) + pos.x] == 1) return false;

	// Si la posicion esta ocupada por un obstáculo no la agrego y salgo
	for( std::list<stObstaculo>::iterator it = datos.obs.begin() ; it != datos.obs.end() ; it++){
		if( (*it).pos == pos ) return false;
	}

	// Si encuentro el nodo en los abiertos le cambio el padre
	for (std::list<FinalF::stNodo>::iterator nodo = tilesAbiertos.begin(); nodo != tilesAbiertos.end(); nodo++){
		if ((*nodo).pos == pos){
			(*nodo).setPadre(padre, distancia);
			return true;
		}
	}

	// Si el nodo no esta en ninguna de las dos listas lo agrego y lo marco como visitado
	tilesAbiertos.push_back(nodo);

	return true;
}
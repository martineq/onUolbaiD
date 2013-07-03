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

	// Creo e inicialo el mapa de nodos cerrados
	datos.mapaNodosCerrados = new char[datos.altoNivel * datos.anchoNivel * sizeof(char)];
	for(unsigned long i=0 ; i<(datos.altoNivel * datos.anchoNivel * sizeof(char)) ; i++) datos.mapaNodosCerrados[i]=0;

	// Creo una lista de nodos abiertos, otra de nodos cerrados y un puntero al nodo actual
	std::list<stNodo> nodosAbiertos;
	std::list<stNodo> nodosCerrados;
	stNodo* nodoActual = NULL;
 
	// Agrego el primer nodo a los abiertos
	this->agregarNodo(datos,nodosAbiertos,posIni,posFin,NULL,0);

	// Itero mientras haya nodos abiertos
	while (!nodosAbiertos.empty()) {

		// Paso el primer nodo abierto a la lista de cerrados y lo saco de la de nodos abiertos
		nodosCerrados.push_back(nodosAbiertos.front());
		nodosAbiertos.pop_front();

		// Preparo el nodo actual y lo marco como cerrado
		nodoActual = &nodosCerrados.back();
		datos.mapaNodosCerrados[ (datos.anchoNivel * nodoActual->pos.y) + nodoActual->pos.x] = 1;

		// Si llegue a la posicion destino reconstruyo el camino
		if ( nodoActual->pos == posFin ) {
			while (nodoActual != NULL) {
				posiciones.push_front(nodoActual->pos);
				nodoActual = nodoActual->padre;
			}
			delete[] datos.mapaNodosCerrados;
			return void();
		}

		// Calculo la posicion superior izquierda
		stPosicion posicionAdyacente = nodoActual->pos;
		posicionAdyacente.x -= 1;
		posicionAdyacente.y -= 1;
		this->agregarNodo(datos, nodosAbiertos, posicionAdyacente, posFin, nodoActual, 14);

		// Calculo la posicion superior
		posicionAdyacente = nodoActual->pos;
		posicionAdyacente.y -= 1;
		this->agregarNodo(datos, nodosAbiertos, posicionAdyacente, posFin, nodoActual, 10);

		// Calculo la posicion superior derecha
		posicionAdyacente = nodoActual->pos;
		posicionAdyacente.x += 1;
		posicionAdyacente.y -= 1;
		this->agregarNodo(datos, nodosAbiertos, posicionAdyacente, posFin, nodoActual, 14);

		// Calculo la posicion izquierda
		posicionAdyacente = nodoActual->pos;
		posicionAdyacente.x -= 1;
		this->agregarNodo(datos, nodosAbiertos, posicionAdyacente, posFin, nodoActual, 10);

		// Calculo la posicion derecha
		posicionAdyacente = nodoActual->pos;
		posicionAdyacente.x += 1;
		this->agregarNodo(datos, nodosAbiertos, posicionAdyacente, posFin, nodoActual, 10);

		// Calculo la posicion inferior izquierda
		posicionAdyacente = nodoActual->pos;
		posicionAdyacente.x -= 1;
		posicionAdyacente.y += 1;
		this->agregarNodo(datos, nodosAbiertos, posicionAdyacente, posFin, nodoActual, 14);

		// Calculo la posicion inferior
		posicionAdyacente = nodoActual->pos;
		posicionAdyacente.y += 1;
		this->agregarNodo(datos, nodosAbiertos, posicionAdyacente, posFin, nodoActual, 10);

		// Calculo la posicion inferior derecha
		posicionAdyacente = nodoActual->pos;
		posicionAdyacente.x += 1;
		posicionAdyacente.y += 1;
		this->agregarNodo(datos, nodosAbiertos, posicionAdyacente, posFin, nodoActual, 14);

	}

	delete[] datos.mapaNodosCerrados;
}

bool FinalF::agregarNodo(stDatos& datos, std::list<stNodo>& nodosAbiertos, stPosicion pos, stPosicion posDest, stNodo* padre, int distancia){

	// Creo el nodo
	stNodo nodo;
	
	// Cargo su posición
	nodo.pos = pos;

	// Cargo la distancia al destino
	double dX = (double)nodo.pos.x - (double)posDest.x;
	double dY = (double)nodo.pos.y - (double)posDest.y;
	nodo.aDest = dX*dX + dY*dY;

	// Cargo el padre y la distancia hacia el origen, haciendo uso de la distancia hacia el pader
	nodo.setPadre(padre,distancia);

	// Si la posicion esta fuera del nivel no la proceso
	if ((pos.x < 0) || (pos.x >= datos.anchoNivel) || (pos.y < 0) || (pos.y >= datos.altoNivel)) return false;

	// Si ya cerre el nodo salgo
	if (datos.mapaNodosCerrados[(datos.anchoNivel * pos.y) + pos.x] == 1) return false;

	// Si la posicion esta ocupada por un obstáculo no la agrego y salgo
	for( std::list<stObstaculo>::iterator it = datos.obs.begin() ; it != datos.obs.end() ; it++){
		if( (*it).pos == pos ) return false;
	}

	// Si encuentro el nodo en los abiertos me fijo si corresponde el cambio el padre por tener menor distancia al origen
	for (std::list<FinalF::stNodo>::iterator nodo = nodosAbiertos.begin(); nodo != nodosAbiertos.end(); nodo++){
		if ((*nodo).pos == pos){
			(*nodo).setPadre(padre, distancia);
			return true;
		}
	}

	// Si el nodo no esta en ninguna de las dos listas lo agrego y lo marco como visitado
	nodosAbiertos.push_back(nodo);

	// Ordeno la lista porque se prceso una posicion
	nodosAbiertos.sort();

	return true;
}

void FinalF::pruebaConversionTilePixel(void){

	// Dimensiones de un tile
	int anchoTile = 10;
	int altoTile = 10;

	// Dimensiones del mapa expresado en tiles
	int altoEnTiles = 2;
	int anchoEnTiles = 2;

	for( int i = 0 ; i < altoEnTiles ; i++ ){
	
		for( int j = 0 ; j < altoEnTiles ; j++ ){

			int pX,pY;
			this->convertirTileAPixel(altoEnTiles,i,j,pX,pY,anchoTile,altoTile);
			std::cout << "(" << i << "," << j << ") " << "(" << pX << "," << pY << ")" << std::endl;

		}

	}


	return void();
}

void FinalF::convertirTileAPixel(int altoEnTiles, int xTile, int yTile, int& xPixel, int& yPixel, int anchoTile, int altoTile) {
	xPixel = (anchoTile / 2) * (xTile - yTile) + (anchoTile / 2) * altoEnTiles;
	yPixel = (altoTile / 2) * (xTile + yTile);
}

void FinalF::convertirPixelATile(int altoEnTiles, int xPixel, int yPixel, int& xTile, int& yTile, int anchoTile, int altoTile) {
	double desplazamientoX = 0, desplazamientoY = 0;
	
	xPixel -= (anchoTile / 2) * altoEnTiles;
	desplazamientoX = (double)xPixel / anchoTile;
	desplazamientoY = (double)yPixel / altoTile;
	
	xTile = floor(desplazamientoY + desplazamientoX);
	yTile = floor(desplazamientoY - desplazamientoX);
} 

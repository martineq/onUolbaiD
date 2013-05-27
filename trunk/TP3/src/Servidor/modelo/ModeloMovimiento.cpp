#include "ModeloEntidad.h"

#define DURACION_CALCULO_CAMINO_MINIMO 1000

using namespace std;

bool ModeloEntidad::ModeloMovimiento::agregarTile(char* mapaTilesCerrados, list<Tile>* tilesAbiertos, Posicion posicion, Posicion posicionDestino, Tile* padre, int distancia) {
	Tile tile;
	tile.padre(padre, distancia);
	tile.posicion(posicion);
	tile.posicionDestino(posicionDestino);
	
	// Si la posicion esta fuera del nivel no la proceso
	if ((posicion.x < 0) || (posicion.x >= this->_anchoNivel) || (posicion.y < 0) || (posicion.y >= this->_anchoNivel))
		return false;
	
	// Si ya cerre el tile salgo
	if (mapaTilesCerrados[(this->_anchoNivel * posicion.y) + posicion.x] == 1)
		return false;

	// Si la posicion esta ocupada no la agrego
	if (this->detectarColision(posicion) != NULL)
		return false;

	// Si encuentro el tile en los abiertos le cambio el padre
	for (list<Tile>::iterator tile = tilesAbiertos->begin(); tile != tilesAbiertos->end(); tile++) {
		if ((*tile).posicion() == posicion) {
			(*tile).padre(padre, distancia);
			return true;
		}
	}

	// Si el tile no esta en ninguna de las dos listas lo agrego y lo marco como visitado
	tilesAbiertos->push_back(tile);

	return true;
}

Posicion ModeloEntidad::ModeloMovimiento::calcularPosicionDestino(Posicion posicionDestino) {
	// Obtengo la entidad en la posicion destino
	ModeloEntidad* modeloEntidad = this->detectarColision(posicionDestino);

	// Si no choca con nada devuelvo la misma posicion
	if (modeloEntidad == NULL)
		return posicionDestino;

	// Obtengo la posicion y dimension de todas las entidades adyacentes
	int x = this->obtenerX(modeloEntidad);
	int y = this->obtenerY(modeloEntidad);
	int alto = this->obtenerAlto(y, modeloEntidad);
	int ancho = this->obtenerAncho(x, modeloEntidad);
	
	// Choco con cara norte
	if (this->_modeloEntidad->posicionActual().y < y)
		posicionDestino.y = y - 1;
	// Choco con cara sur
	else if (this->_modeloEntidad->posicionActual().y >= y + alto)
		posicionDestino.y = y + alto;
	
	// Choco con cara este
	if (this->_modeloEntidad->posicionActual().x >= x + ancho)
		posicionDestino.x = x + ancho;
	// Choco con cara oeste
	else if (this->_modeloEntidad->posicionActual().x < x)
		posicionDestino.x = x - 1;

	return posicionDestino;
}

ModeloEntidad* ModeloEntidad::ModeloMovimiento::detectarColision(Posicion posicion) {
	this->_mutexEntidadesMoviles->lockLectura(__FILE__, __LINE__);
	list<ModeloEntidad*>* listaJugadores = this->_entidadesMoviles;
	this->_mutexEntidadesMoviles->unlock(__FILE__, __LINE__);

	// Detecto colision con jugadores
	if (listaJugadores != NULL) {
		list<ModeloEntidad*>::iterator iterador = listaJugadores->begin();

		while (iterador != listaJugadores->end()) {
			if (((*iterador) != this->_modeloEntidad) && (*iterador)->ocupaPosicion(posicion))
				return *iterador;
			iterador++;
		}
	}

	this->_mutexEntidades->lockLectura(__FILE__, __LINE__);
	multimap<std::pair<int, int>, ModeloEntidad*>::iterator entidad = this->_entidades->find(make_pair(posicion.x, posicion.y));
	multimap<std::pair<int, int>, ModeloEntidad*>::iterator fin = this->_entidades->end();
	this->_mutexEntidades->unlock(__FILE__, __LINE__);
	
	return (entidad == fin) ? NULL : (*entidad).second;
}

int ModeloEntidad::ModeloMovimiento::obtenerAlto(int y, ModeloEntidad* modeloEntidad) {
	int alto = modeloEntidad->posicionActual().y - y;
	while (modeloEntidad != NULL) {
		alto += modeloEntidad->alto();
		Posicion posicion = modeloEntidad->posicionActual();
		posicion.y += modeloEntidad->alto();
		modeloEntidad = this->detectarColision(posicion);
	}
	return alto;
}

int ModeloEntidad::ModeloMovimiento::obtenerAncho(int x, ModeloEntidad* modeloEntidad) {
	int ancho = modeloEntidad->posicionActual().x - x;
	while (modeloEntidad != NULL) {
		ancho += modeloEntidad->alto();
		Posicion posicion = modeloEntidad->posicionActual();
		posicion.x += modeloEntidad->ancho();
		modeloEntidad = this->detectarColision(posicion);
	}
	return ancho;
}

Posicion ModeloEntidad::ModeloMovimiento::obtenerPosicionSiguiente() {
	Posicion posicionSiguiente = this->_posiciones.front();
	this->_posiciones.pop_front();
	return posicionSiguiente;
}

int ModeloEntidad::ModeloMovimiento::obtenerX(ModeloEntidad* modeloEntidad) {
	int x = 0;
	while (modeloEntidad != NULL) {
		Posicion posicion = modeloEntidad->posicionActual();
		x = posicion.x--;
		modeloEntidad = this->detectarColision(posicion);
	}
	return x;
}

int ModeloEntidad::ModeloMovimiento::obtenerY(ModeloEntidad* modeloEntidad) {
	int y = 0;
	while (modeloEntidad != NULL) {
		Posicion posicion = modeloEntidad->posicionActual();
		y = posicion.y--;
		modeloEntidad = this->detectarColision(posicion);
	}
	return y;
}

ModeloEntidad::ModeloMovimiento::ModeloMovimiento(const ModeloMovimiento &modeloMovimiento) {
}

ModeloEntidad::ModeloMovimiento& ModeloEntidad::ModeloMovimiento::operator=(const ModeloMovimiento &modeloMovimiento) {
	return *this;
}

ModeloEntidad::ModeloMovimiento::ModeloMovimiento(int altoNivel, int anchoNivel, ModeloEntidad* modeloEntidad) {
	this->_altoNivel = altoNivel;
	this->_anchoNivel = anchoNivel;
	this->_modeloEntidad = modeloEntidad;
	this->_entidadesMoviles = NULL;
	this->_entidades = NULL;
	this->_instanteUltimoCambioEstado = 0;
}

ModeloEntidad::ModeloMovimiento::~ModeloMovimiento() {
}

void ModeloEntidad::ModeloMovimiento::actualizar(Posicion posicionDestino) {
	// Dentego el movimiento anterior
	this->detener();

	// Ajusta los movimientos para esten dentro del mapa
	if (posicionDestino.x < 0)
		posicionDestino.x = 0;
	else if (posicionDestino.x >= this->_anchoNivel)
		posicionDestino.x = this->_anchoNivel - 1;
	if (posicionDestino.y < 0)
		posicionDestino.y = 0;
	else if (posicionDestino.y >= this->_altoNivel)
		posicionDestino.y = this->_altoNivel - 1;

	// Si la posicion actual es igual a la destino no ejectuo el movimiento
	if (this->_modeloEntidad->posicionActual() == posicionDestino)
		return;

	// Calculo la posicion destino por si seleccione una posicion ocupada
	posicionDestino = this->calcularPosicionDestino(posicionDestino);

	char* mapaTilesCerrados = new char[this->_altoNivel * this->_anchoNivel * sizeof(char)];
	list<Tile> tilesAbiertos;
	list<Tile> tilesCerrados;
	Tile* tileActual = NULL;

	memset(mapaTilesCerrados, 0, this->_altoNivel * this->_anchoNivel * sizeof(char));

	this->agregarTile(mapaTilesCerrados, &tilesAbiertos, this->_modeloEntidad->posicionActual(), posicionDestino, NULL, 0);
	
	DWORD inicio = GetTickCount();

	while (!tilesAbiertos.empty()) {
		// Paso el primer tile abierto a la lista de cerrados
		tilesCerrados.push_back(tilesAbiertos.front());
		tilesAbiertos.pop_front();
		tileActual = &tilesCerrados.back();
		mapaTilesCerrados[(this->_anchoNivel * tileActual->posicion().y) + tileActual->posicion().x] = 1;

		// Si llegue a la posicion destino reconstruyo el camino
		if (tileActual->posicion() == posicionDestino) {
			while (tileActual != NULL) {
				this->_posiciones.push_front(tileActual->posicion());
				tileActual = tileActual->padre();
			}

			// Elimino la primera posicion porque ya estoy en ella
			this->_posiciones.pop_front();

			delete[] mapaTilesCerrados;
			return;
		}

		// Si ya paso el tiempo para calcular el camino minimo salgo
		if ((GetTickCount() - inicio) >= DURACION_CALCULO_CAMINO_MINIMO) {
			delete[] mapaTilesCerrados;
			return;
		}

		Posicion posicionAdyacente;
		bool posicionProcesada = false;

		// Posicion superior izquierda
		posicionAdyacente = tileActual->posicion();
		posicionAdyacente.x -= 1;
		posicionAdyacente.y -= 1;
		posicionProcesada |= this->agregarTile(mapaTilesCerrados, &tilesAbiertos, posicionAdyacente, posicionDestino, tileActual, 14);

		// Posicion superior
		posicionAdyacente = tileActual->posicion();
		posicionAdyacente.y -= 1;
		posicionProcesada |= posicionProcesada |= this->agregarTile(mapaTilesCerrados, &tilesAbiertos, posicionAdyacente, posicionDestino, tileActual, 10);

		// Posicion superior derecha
		posicionAdyacente = tileActual->posicion();
		posicionAdyacente.x += 1;
		posicionAdyacente.y -= 1;
		posicionProcesada |= this->agregarTile(mapaTilesCerrados, &tilesAbiertos, posicionAdyacente, posicionDestino, tileActual, 14);

		// Posicion izquierda
		posicionAdyacente = tileActual->posicion();
		posicionAdyacente.x -= 1;
		posicionProcesada |= posicionProcesada |= this->agregarTile(mapaTilesCerrados, &tilesAbiertos, posicionAdyacente, posicionDestino, tileActual, 10);

		// Posicion derecha
		posicionAdyacente = tileActual->posicion();
		posicionAdyacente.x += 1;
		posicionProcesada |= posicionProcesada |= this->agregarTile(mapaTilesCerrados, &tilesAbiertos, posicionAdyacente, posicionDestino, tileActual, 10);

		// Posicion inferior izquierda
		posicionAdyacente = tileActual->posicion();
		posicionAdyacente.x -= 1;
		posicionAdyacente.y += 1;
		posicionProcesada |= this->agregarTile(mapaTilesCerrados, &tilesAbiertos, posicionAdyacente, posicionDestino, tileActual, 14);

		// Posicion inferior
		posicionAdyacente = tileActual->posicion();
		posicionAdyacente.y += 1;
		posicionProcesada |= posicionProcesada |= this->agregarTile(mapaTilesCerrados, &tilesAbiertos, posicionAdyacente, posicionDestino, tileActual, 10);

		// Posicion inferior derecha
		posicionAdyacente = tileActual->posicion();
		posicionAdyacente.x += 1;
		posicionAdyacente.y += 1;
		posicionProcesada |= this->agregarTile(mapaTilesCerrados, &tilesAbiertos, posicionAdyacente, posicionDestino, tileActual, 14);

		// Ordeno la lista si se prceso alguna posicion
		if (posicionProcesada)
			tilesAbiertos.sort();
	}

	delete[] mapaTilesCerrados;
}

void ModeloEntidad::ModeloMovimiento::asignarEntidades(Mutex* mutexEntidades, multimap<pair<int, int>, ModeloEntidad*>* entidades) {
	this->_mutexEntidades = mutexEntidades;
	this->_entidades = entidades;
}

void ModeloEntidad::ModeloMovimiento::asignarEntidadesMoviles(Mutex* mutexEntidadesMoviles, list<ModeloEntidad*>* entidadesMoviles) {
	this->_mutexEntidadesMoviles = mutexEntidadesMoviles;
	this->_entidadesMoviles = entidadesMoviles;
}

void ModeloEntidad::ModeloMovimiento::cambiarEstado() {
	if (this->_posiciones.empty())
		return;
	
	if (this->_instanteUltimoCambioEstado == 0) {
		this->_instanteUltimoCambioEstado = GetTickCount();
		return;
	}

	if (this->_modeloEntidad->velocidad() > (GetTickCount() - this->_instanteUltimoCambioEstado))
		return;

	// Obtengo la siguente posicion del movimiento actual
	Posicion posicionSiguiente = this->obtenerPosicionSiguiente();
	this->_modeloEntidad->direccion(Posicion::obtenerDireccion(this->_modeloEntidad->posicionActual(), posicionSiguiente));
	
	// Si choque con algo en el camino y no estoy en la ultima posicion recalculo
	if (this->detectarColision(posicionSiguiente) != NULL) {
		// Si la ultima posicion es la que esta ocupada me dentego
		if (this->_posiciones.empty()) {
			this->detener();
			return;
		}

		this->actualizar(this->_posiciones.back());
		Posicion posicionSiguiente = this->obtenerPosicionSiguiente();
		this->_modeloEntidad->direccion(Posicion::obtenerDireccion(this->_modeloEntidad->posicionActual(), posicionSiguiente));
	}

	// Notifico a VistaMovimiento
	this->_modeloEntidad->posicionSiguiente(posicionSiguiente);
	this->notificarObservadores();
	this->_modeloEntidad->posicionActual(this->_modeloEntidad->posicionSiguiente());

	if (this->_posiciones.empty())
		this->_modeloEntidad->accion(CAMINANDO);

	this->_instanteUltimoCambioEstado = GetTickCount();
}

void ModeloEntidad::ModeloMovimiento::detener() {
	this->_posiciones.clear();
	this->_modeloEntidad->accion(CAMINANDO);
}

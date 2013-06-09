#include "ModeloItem.h"

ModeloGolem::ModeloGolem(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad, TIPO_ITEM_GOLEM) {
}

ModeloGolem::~ModeloGolem() {
}

bool ModeloGolem::aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems) {
	if (jugador->tieneGolem())
		return true;

	ModeloJugador* golem = this->crearGolem(jugador);
	listaGolems->agregarJugador(golem);
	jugador->asignarGolem(golem);
	
	return true;
}

// Lo usa el ModeloFactory para cargar los datos necesarios para la creación del golem
void ModeloGolem::cargarDatos(int alto, int ancho, int fps, int anchoEscenario, int altoEscenario, void* pSocketServidor, ModeloDrop::stDatosDrop datosDrop){
	this->alto = alto;
	this->ancho = ancho;
	this->fps = fps;
	this->anchoEscenario = anchoEscenario;
	this->altoEscenario = altoEscenario;
	this->pSocketServidor = pSocketServidor;
	this->datosDrop = datosDrop;
}

ModeloJugador* ModeloGolem::crearGolem(ModeloJugador* jugador) {
	// Creo el proxy para este enemigo
	ProxyModeloEntidad* pProxyEntidad = new ProxyModeloEntidad();
	pProxyEntidad->setSocketServidor(pSocketServidor);

	// Creo el enemigo (es un ModeloJugador) y lo agrego al nivel
	ModeloJugador* pGolem = new ModeloJugador(alto,ancho,jugador->modeloEntidad()->velocidad(),jugador->posicionGolem(),altoEscenario,anchoEscenario,fps,pProxyEntidad,Ticket::getInstance().pedirNumero(),ENTIDAD_GOLEM,"",(jugador->maximoVida() / 2),0,(jugador->danioAtaque() / 2),jugador->modeloEntidad()->id(),TIPO_ENTIDAD_GOLEM,true,datosDrop);

	return pGolem;
}
